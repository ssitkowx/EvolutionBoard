#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <class DERIVED_TYPE>
class HttpClient
{
    friend DERIVED_TYPE;
    DERIVED_TYPE & derivedType = static_cast <DERIVED_TYPE &>(*this);

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

        HttpClient () : eStatusCode (EStatusCode::eNotFound) { }

        void Cleanup          (void)                                             { derivedType.Cleanup                 ();                 }
        bool Init             (void)                                             { return derivedType.Init             ();                 }
        int  GetStatusCode    (void)                                             { return derivedType.GetStatusCode    ();                 }
        int  GetContentLength (void)                                             { return derivedType.GetContentLength ();                 }
        int  Open             (uint16_t v_len)                                   { return derivedType.Open             (v_len);            }
        int  FetchHeaders     (void)                                             { return derivedType.FetchHeaders     ();                 }
        int  Perform          (void)                                             { return derivedType.Perform          ();                 }
        int  Read             (char * v_payload, uint16_t v_len)                 { return derivedType.Read             (v_payload, v_len); }
        void SetPostField     (const char * v_body, int v_len)                   { derivedType.SetPostField            (v_body, v_len);    }
        
    protected:
        void setMethod        (EMethod v_method)                                 { derivedType.setMethod               (v_method);         }
        void setHeader        (std::string_view v_key, std::string_view v_value) { derivedType.setHeader               (v_key, v_value);   }

    private:
        ~HttpClient () = default;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
