/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
volatile char currdata; 
volatile char lastdata;

volatile int flag;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void TransmitChar(char c);
void TransmitStr(char* str);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);



/* USER CODE BEGIN PFP */

/* USER CODE END PFP */



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
HAL_Init();

SystemClock_Config();

RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // GPIOC Enable
RCC->APB1ENR |= RCC_APB1ENR_USART3EN; // USART3 clock Enable	

GPIO_InitTypeDef initStr = {GPIO_PIN_10 | GPIO_PIN_11,
GPIO_MODE_AF_PP,
GPIO_SPEED_FREQ_LOW,
GPIO_NOPULL};
	
GPIO_InitTypeDef initStr2 = {GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9,
GPIO_MODE_OUTPUT_PP,
GPIO_SPEED_FREQ_LOW,
GPIO_NOPULL};
	
HAL_GPIO_Init(GPIOC, &initStr); // Initialize pins PB10, PB11
HAL_GPIO_Init(GPIOC, &initStr2); // Initialize pin PC6, PC7, PC8, PC9

	
GPIOC->AFR[1] |= (1 << 8);    //Set alternate functions for USART3
GPIOC->AFR[1] &= ~(1 << 9);	
GPIOC->AFR[1] &= ~(1 << 10);
GPIOC->AFR[1] &= ~(1 << 11);

GPIOC->AFR[1] |= (1 << 12); 
GPIOC->AFR[1] &= ~(1 << 13);
GPIOC->AFR[1] &= ~(1 << 14);
GPIOC->AFR[1] &= ~(1 << 15);
	

USART3->CR1 |= (1 << 0); // Enable USART 
USART3->CR1 |= (1 << 2); // Enable RE
USART3->CR1 |= (1 << 3); // Enable TE 	
USART3->CR1 |= (1 << 5); // Enable RXNE interrupt





USART3->BRR |= HAL_RCC_GetHCLKFreq() / 115200; // set baud rate: 115200



NVIC_EnableIRQ(USART3_4_IRQn); // Enable USART3
NVIC_SetPriority(USART3_4_IRQn,1); // Set the priority of USART3 interrupt
	
//1st checkoff

//while(1)
//{
//		
//		
//	if((USART3->ISR & USART_ISR_RXNE) != 0) // Ready to read the data
//	{
//		char c = USART3->RDR;
//		switch(c){
//			case 'r':
//				GPIOC->ODR ^= (GPIO_ODR_6);
//				break;


//			case 'b':
//				GPIOC->ODR ^= (GPIO_ODR_7);
//				break;


//			case 'o':
//				GPIOC->ODR ^= (GPIO_ODR_8);
//				break;


//			case 'g':
//				GPIOC->ODR ^= (GPIO_ODR_9);
//				break;


//			default:
//				TransmitStr("error\n");
//			}		
//}
	//}
TransmitStr("CMD?");
flag = 0;
while(1)
{
				
	if(flag == 1)
	{
		TransmitChar(currdata); // Display current data Characters
			
				 
			if(currdata== '0'){ //Turns Off the LED
	
				switch(lastdata){
						
					case 'r': //Red LED off
						GPIOC->ODR &= ~(1 << 6);
						TransmitStr("Red LED off\n");
						TransmitStr("CMD?\n");
						break;
						
						
					case 'b': //Blue LED off
						GPIOC->ODR &= ~(1 << 7);
						TransmitStr("Blue LED off\n");
						TransmitStr("CMD?\n");
						break;
						
						
					case 'o': //Orange LED off
						GPIOC->ODR &= ~(1 << 8);
						TransmitStr("Orange LED off\n");
						TransmitStr("CMD?\n");
						break;
						
						
					case 'g': //Green  LED off
						GPIOC->ODR &= ~(1 << 9);
						TransmitStr("Green  LED off\n");
						TransmitStr("CMD?\n");
						break;
						
						
					default: 
						TransmitStr("Error");
				}
					
			}
			else if(currdata== '1'){ //Turns On the LED
				
				switch(lastdata)
				{	
						
					case 'r': // Red LED on
						GPIOC->ODR |= (1 << 6);
						TransmitStr("Red LED on\n");
						TransmitStr("CMD?\n");
						break;
						
						
					case 'b': // Blue LED on
						GPIOC->ODR |= (1 << 7);
						TransmitStr("Blue LED on\n");
						TransmitStr("CMD?\n");
						break;
						
						
					case 'o': // Orange LED on
						GPIOC->ODR |= (1 << 8);
						TransmitStr("Orange LED on\n");
						TransmitStr("CMD?\n");
						break;
						
						
					case 'g': // Green LED on
						GPIOC->ODR |= (1 << 9);
						TransmitStr("Green LED on\n");
						TransmitStr("CMD?\n");
						break;
						
						
					default: 
						TransmitStr("Error");
				}
					
			}
				
			else if(currdata== '2'){ //Toggles the LED

			
				switch(lastdata)
				{	
						
					case 'r': // Red LED toggled
						GPIOC->ODR ^= (GPIO_ODR_6);
						TransmitStr("Red LED toggled\n");
						TransmitStr("CMD?\n");
						break;
						
						
					case 'b': // Blue LED toggled
						GPIOC->ODR ^= (GPIO_ODR_7);
						TransmitStr("Blue LED toggled\n");
						TransmitStr("CMD?\n");
						break;
						
						
					case 'o': // Orange LED toggled
						GPIOC->ODR ^= (GPIO_ODR_8);
						TransmitStr("Orange LED toggled\n");
						TransmitStr("CMD?\n");
						break;
						
						
					case 'g': // Green LED toggled
						GPIOC->ODR ^= (GPIO_ODR_9);
						TransmitStr("Green LED toggled\n");
						TransmitStr("CMD?\n");
						break;
						
						
					default: 
						TransmitStr("Error");
				}
					
			}
			else{ 
					if((currdata != 'r' 
							& currdata != 'g' 
							& currdata != 'o' 
							& currdata != 'g')){
						
					TransmitStr("Error");
					}
			}
		}
		flag = 0;
	}
}


/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void TransmitChar(char c)
{
	while (1)
  {
		if(USART3->ISR & USART_ISR_TXE) 	
		{
			USART3->TDR = c;
			break;
		}
  }
}
/**
 
*/
void TransmitStr(char* str)
{
	for (int i = 0; str[i] != '\0'; i++) {
			TransmitChar(str[i]);
	}
}

void USART3_4_IRQHandler(void)
{
	lastdata = currdata; //Store the current data into the lastdata
	currdata = USART3->RDR; // Read the current data
	flag = 1; 
	
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
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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