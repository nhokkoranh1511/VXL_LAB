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

void display7SEG(int num);

#define RESET 0
#define ONE 1
#define TWO 2
#define THREE 3
#define ZERO 4
// Khơi tạo trạng thái đầu tiên
int status = RESET;

void FSM();

const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1, 5, 0, 8};

void update7SEG(int index);

int hour = 15, minute = 8, second = 50;
void updateClockBuffer();
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE BEGIN 0 */
int timer0_counter = 0;
int timer0_flag = 0;

int timer1_counter = 0;
int timer1_flag = 0;

int timer2_counter = 0;
int timer2_flag = 0;

int TIMER_CYCLE = 10;

void setTimer0 (int duration){
	timer0_counter = duration / TIMER_CYCLE ;
	timer0_flag = 0;
}

void setTimer1 (int duration){
	timer1_counter = duration / TIMER_CYCLE ;
	timer1_flag = 0;
}

void setTimer2 (int duration){
	timer2_counter = duration / TIMER_CYCLE ;
	timer2_flag = 0;
}

void timer_run(){
	if(timer0_counter > 0){
			timer0_counter --;

			if( timer0_counter == 0){
				timer0_flag = 1;
			}
	}

	if(timer1_counter > 0){
			timer1_counter --;

			if( timer1_counter == 0){
				timer1_flag = 1;
			}
	}

	if(timer2_counter > 0){
			timer2_counter --;

			if( timer2_counter == 0){
				timer2_flag = 1;
			}
	}
}

const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
uint8_t matrix_buffer[] = {0x00, 0xFC, 0x16, 0x13, 0x13, 0x16, 0xFC, 0x00};

void displayLEDMatrix(uint8_t bit)
{
	HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, !((bit&(1<<0))>>0));
	HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, !((bit&(1<<1))>>1));
	HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, !((bit&(1<<2))>>2));
	HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, !((bit&(1<<3))>>3));
	HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, !((bit&(1<<4))>>4));
	HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, !((bit&(1<<5))>>5));
	HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, !((bit&(1<<6))>>6));
	HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, !((bit&(1<<7))>>7));
}

void clearLEDMatrix(){
	HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, 1);
	HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, 1);
	HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, 1);
	HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, 1);
	HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, 1);
	HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, 1);
	HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, 1);
	HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, 1);

	HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, 1);
	HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1);
	HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1);
	HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1);
	HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1);
	HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1);
	HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1);
	HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1);
}

int temp = 0;
void updateLEDMatrix (int index){
	switch (index)
	{
		case 0: {
			HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1);
			displayLEDMatrix(matrix_buffer[(index + temp) % 8]);
			HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, 0);
		  break;
		}
		case 1: {
			HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, 1);
			displayLEDMatrix(matrix_buffer[(index + temp) % 8]);
			HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 0);
		  break;
		}
		case 2: {
			HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1);
			displayLEDMatrix(matrix_buffer[(index + temp) % 8]);
			HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 0);
		  break;
		}
		case 3: {
			HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1);
			displayLEDMatrix(matrix_buffer[(index + temp) % 8]);
			HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 0);
		  break;
		}
		case 4: {
			HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1);
			displayLEDMatrix(matrix_buffer[(index + temp) % 8]);
			HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 0);
		  break;
		}
		case 5: {
			HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1);
			displayLEDMatrix(matrix_buffer[(index + temp) % 8]);
			HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 0);
		  break;
		}
		case 6: {
			HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1);
			displayLEDMatrix(matrix_buffer[(index + temp) % 8]);
			HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 0);
		  break;
		}
		case 7: {
			HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1);
			displayLEDMatrix(matrix_buffer[(index + temp) % 8]);
			HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 0);
		  break;
		}
	}
}
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT (&htim2 );
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  setTimer0(1000);
  setTimer1(25);
  setTimer2(250);

  FSM();

  while (1)
  {
    /* USER CODE END WHILE */
	  if( timer0_flag == 1){
		  second ++;
		  if ( second >= 60) {
			  second = 0;
			  minute ++;
		  }

		  if( minute >= 60) {
			  minute = 0;
			  hour ++;
		  }

		  if( hour >=24){
			  hour = 0;
		  }

		  // update hour, minute, second variables
		  updateClockBuffer();

		  // reset timer0 - delay 1s
		  setTimer0(1000) ;
	  }

	  // Matrix LED
	  if (timer1_flag == 1){
		  if (index_led_matrix > 7){
			  index_led_matrix = 0;
			  //temp++;
		  }

		  //if (temp > 8){
			//  temp = 0;
		  //}

		  updateLEDMatrix(index_led_matrix++);

		  // reset timer1 - delay 0.025s
		  setTimer1(25);
	  }

	  // Đồng hồ
	  if (timer2_flag == 1){
		  FSM();

		  // reset timer2 - delay 0.25s
		  setTimer2(250);
	  }
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|ENM0_Pin|ENM1_Pin|DOT_Pin
                          |LED_RED_Pin|EN0_Pin|EN1_Pin|EN2_Pin
                          |EN3_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin
                          |ENM5_Pin|ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 ENM0_Pin ENM1_Pin DOT_Pin
                           LED_RED_Pin EN0_Pin EN1_Pin EN2_Pin
                           EN3_Pin ENM2_Pin ENM3_Pin ENM4_Pin
                           ENM5_Pin ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_1|ENM0_Pin|ENM1_Pin|DOT_Pin
                          |LED_RED_Pin|EN0_Pin|EN1_Pin|EN2_Pin
                          |EN3_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin
                          |ENM5_Pin|ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin PB3 PB4 PB5
                           PB6 ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim ){
	timer_run();
}


