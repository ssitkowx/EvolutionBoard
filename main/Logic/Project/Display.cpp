///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdio.h>
#include <memory.h>
#include "Display.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "assert.h"

///
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include <stdbool.h>
#include "esp_err.h"

#define LCD_HOST    HSPI_HOST
#define DMA_CHAN    2

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// VARIABLES ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//static spi_device_handle_t gSpi;

typedef enum {
    LCD_TYPE_ILI = 1,
    LCD_TYPE_ST,
    LCD_TYPE_MAX,
} type_lcd_t;

typedef struct {
    uint8_t cmd;
    uint8_t data[16];
    uint8_t databytes; //No of data in data; bit 7 = delay after set; 0xFF = end of cmds.
} lcd_init_cmd_t;

DRAM_ATTR static const lcd_init_cmd_t ili_init_cmds[]={
    /* Power contorl B, power control = 0, DC_ENA = 1 */
    {0xCF, {0x00, 0x83, 0X30}, 3},
    /* Power on sequence control,
     * cp1 keeps 1 frame, 1st frame enable
     * vcl = 0, ddvdh=3, vgh=1, vgl=2
     * DDVDH_ENH=1
     */
    {0xED, {0x64, 0x03, 0X12, 0X81}, 4},
    /* Driver timing control A,
     * non-overlap=default +1
     * EQ=default - 1, CR=default
     * pre-charge=default - 1
     */
    {0xE8, {0x85, 0x01, 0x79}, 3},
    /* Power control A, Vcore=1.6V, DDVDH=5.6V */
    {0xCB, {0x39, 0x2C, 0x00, 0x34, 0x02}, 5},
    /* Pump ratio control, DDVDH=2xVCl */
    {0xF7, {0x20}, 1},
    /* Driver timing control, all=0 unit */
    {0xEA, {0x00, 0x00}, 2},
    /* Power control 1, GVDD=4.75V */
    {0xC0, {0x26}, 1},
    /* Power control 2, DDVDH=VCl*2, VGH=VCl*7, VGL=-VCl*3 */
    {0xC1, {0x11}, 1},
    /* VCOM control 1, VCOMH=4.025V, VCOML=-0.950V */
    {0xC5, {0x35, 0x3E}, 2},
    /* VCOM control 2, VCOMH=VMH-2, VCOML=VML-2 */
    {0xC7, {0xBE}, 1},
    /* Memory access contorl, MX=MY=0, MV=1, ML=0, BGR=1, MH=0 */
    {0x36, {0x28}, 1},
    /* Pixel format, 16bits/pixel for RGB/MCU interface */
    {0x3A, {0x55}, 1},
    /* Frame rate control, f=fosc, 70Hz fps */
    {0xB1, {0x00, 0x1B}, 2},
    /* Enable 3G, disabled */
    {0xF2, {0x08}, 1},
    /* Gamma set, curve 1 */
    {0x26, {0x01}, 1},
    /* Positive gamma correction */
    {0xE0, {0x1F, 0x1A, 0x18, 0x0A, 0x0F, 0x06, 0x45, 0X87, 0x32, 0x0A, 0x07, 0x02, 0x07, 0x05, 0x00}, 15},
    /* Negative gamma correction */
    {0XE1, {0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3A, 0x78, 0x4D, 0x05, 0x18, 0x0D, 0x38, 0x3A, 0x1F}, 15},
    /* Column address set, SC=0, EC=0xEF */
    {0x2A, {0x00, 0x00, 0x00, 0xEF}, 4},
    /* Page address set, SP=0, EP=0x013F */
    {0x2B, {0x00, 0x00, 0x01, 0x3f}, 4},
    /* Memory write */
    {0x2C, {0}, 0},
    /* Entry mode set, Low vol detect disabled, normal display */
    {0xB7, {0x07}, 1},
    /* Display function control */
    {0xB6, {0x0A, 0x82, 0x27, 0x00}, 4},
    /* Sleep out */
    {0x11, {0}, 0x80},
    /* Display on */
    {0x29, {0}, 0x80},
    {0, {0}, 0xff},
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void resetDiplay     (void) {}
void enableBacklight (void) {}

void lcd_cmd (spi_device_handle_t spi, const uint8_t cmd)
{
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=8;                     //Command is 8 bits
    t.tx_buffer=&cmd;               //The data is the cmd itself
    t.user=(void*)0;                //D/C needs to be set to 0
    //gpio_set_level ((gpio_num_t)Gpio::EPinNum::eDc, 0);
    ret = spi_device_polling_transmit (spi, &t);  //Transmit!
    assert (ret==ESP_OK);            //Should have had no issues.
}

uint32_t lcd_get_id (spi_device_handle_t spi)
{
    //get_id cmd
    lcd_cmd(spi, 0x04);

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length=8*3;
    t.flags = SPI_TRANS_USE_RXDATA;
    t.user = (void*)1;
    //gpio_set_level ((gpio_num_t)Gpio::EPinNum::eDc, 1);
    esp_err_t ret = spi_device_polling_transmit (spi, &t);
    assert (ret == ESP_OK );

    return *(uint32_t*)t.rx_data;
}

void lcd_data (spi_device_handle_t spi, const uint8_t *data, int len)
{
    esp_err_t ret;
    spi_transaction_t t;
    if (len==0) return;             //no need to send anything
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=len*8;                 //Len is in bytes, transaction length is in bits.
    t.tx_buffer=data;               //Data
    t.user=(void*)1;                //D/C needs to be set to 1
    //gpio_set_level ((gpio_num_t)Gpio::EPinNum::eDc, 1);
    ret=spi_device_polling_transmit(spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.
}

Display::Display (Gpio & v_gpio, Spi & v_spi) : gpio (v_gpio), spi (v_spi)
{
    printf ("Display init.\n");

    int cmd=0;
    const lcd_init_cmd_t* lcd_init_cmds;

    //Initialize non-SPI GPIOs
    gpio.SetPinDirection (Gpio::EPinNum::eDc  , Gpio::EPinMode::eOutput);
    gpio.SetPinDirection (Gpio::EPinNum::eRst , Gpio::EPinMode::eOutput);
    gpio.SetPinDirection (Gpio::EPinNum::eBclk, Gpio::EPinMode::eOutput);

    //Reset the display
    gpio.SetPinLevel (Gpio::EPinNum::eRst, false);
    vTaskDelay(100 / portTICK_RATE_MS);
    gpio.SetPinLevel (Gpio::EPinNum::eRst, true);
    vTaskDelay(100 / portTICK_RATE_MS);

    //detect LCD type
    printf("Get id\n");
    //uint32_t lcd_id = lcd_get_id(spi.spi);
    uint32_t lcd_id = getId ();
    int lcd_detected_type;

    printf("LCD ID: %08X\n", lcd_id);
    if ( lcd_id == 0 ) {
        //zero, ili
        lcd_detected_type = LCD_TYPE_ILI;
        printf("ILI9341 detected.\n");
    } else {
        // none-zero, ST
        lcd_detected_type = LCD_TYPE_ST;
        printf("ST7789V detected.\n");
    }

    printf("LCD ILI9341 initialization.\n");
    lcd_init_cmds = ili_init_cmds;

    //Send all the commands
    while (lcd_init_cmds[cmd].databytes!=0xff)
    {
        // command
        uint8_t data [18] = {0, 0};
        data [0] = 0;
        data [1] = 0;
        data [3] = lcd_init_cmds [cmd].cmd;
        spi.Send (&data [0], 1);

        // data
        data [0] = 0;
        data [1] = 1;
        memcpy (&data[2], lcd_init_cmds [cmd].data, lcd_init_cmds [cmd].databytes & 0x1F);
        spi.Send (&data [0], lcd_init_cmds [cmd].databytes & 0x1F);
        if (lcd_init_cmds[cmd].databytes & 0x80)
        {
            vTaskDelay(100 / portTICK_RATE_MS);
        }
        cmd++;
    }

    ///Enable backlight
    gpio.SetPinLevel (Gpio::EPinNum::eBclk, false);
}

void Display::DrawRect (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_length, const uint16_t v_width, const uint16_t v_color)
{
    if (validateRect (v_xPos, v_yPos, v_length, v_width) == false)
    {
        printf("Rect outside display \n");
        return;
    }

    const uint16_t rectMaxLen = Settings::GetInstance ().Lcd.Length * Settings::GetInstance ().Lcd.MaxLinesPerTransfer;
    uint16_t rect [rectMaxLen];
    memset (rect, v_color, rectMaxLen * 2);

    uint8_t maxRects = calculateRects (v_length, v_width);
    if (maxRects == 1)
    {
        printf("v_xPos: %u, v_yPos: %u, v_length: %u, v_width: %u end \n", v_xPos, v_yPos, v_length, v_width);
        sendLines (v_xPos, v_yPos, v_length, v_width, (uint16_t *)rect);
    }
    else
    {
        uint16_t yPos  = v_yPos;
        uint16_t width = 0;
        for (uint8_t rectNum = 1; rectNum < (maxRects + 1); rectNum++)
        {
            if (rectNum == maxRects)
            {
                printf("Last rect \n");
                width = v_width + v_yPos - yPos;

                printf("v_xPos: %u, yPos: %u, v_length: %u, width: %u end \n", v_xPos, yPos, v_length, width);
                sendLines (v_xPos, yPos, v_length, width, (uint16_t *)rect);
                break;
            }

            printf("v_xPos: %u, yPos: %u, v_length: %u, width: %u end \n", v_xPos, yPos, v_length, Settings::GetInstance().Lcd.MaxLinesPerTransfer);
            sendLines (v_xPos, yPos, v_length, Settings::GetInstance().Lcd.MaxLinesPerTransfer, (uint16_t *)rect);
            yPos = yPos + Settings::GetInstance().Lcd.MaxLinesPerTransfer;
        }
    }
}

#include "driver/spi_master.h"
void Display::sendLines (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_length, const uint16_t v_width, const uint16_t * v_data)
{/*
        static spi_transaction_t trans[6];
        for (uint8_t pos = 0; pos < 6; pos++)
        {
            memset (&trans[pos], 0, sizeof(trans [pos]));
        }

        trans[0].tx_data[0] = 0x2A;                           // Column Address Set
        spi.SendInQueue (&trans[0].tx_data[0], 1, 0, Spi::EFlag::eTxData);

        trans[1].tx_data[0] = v_xPos >> 8;                    // Start Col High
        trans[1].tx_data[1] = v_xPos & 0xFF;                  // Start Col Low
        trans[1].tx_data[2] = (v_xPos + v_length) >> 8;       // End Col High
        trans[1].tx_data[3] = (v_xPos + v_length) & 0xFF;     // End Col Low
        spi.SendInQueue (&trans[1].tx_data[0], 4, 1, Spi::EFlag::eTxData);

        trans[2].tx_data[0] = 0x2B;                           // Page address set
        spi.SendInQueue (&trans[2].tx_data[0], 1, 0, Spi::EFlag::eTxData);

        trans[3].tx_data[0] = v_yPos >> 8;                    // Start page high
        trans[3].tx_data[1] = v_yPos & 0xFF;                  // start page low
        trans[3].tx_data[2] = (v_yPos + v_width) >> 8;          // End page high
        trans[3].tx_data[3] = (v_yPos + v_width) & 0xFF;        // End page low
        spi.SendInQueue (&trans[3].tx_data[3], 4, 1, Spi::EFlag::eTxData);

        trans[4].tx_data[0] = 0x2C;                           // Memory write
        spi.SendInQueue (&trans[4].tx_data[0], 1, 0, Spi::EFlag::eTxData);

        //trans[5].tx_buffer  = v_data;                         // Finally send the line data
        //trans[5].length     = v_length * v_width * 2 * 8;     // Data length, in bits
        //trans[5].flags      = 0;                              // Undo SPI_TRANS_USE_TXDATA flag
        spi.SendRawInQueue (v_data, v_length * v_width, 1);
*/

    esp_err_t ret;
    int x;
    //Transaction descriptors. Declared static so they're not allocated on the stack; we need this memory even when this
    //function is finished because the SPI driver needs access to it even while we're already calculating the next line.
    static spi_transaction_t trans[6];

    //In theory, it's better to initialize trans and data only once and hang on to the initialized
    //variables. We allocate them on the stack, so we need to re-init them each call.
    for (x=0; x<6; x++) {
        memset(&trans[x], 0, sizeof(spi_transaction_t));
       /* if ((x&1)==0) {
            //Even transfers are commands
            trans[x].length=8;
            trans[x].user=(void*)0;
        } else {
            //Odd transfers are data
            trans[x].length=8*4;
            trans[x].user=(void*)1;
        }
        trans[x].flags=SPI_TRANS_USE_TXDATA;*/
    }


    trans [0].tx_data [0] = SPI_TRANS_USE_TXDATA;
    trans [0].tx_data [1] = 0;
    trans [0].tx_data [2] = 0x2A;                           // Column Address Set
    spi.Send (&trans [0].tx_data[0], 1);

    trans [1].tx_data [0] = SPI_TRANS_USE_TXDATA;
    trans [1].tx_data [1] = 1;
    trans [1].tx_data [2] = v_xPos >> 8;                    // Start Col High
    trans [1].tx_data [3] = v_xPos & 0xFF;                  // Start Col Low
    trans [1].tx_data [4] = (v_xPos + v_length) >> 8;       // End Col High
    trans [1].tx_data [5] = (v_xPos + v_length) & 0xFF;     // End Col Low
    spi.Send (&trans [1].tx_data[0], 4);

    trans [2].tx_data [0] = SPI_TRANS_USE_TXDATA;
    trans [2].tx_data [1] = 0;
    trans [2].tx_data [2] = 0x2B;                           // Page address set
    spi.Send (&trans[2].tx_data[0], 1);

    trans [3].tx_data [0] = SPI_TRANS_USE_TXDATA;
    trans [3].tx_data [1] = 1;
    trans [3].tx_data [2] = v_yPos >> 8;                    // Start page high
    trans [3].tx_data [3] = v_yPos & 0xFF;                  // start page low
    trans [3].tx_data [4] = (v_yPos + v_width) >> 8;          // End page high
    trans [3].tx_data [5] = (v_yPos + v_width) & 0xFF;        // End page low
    spi.Send (&trans [3].tx_data[0], 4);

    trans [4].tx_data [0] = SPI_TRANS_USE_TXDATA;
    trans [4].tx_data [1] = 0;
    trans [4].tx_data [2] = 0x2C;                           // Memory write
    spi.Send (&trans [4].tx_data[0], 1);

    trans [5].tx_buffer   = v_data;                         // Finally send the line data
    trans [5].length      = v_length * v_width * 2 * 8;     // Data length, in bits
    trans [5].flags       = 0;                              // Undo SPI_TRANS_USE_TXDATA flag
    spi.Send (&trans [5].tx_data[0], 4);
}

uint8_t Display::calculateRects (const uint16_t v_length, const uint16_t v_width)
{
    double  rects    = v_width / Settings::GetInstance ().Lcd.MaxLinesPerTransfer;
    uint8_t maxRects = (uint8_t)rects;

    if ((v_width % Settings::GetInstance ().Lcd.MaxLinesPerTransfer) != 0) { maxRects++; }

    return maxRects;
}

bool Display::validateRect (const uint16_t v_xPos, const uint16_t v_yPos, const uint16_t v_length, const uint16_t v_width)
{
    if (((v_xPos + v_length) <= 0)                 ||
        ((v_yPos + v_width)  <= 0)                 ||
        ((v_xPos + v_length) > Settings::GetInstance ().Lcd.Length) ||
        ((v_yPos + v_width)  > Settings::GetInstance ().Lcd.Width))
    {
        return false;
    }

    return true;
}

uint32_t Display::getId (void)
{
    uint8_t data [3] = {};
    data [0] = 0;
    data [1] = 0;
    data [2] = 0x04;
    spi.Send (&data[0], 1);

    data [0] = SPI_TRANS_USE_RXDATA;
    data [1] = 1;
    return *(uint32_t*)spi.Send (&data[0], 3);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
