/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
int NUM[10][7]={
		{0,0,0,0,0,0,1},
		{1,0,0,1,1,1,1},
		{0,0,1,0,0,1,0},
		{0,0,0,0,1,1,0},
		{1,0,0,1,1,0,0},
		{0,1,0,0,1,0,0},
		{0,1,0,0,0,0,0},
		{0,0,0,1,1,1,1},
		{0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0},
};

void display7SEG(int num)
{
	HAL_GPIO_WritePin(B0_GPIO_Port, B0_Pin, NUM[num][0]);
	HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, NUM[num][1]);
	HAL_GPIO_WritePin(B2_GPIO_Port, B2_Pin, NUM[num][2]);
	HAL_GPIO_WritePin(B3_GPIO_Port, B3_Pin, NUM[num][3]);
	HAL_GPIO_WritePin(B4_GPIO_Port, B4_Pin, NUM[num][4]);
	HAL_GPIO_WritePin(B5_GPIO_Port, B5_Pin, NUM[num][5]);
	HAL_GPIO_WritePin(B6_GPIO_Port, B6_Pin, NUM[num][6]);
}
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_GPIO_WritePin(GPIOA, LED_RED_1_Pin, 1);
  HAL_GPIO_WritePin(GPIOA, LED_YELLOW_1_Pin, 1);
  HAL_GPIO_WritePin(GPIOA, LED_GREEN_1_Pin, 1);

  HAL_GPIO_WritePin(GPIOA, LED_RED_2_Pin, 1);
  HAL_GPIO_WritePin(GPIOA, LED_YELLOW_2_Pin, 1);
  HAL_GPIO_WritePin(GPIOA, LED_GREEN_2_Pin, 1);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int counter = 0;
  while (1)
  {
    /* USER CODE END WHILE */
	  	  if (counter >= 0) counter = 0;

	  	  HAL_GPIO_WritePin(GPIOA, LED_RED_2_Pin, 0);		// Turn on RED_LED_2

	  	  HAL_GPIO_WritePin(GPIOA, LED_GREEN_1_Pin, 0);		// Turn on GREEN_LED_1 3s
	  	  display7SEG(counter++);							// 7SEG: 0s
	  	  HAL_Delay(1000);
	  	  display7SEG(counter++);							// 7SEG: 1s
	  	  HAL_Delay(1000);
	  	  display7SEG(counter++);							// 7SEG: 2s
	  	  HAL_Delay(1000);
	  	  HAL_GPIO_WritePin(GPIOA, LED_GREEN_1_Pin, 1);

	  	  HAL_GPIO_WritePin(GPIOA, LED_YELLOW_1_Pin, 0);	// Turn on YELLOW_LED_1 2s
	  	  display7SEG(counter++);							// 7SEG: 3s
	  	  HAL_Delay(1000);
	  	  display7SEG(counter++);							// 7SEG: 4s
	  	  HAL_Delay(1000);
	  	  HAL_GPIO_WritePin(GPIOA, LED_YELLOW_1_Pin, 1);

	  	  HAL_GPIO_WritePin(GPIOA, LED_RED_2_Pin, 1);		// Turn off RED_LED_2 after 5s


	  	  HAL_GPIO_WritePin(GPIOA, LED_RED_1_Pin, 0);		// Turn on RED_LED_1

	  	  HAL_GPIO_WritePin(GPIOA, LED_GREEN_2_Pin, 0);		// Turn on GREEN_LED_2 3s
	  	  display7SEG(counter++);							// 7SEG: 5s
	  	  HAL_Delay(1000);
	  	  display7SEG(counter++);							// 7SEG: 6s
	  	  HAL_Delay(1000);
	  	  display7SEG(counter++);							// 7SEG: 7s
	  	  HAL_Delay(1000);
	  	  HAL_GPIO_WritePin(GPIOA, LED_GREEN_2_Pin, 1);

	  	  HAL_GPIO_WritePin(GPIOA, LED_YELLOW_2_Pin, 0);	// Turn on YELLOW_LED_2 2s
	  	  display7SEG(counter++);							// 7SEG: 8s
	  	  HAL_Delay(1000);
	  	  display7SEG(counter++);							// 7SEG: 9s
	  	  HAL_Delay(1000);
	  	  HAL_GPIO_WritePin(GPIOA, LED_YELLOW_2_Pin, 1);

	  	  HAL_GPIO_WritePin(GPIOA, LED_RED_1_Pin, 1);		// Turn off RED_LED_1 after 5s
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |LED_RED_1_Pin|LED_YELLOW_1_Pin|LED_GREEN_1_Pin|LED_RED_2_Pin
                          |LED_YELLOW_2_Pin|LED_GREEN_2_Pin|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, B0_Pin|B1_Pin|B2_Pin|B10_Pin
                          |B11_Pin|B12_Pin|B13_Pin|B3_Pin
                          |B4_Pin|B5_Pin|B6_Pin|B7_Pin
                          |B8_Pin|B9_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA2 PA3 PA4
                           LED_RED_1_Pin LED_YELLOW_1_Pin LED_GREEN_1_Pin LED_RED_2_Pin
                           LED_YELLOW_2_Pin LED_GREEN_2_Pin PA11 PA12
                           PA13 PA14 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |LED_RED_1_Pin|LED_YELLOW_1_Pin|LED_GREEN_1_Pin|LED_RED_2_Pin
                          |LED_YELLOW_2_Pin|LED_GREEN_2_Pin|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : B0_Pin B1_Pin B2_Pin B10_Pin
                           B11_Pin B12_Pin B13_Pin B3_Pin
                           B4_Pin B5_Pin B6_Pin B7_Pin
                           B8_Pin B9_Pin */
  GPIO_InitStruct.Pin = B0_Pin|B1_Pin|B2_Pin|B10_Pin
                          |B11_Pin|B12_Pin|B13_Pin|B3_Pin
                          |B4_Pin|B5_Pin|B6_Pin|B7_Pin
                          |B8_Pin|B9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
