#include <stdint.h>
#include "MainCpp.h"
#include "stm32f4xx_hal_gpio.h"

// GPIOC
#define LCD_PC0_PIN  GPIO_PIN_0
#define LCD_PC1_PIN  GPIO_PIN_1
#define LCD_PC2_PIN  GPIO_PIN_2
#define LCD_PC3_PIN  GPIO_PIN_3
#define LCD_PC4_PIN  GPIO_PIN_4
#define LCD_PC5_PIN  GPIO_PIN_5
#define LCD_PC6_PIN  GPIO_PIN_6
#define LCD_PC7_PIN  GPIO_PIN_7
#define LCD_PC8_PIN  GPIO_PIN_8
#define LCD_PC9_PIN  GPIO_PIN_9
#define LCD_PC10_PIN GPIO_PIN_10
#define LCD_PC11_PIN GPIO_PIN_11
#define LCD_PC12_PIN GPIO_PIN_12
#define LCD_PC13_PIN GPIO_PIN_13
#define LCD_PC14_PIN GPIO_PIN_14
#define LCD_PC15_PIN GPIO_PIN_15


// GPIOB
#define LCD_CS   GPIO_PIN_12  	// CSX
#define LCD_RS   GPIO_PIN_13  	// D/CX
#define LCD_WR   GPIO_PIN_14    // WRX
#define LCD_RD   GPIO_PIN_15  	// RDX

// GPIOA
#define LCD_XL   GPIO_PIN_0
#define LCD_YU   GPIO_PIN_1
#define LCD_XR   GPIO_PIN_2
#define LCD_YD   GPIO_PIN_3

void SetGpiocAsInput (void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin              = LCD_PC0_PIN|
						      	  	   LCD_PC1_PIN|
									   LCD_PC2_PIN|
									   LCD_PC3_PIN|
									   LCD_PC4_PIN|
									   LCD_PC5_PIN|
									   LCD_PC6_PIN|
									   LCD_PC7_PIN|
									   LCD_PC8_PIN|
									   LCD_PC9_PIN|
									   LCD_PC10_PIN|
									   LCD_PC11_PIN|
									   LCD_PC12_PIN|
									   LCD_PC13_PIN|
									   LCD_PC14_PIN|
									   LCD_PC15_PIN;
	  GPIO_InitStruct.Mode  		 = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull  		 = GPIO_NOPULL;
	  GPIO_InitStruct.Speed 		 = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init (GPIOC, &GPIO_InitStruct);
}


void SetGpiocAsOutput (void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin              = LCD_PC0_PIN|
						      	  	   LCD_PC1_PIN|
									   LCD_PC2_PIN|
									   LCD_PC3_PIN|
									   LCD_PC4_PIN|
									   LCD_PC5_PIN|
									   LCD_PC6_PIN|
									   LCD_PC7_PIN|
									   LCD_PC8_PIN|
									   LCD_PC9_PIN|
									   LCD_PC10_PIN|
									   LCD_PC11_PIN|
									   LCD_PC12_PIN|
									   LCD_PC13_PIN|
									   LCD_PC14_PIN|
									   LCD_PC15_PIN;
	  GPIO_InitStruct.Mode  		 = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull  		 = GPIO_NOPULL;
	  GPIO_InitStruct.Speed 		 = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init (GPIOC, &GPIO_InitStruct);
}

void Write (uint16_t v_data)
{
	for (uint8_t bitPos = 0; bitPos < 16; bitPos++)
	{
		GPIO_PinState state = GPIO_PIN_RESET;

		if (((v_data >> bitPos) & 0x1) == true)
		{
			state = GPIO_PIN_SET;
		}

		HAL_GPIO_WritePin (GPIOC, (1 << bitPos), state);

	}
}

void WriteCommand (uint16_t v_data)
{
	HAL_GPIO_WritePin (GPIOB, LCD_CS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GPIOB, LCD_RS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GPIOB, LCD_RD, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOB, LCD_WR, GPIO_PIN_RESET);

	Write             (v_data);

	HAL_Delay         (1);
	HAL_GPIO_WritePin (GPIOB, LCD_WR, GPIO_PIN_SET);
}

uint16_t ReadParameter (void)
{
	SetGpiocAsInput   ();
	HAL_GPIO_WritePin (GPIOB, LCD_CS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GPIOB, LCD_RS, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOB, LCD_WR, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOB, LCD_RD, GPIO_PIN_RESET);

	uint16_t data = 0;
	for (uint8_t bitPos = 0; bitPos < 16; bitPos++)
	{
		bool state = HAL_GPIO_ReadPin (GPIOC, (1 << bitPos));
		data = data + (1 << bitPos) * state;
	}

	HAL_Delay         (1);
	HAL_GPIO_WritePin (GPIOB, LCD_RD, GPIO_PIN_SET);
	SetGpiocAsOutput  ();

	return data;
}

void WriteParameter (uint16_t v_data)
{
	HAL_GPIO_WritePin (GPIOB, LCD_CS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GPIOB, LCD_RS, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOB, LCD_RD, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOB, LCD_WR, GPIO_PIN_RESET);

	Write             (v_data);

	HAL_Delay         (1);
	HAL_GPIO_WritePin (GPIOB, LCD_WR, GPIO_PIN_SET);
}

#define SOFTWARE_RESET         0x01
#define DISPLAY_ON             0x29
#define NORMAL_DISPLAY_MODE_ON 0x13
#define DISPLAY_INVERSION_OFF  0x20
#define DISPLAY_INVERSION_ON   0x21

#define BACKLIGHT_CONTROL_1    0xB8
#define BACKLIGHT_CONTROL_2    0xB9
#define BACKLIGHT_CONTROL_3    0xBA
#define BACKLIGHT_CONTROL_4    0xBB
#define BACKLIGHT_CONTROL_5    0xBC
#define BACKLIGHT_CONTROL_6    0xBD
#define BACKLIGHT_CONTROL_7    0xBE
#define BACKLIGHT_CONTROL_8    0xBF

extern "C" void MainCpp (void)
{
	WriteCommand   (SOFTWARE_RESET);
	HAL_Delay      (1000);

	WriteCommand   (DISPLAY_ON);

	WriteCommand   (BACKLIGHT_CONTROL_1);
	WriteParameter (0x04);

	while (1)
	{
		//WriteParameter (DISPLAY_ON);
	}
}

