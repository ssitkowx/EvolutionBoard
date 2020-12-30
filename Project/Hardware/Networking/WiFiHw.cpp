///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include <thread>
#include "Utils.h"
#include <string.h>
#include <stdint.h>
#include "WiFiHw.h"
#include "esp_err.h"
#include "LoggerHw.h"
#include "Settings.h"
#include "SystemTime.h"
#include "esp_system.h"
#include "esp_event_loop.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

WiFiHw::WiFiHw ()
{
    setStationSettings (static_cast <std::string>(Settings::GetInstance ().WiFi.Station.Ssid),
                        static_cast <std::string>(Settings::GetInstance ().WiFi.Station.Password));
    initStation        ();
    start              ();
}

WiFiHw::~WiFiHw ()
{
    stop   ();
    deinit ();
}

void WiFiHw::Reconnect (void)
{
    LOGI (MODULE, "Try reconnect.")

    if (getModes ().StaConnected == true)
    {
        //if (esp_wifi_disconnect () == ESP_OK)
        //{
            if (esp_wifi_connect () == ESP_OK)
            {
                LOGW (MODULE, "Can't connect WiFi");
            }
        //}
        //else
        //{
        //    LOGW (MODULE, "Can't disconnect WiFi");
        //}
    }
    
    Rtos::GetInstance()->DelayInMs (FIVE_THOUSAND);
    //std::this_thread::sleep_for (5s);
}

esp_err_t WiFiHw::onWiFiEvent (void * v_ctx, system_event_t * v_event)
{
    LOGI (MODULE, "WiFi management event: %u.", v_event->event_id);

    EEvents EEvent = EEvents::eDisconnected;
    if (v_event->event_id == SYSTEM_EVENT_STA_START)
    {
        EEvent = EEvents::eStart;
        LOGI             (MODULE, "Station start.");
        esp_wifi_connect ();
    }
    if (v_event->event_id == SYSTEM_EVENT_STA_STOP)
    {
        EEvent = EEvents::eStop;
        LOGI (MODULE, "Station stop./n");
    }
    else if (v_event->event_id == SYSTEM_EVENT_STA_CONNECTED)
    {
        EEvent = EEvents::eConnected;
        displayMac ();
        LOGI       (MODULE, "Station connected.");
    }
    else if (v_event->event_id == SYSTEM_EVENT_STA_DISCONNECTED)
    {
        EEvent = EEvents::eDisconnected;
        LOGI (MODULE, "Station disconnected.");
    }
    else if (v_event->event_id == SYSTEM_EVENT_STA_GOT_IP)
    {
        EEvent = EEvents::eGotIp;
        displayNetworkParams      ();
        SystemTime::GetInstance ()->Update ();
    }
    else if (v_event->event_id == SYSTEM_EVENT_STA_LOST_IP)
    {
        EEvent = EEvents::eLostIp;
        LOGI (MODULE, "Ip lost.");
    }

    onEvent (EEvent);

    return ESP_OK;
}

void WiFiHw::startStation(void)
{
    stop        ();
    initStation ();
    start       ();
}

void WiFiHw::displayMac (void)
{
    std::array <uint8_t, MAC_LEN> macAddr;
    getMac (EMode::eStation, macAddr);

    LOGI (MODULE, "Mac Address %02x:%02x:%02x:%02x:%02x:%02x.", macAddr [FIRST_BYTE],
                                                                macAddr [SECOND_BYTE],
                                                                macAddr [THIRD_BYTE],
                                                                macAddr [FOURTH_BYTE],
                                                                macAddr [FIFTH_BYTE],
                                                                macAddr [SIXTH_BYTE]);
}

void WiFiHw::displayNetworkParams (void)
{
    WiFi::Config::NetworkParams networkParams = getNetworkParams ();
    LOGI (MODULE, "Got Ip: %s, Mask: %s, Gateway: %s, IPv6: %s.", networkParams.Ipv4.c_str    (),
                                                                  networkParams.Mask.c_str    (),
                                                                  networkParams.Gateway.c_str (),
                                                                  networkParams.Ipv6.c_str    ());
}

void WiFiHw::getMac (EMode v_mode, std::array <uint8_t, SIX_BYTES> & v_mac)
{
    switch (v_mode)
    {
        case EMode::eStation:
        {
			esp_wifi_get_mac (WIFI_IF_STA, v_mac.data ());
            break;
        }
        case EMode::eAp:
        {
			esp_wifi_get_mac (ESP_IF_WIFI_AP, v_mac.data ());
            break;
        }
        default:
        {
			esp_wifi_get_mac (ESP_IF_MAX, v_mac.data ());
            break;
        }
    }
}

