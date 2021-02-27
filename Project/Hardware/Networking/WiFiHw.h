#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "WiFi.h"
#include <string>
#include "Utils.h"
#include "TimerHw.h"
#include "esp_wifi.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class WiFiHw final : public WiFi<WiFiHw>
{
    static constexpr char * MODULE = (char *)"WiFiHw";

    public:
        WiFiHw ();
        ~WiFiHw ();

        void                         Reconnect            (void);

    protected:
        static esp_err_t             onWiFiEvent          (void * v_ctx, system_event_t * v_event);
        void                         startStation         (void);
        void                         startApp             (void);
    
    private:
        static void                  displayMac           (void);
        static void                  displayNetworkParams (void);
        static void                  getMac               (EMode v_mode, std::array <uint8_t, SIX_BYTES> & v_mac);
        static Config::NetworkParams getNetworkParams     (void);
        static WiFi<WiFiHw>::Modes   getModes             (void);

        void                         initStation          (void);
        void                         deinit               (void);
        void                         start                (void);
        void                         stop                 (void);
        void                         setStationSettings   (std::string_view v_ssid, std::string_view v_password);
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
