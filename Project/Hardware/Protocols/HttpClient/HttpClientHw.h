#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <stdint.h>
#include "HttpClient.h"
#include "HttpClientHw.h"
#include "esp_http_client.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class HttpClientHw final : public HttpClient
{
    static constexpr char * MODULE = (char *)"HttpClientHw";

    public:
        HttpClientHw () = default;
        ~HttpClientHw () = default;

        void Cleanup          (void)                                   override;
        bool Init             (void)                                   override;
        int  GetStatusCode    (void)                                   override;
        int  GetContentLength (void)                                   override;
        int  Open             (uint16_t v_len)                         override;
        int  FetchHeaders     (void)                                   override;
        int  Perform          (void)                                   override;
        int  Read             (char * v_payload, uint16_t v_len)       override;
        void SetPostField     (const char * v_body, int v_len)         override;

    protected:
        void setMethod        (EMethod v_method)                       override;
        void setHeader        (std::string v_key, std::string v_value) override;

    private:
        esp_http_client_handle_t client = { };
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
