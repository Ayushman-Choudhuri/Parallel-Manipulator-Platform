/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f1xx_hal.h"
#include "tim.h"
#include "steppermotorcontrol.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

	MotorActuateTest();


	/*Hardware level control of motor direction pins and motor timers*/

	for(uint8_t motor_index = 1 ; motor_index <=6 ; motor_index ++ )
	{
		switch(motor_index)
		{
			case 1: switch(MotorState[motor_index -1])
					{
						case HIGH: switch(MotorHighStateSetFlag[motor_index -1])
									{
									   case LOW: HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
									   	   	   	 MotorHighStateSetFlag[motor_index -1] = HIGH;
									   			 break;

									   case HIGH: break;

									   default: break ;
									}

									switch(MotorDirection[motor_index-1])
									{
										case ANGLE_UP:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
													    break;

										case ANGLE_DOWN:HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
														break;

										case ANGLE_HOLD:break;

										default : break;
									}

									break;

						case LOW : HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
								   break;

						default:  break;
					}

			case 2: switch(MotorState[motor_index -1])
					{
						case HIGH: switch(MotorHighStateSetFlag[motor_index -1])
									{
									   case LOW: HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
									   			 MotorHighStateSetFlag[motor_index -1] = HIGH;
									   			 break;

									   case HIGH: break;

									   default: break ;
									}

									switch(MotorDirection[motor_index-1])
									{
										case ANGLE_UP:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);

														break;

										case ANGLE_DOWN: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
														break;

										case ANGLE_HOLD:break;

										default : break;
									}

									break;

						case LOW : HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
								   break;

						default: break;
					}

			case 3: switch(MotorState[motor_index -1])
					{
						case HIGH: switch(MotorHighStateSetFlag[motor_index -1])
									{
									   case LOW: HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
									   			 MotorHighStateSetFlag[motor_index -1] = HIGH;
									   			 break;

									   case HIGH: break;

									   default: break ;
									}

									switch(MotorDirection[motor_index-1])
									{
										case ANGLE_UP:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

														break;

										case ANGLE_DOWN:HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
														break;

										case ANGLE_HOLD:break;

										default : break;
									}


									break;

						case LOW : HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
								   break;

						default: break;
					}

			case 4: switch(MotorState[motor_index -1])
					{
						case HIGH: switch(MotorHighStateSetFlag[motor_index -1])
									{
									   case LOW: HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
									   			 MotorHighStateSetFlag[motor_index -1] = HIGH;
									   			 break;

									   case HIGH: break;

									   default: break ;
									}

									switch(MotorDirection[motor_index-1])
									{
										case ANGLE_UP:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);

														break;

										case ANGLE_DOWN: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
														break;

										case ANGLE_HOLD:break;

										default : break;
									}
									break;

						case LOW : HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
								   break;

						default: break;
					}

			case 5: switch(MotorState[motor_index -1])
					{
						case HIGH: switch(MotorHighStateSetFlag[motor_index -1])
									{
									   case LOW: HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
									   			 MotorHighStateSetFlag[motor_index -1] = HIGH;
									   			 break;

									   case HIGH: break;

									   default: break ;
									}

									switch(MotorDirection[motor_index-1])
									{
										case ANGLE_UP:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);

														break;

										case ANGLE_DOWN: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
														break;

										case ANGLE_HOLD:break;

										default : break;
									}
									break;

						case LOW : HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
								   break;

						default: break;
					}

			case 6: switch(MotorState[motor_index -1])
					{
						case HIGH: switch(MotorHighStateSetFlag[motor_index -1])
									{
									   case LOW: HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
									   			 MotorHighStateSetFlag[motor_index -1] = HIGH;
									   			 break;

									   case HIGH: break;

									   default: break ;
									}

									switch(MotorDirection[motor_index-1])
									{
										case ANGLE_UP:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

														break;

										case ANGLE_DOWN: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
														break;

										case ANGLE_HOLD:break;

										default : break;
									}

									break;

						case LOW : HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
								   break;

						default: break;
					}



		}
	}











//	for (uint8_t motor_index = 1; motor_index <=6 ; motor_index ++)
//	{
//		switch(MotorState[motor_index-1])
//		{
//			case HIGH: switch(motor_index)
//					  {
//						case 1: /*Direction Control of Motor 1*/
//
//								switch(MotorDirection[motor_index-1])
//								{
//									case ANGLE_UP:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
//												    break;
//
//									case ANGLE_DOWN:HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
//													break;
//
//									case ANGLE_HOLD:break;
//
//									default : break;
//								}
//
//								break;
//
//						case 2: /*Direction Control of Motor 2*/
//								switch(MotorDirection[motor_index-1])
//								{
//									case ANGLE_UP:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
//
//													break;
//
//									case ANGLE_DOWN: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
//													break;
//
//									case ANGLE_HOLD:break;
//
//									default : break;
//								}
//
//								break;
//						case 3:/*Direction Control of Motor 3*/
//								switch(MotorDirection[motor_index-1])
//								{
//									case ANGLE_UP:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//
//													break;
//
//									case ANGLE_DOWN:HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
//													break;
//
//									case ANGLE_HOLD:break;
//
//									default : break;
//								}
//
//
//								break;
//						case 4:/*Direction Control of Motor 4*/
//								switch(MotorDirection[motor_index-1])
//								{
//									case ANGLE_UP:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
//
//													break;
//
//									case ANGLE_DOWN: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
//													break;
//
//									case ANGLE_HOLD:break;
//
//									default : break;
//								}
//								break;
//
//						case 5:/*Direction Control of Motor 5*/
//								switch(MotorDirection[motor_index-1])
//								{
//									case ANGLE_UP:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
//
//													break;
//
//									case ANGLE_DOWN: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
//													break;
//
//									case ANGLE_HOLD:break;
//
//									default : break;
//								}
//								break;
//
//						case 6:/*Direction Control of Motor 6*/
//								switch(MotorDirection[motor_index-1])
//								{
//									case ANGLE_UP:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
//
//													break;
//
//									case ANGLE_DOWN: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
//													break;
//
//									case ANGLE_HOLD:break;
//
//									default : break;
//								}
//
//								break;
//
//						default : break;
//					  }
//					   break;
//
//			case LOW: switch(motor_index)
//					  {
//						case 1: HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
//								break;
//
//						case 2: HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
//								break;
//
//						case 3: HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
//								break;
//
//						case 4: HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
//								break;
//
//						case 5:HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
//
//								break;
//
//						case 6:
//								HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
//								break;
//
//						default : break;
//					  }
//
//					  break;
//
//			default : break;
//		}
//
//
//	}



  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */

  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */

  /* USER CODE END EXTI1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line2 interrupt.
  */
void EXTI2_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_IRQn 0 */

  /* USER CODE END EXTI2_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  /* USER CODE BEGIN EXTI2_IRQn 1 */

  /* USER CODE END EXTI2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
