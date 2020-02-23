/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_PC13_Pin GPIO_PIN_13
#define LCD_PC13_GPIO_Port GPIOC
#define LCD_PC14_Pin GPIO_PIN_14
#define LCD_PC14_GPIO_Port GPIOC
#define LCD_PC15_Pin GPIO_PIN_15
#define LCD_PC15_GPIO_Port GPIOC
#define LCD_PC0_Pin GPIO_PIN_0
#define LCD_PC0_GPIO_Port GPIOC
#define LCD_PC1_Pin GPIO_PIN_1
#define LCD_PC1_GPIO_Port GPIOC
#define LCD_PC2_Pin GPIO_PIN_2
#define LCD_PC2_GPIO_Port GPIOC
#define LCD_PC3_Pin GPIO_PIN_3
#define LCD_PC3_GPIO_Port GPIOC
#define LCD_X_Pin GPIO_PIN_0
#define LCD_X_GPIO_Port GPIOA
#define LCD_Y_Pin GPIO_PIN_1
#define LCD_Y_GPIO_Port GPIOA
#define LCD_XA2_Pin GPIO_PIN_2
#define LCD_XA2_GPIO_Port GPIOA
#define LCD_YA3_Pin GPIO_PIN_3
#define LCD_YA3_GPIO_Port GPIOA
#define LCD_PC4_Pin GPIO_PIN_4
#define LCD_PC4_GPIO_Port GPIOC
#define LCD_PC5_Pin GPIO_PIN_5
#define LCD_PC5_GPIO_Port GPIOC
#define LED_DATA_Pin GPIO_PIN_0
#define LED_DATA_GPIO_Port GPIOB
#define LED_SHCP_Pin GPIO_PIN_1
#define LED_SHCP_GPIO_Port GPIOB
#define LED_STCP_Pin GPIO_PIN_2
#define LED_STCP_GPIO_Port GPIOB
#define LCD_CS_Pin GPIO_PIN_12
#define LCD_CS_GPIO_Port GPIOB
#define LCD_RS_Pin GPIO_PIN_13
#define LCD_RS_GPIO_Port GPIOB
#define LCD_WR_Pin GPIO_PIN_14
#define LCD_WR_GPIO_Port GPIOB
#define LCD_RD_Pin GPIO_PIN_15
#define LCD_RD_GPIO_Port GPIOB
#define LCD_PC6_Pin GPIO_PIN_6
#define LCD_PC6_GPIO_Port GPIOC
#define LCD_PC7_Pin GPIO_PIN_7
#define LCD_PC7_GPIO_Port GPIOC
#define LCD_PC8_Pin GPIO_PIN_8
#define LCD_PC8_GPIO_Port GPIOC
#define LCD_PC9_Pin GPIO_PIN_9
#define LCD_PC9_GPIO_Port GPIOC
#define LCD_PC10_Pin GPIO_PIN_10
#define LCD_PC10_GPIO_Port GPIOC
#define LCD_PC11_Pin GPIO_PIN_11
#define LCD_PC11_GPIO_Port GPIOC
#define LCD_PC12_Pin GPIO_PIN_12
#define LCD_PC12_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
