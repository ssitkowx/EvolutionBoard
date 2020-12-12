///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Rtos.h"
#include "GpioHw.h"
#include "LoggerHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

GpioHw::GpioHw ()
{
    LOG (MODULE, "Init.");
/*
    gpio_config_t config;
    config.intr_type    = static_cast<gpio_int_type_t>(EInterrupt::eFalling);
    config.mode         = static_cast<gpio_mode_t>    (EPinMode::eInput);
    config.pin_bit_mask = static_cast<gpio_num_t>     (1ULL << (uint8_t)ETouch::eIrq);
    config.pull_down_en = static_cast<gpio_pulldown_t>(GPIO_PULLDOWN_DISABLE);
    config.pull_up_en   = static_cast<gpio_pullup_t>  (GPIO_PULLUP_DISABLE);

    ESP_ERROR_CHECK          (gpio_config (&config));
    gpio_install_isr_service (ESP_INTR_FLAG_EDGE);
    gpio_isr_handler_add     (static_cast<gpio_num_t>(ETouch::eIrq), WaitForTouchIsr, (void *)ETouch::eIrq);
    */
}

GpioHw::~GpioHw () { LOG (MODULE, "Deinit."); }

void GpioHw::SetPinLevel     (const uint16_t v_num, const bool v_state)    { gpio_set_level        (static_cast<gpio_num_t> (v_num), v_state);                                      }
void GpioHw::SetPinDirection (const uint16_t v_num, const uint16_t v_mode) { gpio_set_direction    (static_cast<gpio_num_t> (v_num), getPinMode (static_cast <EPinMode> (v_mode))); }
bool GpioHw::ReadPinLevel    (const uint16_t v_num)                        { return gpio_get_level (static_cast<gpio_num_t> (v_num));                                               }

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