void display7SEG(int num)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, NUM[num][0]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, NUM[num][1]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, NUM[num][2]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, NUM[num][3]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, NUM[num][4]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, NUM[num][5]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, NUM[num][6]);
}

void update7SEG (int index ){
	switch (index ){
		case 0:
			// Display the first 7 SEG with led_buffer [0]
			display7SEG(led_buffer[0]);
			break ;

		case 1:
			// Display the second 7 SEG with led_buffer [1]
			display7SEG(led_buffer[1]);
			break ;

		case 2:
			// Display the third 7 SEG with led_buffer [2]
			display7SEG(led_buffer[2]);
			break ;

		case 3:
			// Display the forth 7 SEG with led_buffer [3]
			// sáng đèn thứ hai , tắt các đèn còn lại
			display7SEG(led_buffer[3]);
			break ;

		default :
			break ;
	}
}

void updateClockBuffer(){
	led_buffer[0] = hour / 10;
	led_buffer[1] = hour % 10;
	led_buffer[2] = minute / 10;
	led_buffer[3] = minute % 10;
}

void FSM(){
	switch (status) {
		case RESET:
			// tắt tất cả đèn
			// 4 đèn 7SEG
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);

			// đèn LED_RED
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 1);

			// đèn DOT
			HAL_GPIO_WritePin(DOT_GPIO_Port, DOT_Pin, 1);

			// LED Matrix
			clearLEDMatrix();

			status = ONE;
			break;

		case ONE:
			// sáng đèn thứ nhất LED = 1, tắt các đèn còn lại
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
			update7SEG(0);
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);

			status = TWO;
			break;

		case TWO:
			// sáng đèn thứ hai LED = 2, tắt các đèn còn lại
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			update7SEG(1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);

			status = THREE;
			break;

		case THREE:
			// sáng đèn thứ ba LED = 3, tắt các đèn còn lại
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			update7SEG(2);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);

			status = ZERO;
			break;

		case ZERO:
			// sáng đèn thứ tư LED = 0, tắt các đèn còn lại
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			update7SEG(3);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);

			// chớp đèn sau 1s
			HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
			HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);

			status = ONE;
			break;

		default:
			// tắt tất cả đèn
			// 4 đèn 7SEG
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);

			// đèn LED_RED
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 1);

			// đèn DOT
			HAL_GPIO_WritePin(DOT_GPIO_Port, DOT_Pin, 1);

			status = RESET;
			break;
	}
}

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
