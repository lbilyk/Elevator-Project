/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Change the NODE number depending on the floor node */
#define NODE  2

#if NODE == 1					// First floor
#define ID 					0x0201

#elif NODE == 2					// Second floor
#define ID 					0x0202

#elif NODE == 3					// Third floor
#define ID					0x0203

#elif NODE == 4 				// Inside elevator
#define ID					0x0200

#endif

#define FLOOR_1				0x05
#define FLOOR_2				0x06
#define FLOOR_3				0x07

#define NO_BUTTON_PRESSED	0
#define BUTTON_PRESSED 		1

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
CAN_TxHeaderTypeDef   TxHeader;
CAN_RxHeaderTypeDef   RxHeader;

uint8_t               TxData[8];
uint8_t               RxData[8];
uint32_t              TxMailbox;

uint8_t msg = FLOOR_1;					// Message from node
uint8_t	BUTTON = NO_BUTTON_PRESSED;		// Button pressed flag changed in interrupt

uint8_t currentFloor = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

void lightFloorLED(char led);
void lightOffSwitchLED();

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
  MX_CAN_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* Variables */
  uint8_t i;
  char receivedMsg;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	  /* Light LED depending of current floor */
	  if ((RxData[0] != 0) && (RxData[0] != 0x01)){
		 receivedMsg = RxData[0];

		 if (receivedMsg != currentFloor ){
			 lightFloorLED(receivedMsg);
			 currentFloor = receivedMsg;
		 }
		 for(i=0;i<8;i++){	// Clear buffer
			 RxData[i] = 0x00;
		 }
	  }

	  lightOffSwitchLED();

	  // Transmit.

	  /* Transmit floor message. Floor selected on interrupt */
	  if (BUTTON != 0) {

		 HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
		 HAL_Delay(300);
		 TxData[0] = msg;

		 if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK){
			 Error_Handler();
		 }

		 HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
		 BUTTON = NO_BUTTON_PRESSED;
	 }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN;
  hcan.Init.Prescaler = 32;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_6TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */
  /*******************************************************/
  // Set up CAN Rx filters
  CAN_FilterTypeDef sFilterConfig;

  // Configure filter 0 to direct everything to FIFO 0
  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.SlaveStartFilterBank = 0;

  if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK){
    /* Filter configuration Error */
    Error_Handler();
  }

  // Start CAN peripheral
  if (HAL_CAN_Start(&hcan) != HAL_OK){
    /* Start Error */
    Error_Handler();
  }

  // Activate CAN Rx notification interrupt
  if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK){
    /* Notification Error */
    Error_Handler();
  }

  TxHeader.IDE = CAN_ID_STD;	// Using standard mode. Note CAN_ID_EXT for extended mode
  TxHeader.ExtId = 0x00;		// Extented id not used
  TxHeader.StdId = ID;			// ID defined in constant sections
  TxHeader.RTR = CAN_RTR_DATA;	// Send a data frame nor an RTR
  TxHeader.DLC = 1;				// Data length code = 1 (just one byte)
  TxHeader.TransmitGlobalTime = DISABLE;

  /****************************************************************/

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, ledSwitchFloor1_Pin|ledSwitchFloor2_Pin|ledSwitchFloor3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ledCurrentFloor1_Pin|ledCurrentFloor2_Pin|ledCurrentFloor3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ledSwitchFloor1_Pin ledSwitchFloor2_Pin ledSwitchFloor3_Pin */
  GPIO_InitStruct.Pin = ledSwitchFloor1_Pin|ledSwitchFloor2_Pin|ledSwitchFloor3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ledCurrentFloor1_Pin ledCurrentFloor2_Pin ledCurrentFloor3_Pin */
  GPIO_InitStruct.Pin = ledCurrentFloor1_Pin|ledCurrentFloor2_Pin|ledCurrentFloor3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : bFirstFloor_Pin bSecondFloor_Pin bThirdFloor_Pin */
  GPIO_InitStruct.Pin = bFirstFloor_Pin|bSecondFloor_Pin|bThirdFloor_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

/**************** Private functions start here *************************/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	/* Depending on GPIO activated */
	if(GPIO_Pin == bThirdFloor_Pin){
		BUTTON = BUTTON_PRESSED;
		msg = FLOOR_3;

		/* Light up switch LED*/
		HAL_GPIO_WritePin(GPIOC,ledSwitchFloor3_Pin, GPIO_PIN_SET);	// Light up switch led

	}else if(GPIO_Pin == bSecondFloor_Pin){
		BUTTON = BUTTON_PRESSED;
		msg = FLOOR_2;

		HAL_GPIO_WritePin(GPIOC,ledSwitchFloor2_Pin, GPIO_PIN_SET);	// Light up switch led

	}else if(GPIO_Pin == bFirstFloor_Pin){
		BUTTON = BUTTON_PRESSED;
		msg = FLOOR_1;

		HAL_GPIO_WritePin(GPIOC,ledSwitchFloor1_Pin, GPIO_PIN_SET);	// Light up switch led

	}else {}	/* Do nothing */

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
	/* Get the TX message and store in RxData[] buffer */
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK){
		Error_Handler();
	}
}

void lightFloorLED(char led){

	/* Switch off and on floor LEDs*/
	switch (led){

	case FLOOR_1:	// Light up LED for floor 1
		HAL_GPIO_WritePin(GPIOB, ledCurrentFloor2_Pin | ledCurrentFloor3_Pin, GPIO_PIN_RESET);	// Reset LED
		HAL_GPIO_WritePin(GPIOB,ledCurrentFloor1_Pin, GPIO_PIN_SET);
		break;

	case FLOOR_2:	// Light up LED for floor 2
		HAL_GPIO_WritePin(GPIOB,ledCurrentFloor1_Pin | ledCurrentFloor3_Pin, GPIO_PIN_RESET);	// Reset LED
		HAL_GPIO_WritePin(GPIOB,ledCurrentFloor2_Pin, GPIO_PIN_SET);
		break;

	case FLOOR_3:	// Light up LED for floor 3
		HAL_GPIO_WritePin(GPIOB,ledCurrentFloor1_Pin | ledCurrentFloor2_Pin , GPIO_PIN_RESET);	// Reset LED
		HAL_GPIO_WritePin(GPIOB,ledCurrentFloor3_Pin, GPIO_PIN_SET);
		break;

	default:
		break;

	}
}

void lightOffSwitchLED(){

	/* When elevator arrives to floor turn of switch LED */
	switch (currentFloor){

	case FLOOR_1:	// Light up LED for floor 1
		HAL_GPIO_WritePin(GPIOC,ledSwitchFloor1_Pin, GPIO_PIN_RESET);	// Light up switch led
		break;

	case FLOOR_2:	// Light up LED for floor 2
		HAL_GPIO_WritePin(GPIOC,ledSwitchFloor2_Pin, GPIO_PIN_RESET);	// Light OFF switch led
		break;

	case FLOOR_3:	// Light up LED for floor 3
		HAL_GPIO_WritePin(GPIOC,ledSwitchFloor3_Pin, GPIO_PIN_RESET);	// Light up switch led
		break;

	}
}

/***********************************************************************/
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
