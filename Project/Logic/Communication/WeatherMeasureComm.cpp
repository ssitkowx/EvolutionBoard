///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include <vector>
#include "cJSON.h"
#include "WiFiHw.h"
#include <stdint.h>
#include "ActionId.h"
#include "LoggerHw.h"
#include "SystemTime.h"
#include "SystemEvents.h"
#include "WeatherMeasureComm.h"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void WeatherMeasureComm::receive (void)
{
    static bool isMeasureUpdated = false;
    //static bool isMeasureUpdated = true;    // todo temp
    if (isMeasureUpdated == true)
    {
        LOGD (MODULE, "Measurement already updated");
        return;
    }

    isMeasureUpdated = true;

    if (WiFi<WiFiHw>::IsOnline () == false)
    {
        LOGW (MODULE, "Offline.");
        return;
    }

    if (http.Init () == false)
    {
        LOGE  (MODULE, "Can't initialize http client.");
        http.Cleanup ();
        return;
    }

    int openStatus = http.Open (ZERO);
    if (openStatus != ZERO)
    {
        LOGE (MODULE, "Can't open HTTP connection. Status: %d.", openStatus);
        http.Cleanup ();
        return;
    }

    int contentLen = http.FetchHeaders ();
    if (contentLen < ZERO)
    {
        LOGE (MODULE, "Can't fetch headers or contentLen over limit. ContentLen: %d.", contentLen);
        http.Cleanup ();
        return;
    }

    Chunk recvData (recvDataMaxLen);
    int readLen = http.Read (recvData.payload, recvDataMaxLen);
    if (readLen < ZERO)
    {
        LOGE (MODULE, "Can't read response.");
        http.Cleanup ();
        return;
    }

    root = cJSON_Parse         (recvData.payload);
    weatherMeasureParser.Parse (root);
    body = cJSON_Print         (root);
    LOGI                       (MODULE, "Json:                  %s.", body);
    LOGV                       (MODULE, "Expected data readLen: %d.", readLen);
    LOGV                       (MODULE, "http.GetStatusCode (): %d.", http.GetStatusCode ());
    LOGV                       (MODULE, "Stack size:            %u.", Rtos::GetInstance ()->GetCurrentStackSize ("WeatherMeasureComm"));
    LOGV                       (MODULE, "Heap size:             %u.", Rtos::GetInstance ()->GetCurrentHeapSize ());
    clear                      (root, body);

    SystemEvents::GetInstance ().CircBuf.Add ((uint8_t)EActionId::eWeatherUpdated);
}

void WeatherMeasureComm::clear (cJSON * v_root, char * v_body)
{
    free         (v_body);
    cJSON_Delete (v_root);
    http.Cleanup ();
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
