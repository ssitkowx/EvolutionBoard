///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Settings.h"
#include "HttpClientHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void HttpClientHw::Cleanup (void)
{
    esp_http_client_cleanup (client);
}

bool HttpClientHw::Init (void)
{
    esp_http_client_config_t config = { };
    config.url                      = static_cast<std::string>(Settings::GetInstance ().WeatherMeasure.Endpoint).c_str ();
    config.transport_type           = HTTP_TRANSPORT_OVER_SSL;

    client = esp_http_client_init (&config);
    if (client == NULL) { return false; }

    setMethod (HttpClient::EMethod::eGet);
    setHeader (Settings::GetInstance ().WeatherMeasure.Authorization.Key,
               Settings::GetInstance ().WeatherMeasure.Authorization.Value);
    setHeader ("Content-Type", "application/json");
    return true;
}

int HttpClientHw::GetStatusCode (void)
{
    return esp_http_client_get_status_code (client);
}

int HttpClientHw::GetContentLength (void)
{
    return esp_http_client_get_content_length (client);
}

int HttpClientHw::Open (uint16_t v_len)
{
    return esp_http_client_open (client, v_len);
}

int HttpClientHw::FetchHeaders (void)
{
    return esp_http_client_fetch_headers (client);
}

int HttpClientHw::Perform (void)
{
    return esp_http_client_perform (client);
}

int HttpClientHw::Read (char * v_payload, uint16_t v_len)
{
    return esp_http_client_read (client, (char *)v_payload, v_len);
}

void HttpClientHw::SetPostField (const char * v_body, int v_len)
{
    esp_http_client_set_post_field (client, v_body, v_len);
}

void HttpClientHw::setMethod (EMethod v_method)
{
    esp_http_client_set_method (client, static_cast <esp_http_client_method_t> (v_method));
}

void HttpClientHw::setHeader (std::string_view v_key, std::string_view v_value)
{
    esp_http_client_set_header (client, static_cast<std::string>(v_key).c_str(), static_cast<std::string>(v_value).c_str());
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
