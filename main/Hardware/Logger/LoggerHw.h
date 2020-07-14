#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "Logger.h"
#include "esp_log.h"
#include "SystemTime.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#define LOG(MODULE,MSG, ...)  Logger::GetInstance ()->Log <LoggerHw> (Logger::ELogLevel::eLogNone   , MODULE, MSG, ##__VA_ARGS__);
#define LOGE(MODULE,MSG, ...) Logger::GetInstance ()->Log <LoggerHw> (Logger::ELogLevel::eLogError  , MODULE, MSG, ##__VA_ARGS__);
#define LOGW(MODULE,MSG, ...) Logger::GetInstance ()->Log <LoggerHw> (Logger::ELogLevel::eLogWarning, MODULE, MSG, ##__VA_ARGS__);
#define LOGI(MODULE,MSG, ...) Logger::GetInstance ()->Log <LoggerHw> (Logger::ELogLevel::eLogInfo   , MODULE, MSG, ##__VA_ARGS__);
#define LOGD(MODULE,MSG, ...) Logger::GetInstance ()->Log <LoggerHw> (Logger::ELogLevel::eLogDebug  , MODULE, MSG, ##__VA_ARGS__);
#define LOGV(MODULE,MSG, ...) Logger::GetInstance ()->Log <LoggerHw> (Logger::ELogLevel::eLogVerbose, MODULE, MSG, ##__VA_ARGS__);

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class LoggerHw : public Logger
{
    private:
        std::string getFontColor (ELogLevel v_eLogLevel)
        {
            switch (v_eLogLevel)
            {
                case ELogLevel::eLogNone:    { return LOG_COLOR_BLACK;  }
                case ELogLevel::eLogError:   { return LOG_COLOR_RED;    }
                case ELogLevel::eLogWarning: { return LOG_COLOR_CYAN;  }   // This is Yellow :)
                case ELogLevel::eLogInfo:    { return LOG_COLOR_BLUE;   }
                case ELogLevel::eLogDebug:   { return LOG_COLOR_PURPLE; }
                case ELogLevel::eLogVerbose: { return LOG_COLOR_GREEN;  }
                default:                     { break;                   }
            };

            return LOG_COLOR_BLACK;
        }

    public:
        template<typename... ARGS>
        void Log (const ELogLevel v_eLogLevel, const std::string && v_module, const std::string && v_msg, ARGS &&... v_args)
        {
            std::string line = Format ("\033[1;37m%s \033[1;%sm%s: %s.\n",
                                       "fAKE TIME",//SystemTime::GetInstance ()->ToString ("%F %T").c_str (),    // this make restart, dont know why
                                       getFontColor  (v_eLogLevel).data (),
                                       v_module.data (), v_msg.data ());

            esp_log_write (static_cast <esp_log_level_t> (v_eLogLevel), v_module.data (), line.c_str (), std::forward <ARGS>(v_args)...);
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
