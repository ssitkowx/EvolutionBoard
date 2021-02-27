#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <stdint.h>
#include "Settings.h"
#include "HttpClient.h"
#include "HttpClientHw.h"
#include "esp_http_client.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class HttpClientHw final : public HttpClient <HttpClientHw>
{
    static constexpr char * MODULE = (char *)"HttpClientHw";
    friend HttpClient<HttpClientHw>;

    public:
        HttpClientHw () = default;
        ~HttpClientHw () = default;

        void Cleanup (void) { esp_http_client_cleanup (client); }
        bool Init    (void)
        {
            esp_http_client_config_t config = { };
            config.url                      = Settings::GetInstance ().WeatherMeasure.Endpoint.data ();
            config.transport_type           = HTTP_TRANSPORT_OVER_SSL;

            client = esp_http_client_init (&config);
            if (client == NULL) { return false; }

            setMethod (HttpClient::EMethod::eGet);
            setHeader (Settings::GetInstance ().WeatherMeasure.Authorization.Key.data (),
                       Settings::GetInstance ().WeatherMeasure.Authorization.Value.data ());
            return true;
        }

        int  GetStatusCode    (void)                                               { return esp_http_client_get_status_code    (client);                           }
        int  GetContentLength (void)                                               { return esp_http_client_get_content_length (client);                           }
        int  Open             (const uint16_t v_len)                               { return esp_http_client_open               (client, v_len);                    }
        int  FetchHeaders     (void)                                               { return esp_http_client_fetch_headers      (client);                           }
        int  Perform          (void)                                               { return esp_http_client_perform            (client);                           }
        int  Read             (const char * const v_payload, const uint16_t v_len) { return esp_http_client_read               (client, (char *)v_payload, v_len); }
        void SetPostField     (const char * const v_body, const int v_len)         { esp_http_client_set_post_field            (client, v_body, v_len);            }

    protected:
        void setMethod        (const EMethod v_method)                             { esp_http_client_set_method                (client, static_cast <esp_http_client_method_t> (v_method)); }
        void setHeader        (std::string_view v_key, std::string_view v_value)   { esp_http_client_set_header                (client, static_cast<std::string>(v_key).c_str(), static_cast<std::string>(v_value).c_str()); }

    private:
        esp_http_client_handle_t client = { };
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
