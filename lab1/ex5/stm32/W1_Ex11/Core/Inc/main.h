/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define LED_RED_1_Pin GPIO_PIN_5
#define LED_RED_1_GPIO_Port GPIOA
#define LED_YELLOW_1_Pin GPIO_PIN_6
#define LED_YELLOW_1_GPIO_Port GPIOA
#define LED_GREEN_1_Pin GPIO_PIN_7
#define LED_GREEN_1_GPIO_Port GPIOA
#define B0_Pin GPIO_PIN_0
#define B0_GPIO_Port GPIOB
#define B1_Pin GPIO_PIN_1
#define B1_GPIO_Port GPIOB
#define B2_Pin GPIO_PIN_2
#define B2_GPIO_Port GPIOB
#define B10_Pin GPIO_PIN_10
#define B10_GPIO_Port GPIOB
#define B11_Pin GPIO_PIN_11
#define B11_GPIO_Port GPIOB
#define B12_Pin GPIO_PIN_12
#define B12_GPIO_Port GPIOB
#define B13_Pin GPIO_PIN_13
#define B13_GPIO_Port GPIOB
#define LED_RED_2_Pin GPIO_PIN_8
#define LED_RED_2_GPIO_Port GPIOA
#define LED_YELLOW_2_Pin GPIO_PIN_9
#define LED_YELLOW_2_GPIO_Port GPIOA
#define LED_GREEN_2_Pin GPIO_PIN_10
#define LED_GREEN_2_GPIO_Port GPIOA
#define B3_Pin GPIO_PIN_3
#define B3_GPIO_Port GPIOB
#define B4_Pin GPIO_PIN_4
#define B4_GPIO_Port GPIOB
#define B5_Pin GPIO_PIN_5
#define B5_GPIO_Port GPIOB
#define B6_Pin GPIO_PIN_6
#define B6_GPIO_Port GPIOB
#define B7_Pin GPIO_PIN_7
#define B7_GPIO_Port GPIOB
#define B8_Pin GPIO_PIN_8
#define B8_GPIO_Port GPIOB
#define B9_Pin GPIO_PIN_9
#define B9_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