WiFi<WiFiHw>::Config::NetworkParams WiFiHw::getNetworkParams (void)
{
    if (getModes ().StaConnected == false) { LOGE (MODULE, "Station disconnected./n"); }

    tcpip_adapter_ip_info_t networkInfo = { };
    if (tcpip_adapter_get_ip_info (TCPIP_ADAPTER_IF_STA, &networkInfo) != ESP_OK) { LOGE (MODULE, "Can't get Ipv4 info."); }

    struct IPv4Address
    {
        union
        {
            uint8_t  bytes [FOUR_BYTES];
            uint32_t dword;
        } Ipv4;
        
        IPv4Address (uint32_t v_ipv4) { Ipv4.dword = v_ipv4; }
    };

    const IPv4Address ipv4 (networkInfo.ip.addr);
    const IPv4Address mask (networkInfo.netmask.addr);
    const IPv4Address gw   (networkInfo.gw.addr);

    ip6_addr_t ipv6 = { };
    if (tcpip_adapter_get_ip6_linklocal (TCPIP_ADAPTER_IF_STA, &ipv6) != ESP_OK) { LOGW (MODULE, "Can't get Ipv6 info."); }

    char ipv6Buff [THIRTY_BYTES] = { };
    ip6addr_ntoa_r (&ipv6, ipv6Buff, sizeof (ipv6Buff));

    auto toString = [] (const IPv4Address & v_address) { return Format ("%u.%u.%u.%u", v_address.Ipv4.bytes [FIRST_BYTE],
                                                                                       v_address.Ipv4.bytes [SECOND_BYTE],
                                                                                       v_address.Ipv4.bytes [THIRD_BYTE],
                                                                                       v_address.Ipv4.bytes [FOURTH_BYTE]); };

    return { toString (ipv4), toString (mask), toString (gw), std::string (ipv6Buff) };
}

WiFi<WiFiHw>::Modes WiFiHw::getModes (void)
{
    wifi_mode_t wifiMode;
    if (Mode.Started == false)
    {
        wifiMode = WIFI_MODE_NULL;
        LOGE (MODULE, "Not started.");
    }

    if (esp_wifi_get_mode (&wifiMode) == ESP_ERR_WIFI_NOT_INIT)
    {
        wifiMode = WIFI_MODE_NULL;
        LOGE (MODULE, "Can't read mode.");
    }

    WiFi::Modes modes;
    modes.Started         = Mode.Started;
    modes.StaConnected    = (wifiMode & WIFI_MODE_STA) == 1 ? true : false;

    return modes;
}

void WiFiHw::initStation (void)
{
    LOG                (MODULE, "Init station with Ssid = %s and Password = %s.", settings.Station.Ssid,
                                                                                    settings.Station.Password);

    tcpip_adapter_init ();
    ESP_ERROR_CHECK    (esp_event_loop_init (onWiFiEvent, NULL));

    wifi_init_config_t configInit = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK    (esp_wifi_init        (&configInit));
    ESP_ERROR_CHECK    (esp_wifi_set_storage (WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK    (esp_wifi_set_mode    (WIFI_MODE_STA));
    
    wifi_config_t      configWiFi;
    memset             (&configWiFi, 0, sizeof (wifi_config_t));
    memcpy             (configWiFi.sta.ssid    , settings.Station.Ssid    , SSID_LEN);
    memcpy             (configWiFi.sta.password, settings.Station.Password, PASSWORD_LEN);

    ESP_ERROR_CHECK    (esp_wifi_set_mode   (WIFI_MODE_STA));
    ESP_ERROR_CHECK    (esp_wifi_set_config (ESP_IF_WIFI_STA, &configWiFi));
}

void WiFiHw::deinit (void)
{
    ESP_ERROR_CHECK (esp_wifi_deinit ());
    LOG             (MODULE, "Deinit.")
}

void WiFiHw::start (void)
{
    Mode.Started = true;

    LOG             (MODULE, "Start.");
    ESP_ERROR_CHECK (esp_wifi_start ());
}

void WiFiHw::stop (void)
{
    LOG             (MODULE, "Stop.")
    ESP_ERROR_CHECK (esp_wifi_stop ());
}

void WiFiHw::setStationSettings (std::string v_ssid, std::string v_password)
{
    memset (settings.Station.Ssid    , ZERO              , SSID_LEN);
    memset (settings.Station.Password, ZERO              , PASSWORD_LEN);
    memcpy (settings.Station.Ssid    , v_ssid    .data (), v_ssid    .length ());
    memcpy (settings.Station.Password, v_password.data (), v_password.length ());
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
