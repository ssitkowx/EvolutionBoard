#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class HttpClient
{
    public:
        enum class EStatusCode : uint16_t
        {
            eOk               = 200,
            eCreated          = 201,
            ePartialContent   = 201,
            eBadRequest       = 400,
            eUnauthorized     = 401,
            eNotFound         = 404,
            eMethodNotAllowed = 405
        } eStatusCode;

        enum class EMethod : uint8_t
        {
            eGet,
            ePost,
            ePut,
            ePatch,
            eDelete,
            eHead,
            eNotify,
            eSubscribe,
            eUnsubscribe,
            eOptions,
            eMax,
        };

        HttpClient ();
        virtual ~HttpClient () = default;

        virtual void Cleanup          (void)                                             = 0;
        virtual bool Init             (void)                                             = 0;
        virtual int  GetStatusCode    (void)                                             = 0;
        virtual int  GetContentLength (void)                                             = 0;
        virtual int  Open             (uint16_t v_len)                                   = 0;
        virtual int  FetchHeaders     (void)                                             = 0;
        virtual int  Perform          (void)                                             = 0;
        virtual int  Read             (char * v_payload, uint16_t v_len)                 = 0;
        virtual void SetPostField     (const char * v_body, int v_len)                   = 0;
        
    protected:
        virtual void setMethod        (EMethod v_method)                                 = 0;
        virtual void setHeader        (std::string_view v_key, std::string_view v_value) = 0;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
