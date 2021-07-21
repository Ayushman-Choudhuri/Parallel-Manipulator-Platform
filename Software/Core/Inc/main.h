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
#define LIMIT_SWITCH_3_Pin GPIO_PIN_1
#define LIMIT_SWITCH_3_GPIO_Port GPIOA
#define LIMIT_SWITCH_3_EXTI_IRQn EXTI1_IRQn
#define LIMIT_SWITCH_2_Pin GPIO_PIN_2
#define LIMIT_SWITCH_2_GPIO_Port GPIOA
#define LIMIT_SWITCH_2_EXTI_IRQn EXTI2_IRQn
#define MOTOR_3_DIR_Pin GPIO_PIN_5
#define MOTOR_3_DIR_GPIO_Port GPIOA
#define MOTOR_3_STEP_Pin GPIO_PIN_6
#define MOTOR_3_STEP_GPIO_Port GPIOA
#define LIMIT_SWITCH_1_Pin GPIO_PIN_7
#define LIMIT_SWITCH_1_GPIO_Port GPIOA
#define LIMIT_SWITCH_1_EXTI_IRQn EXTI9_5_IRQn
#define MOTOR_2_STEP_Pin GPIO_PIN_0
#define MOTOR_2_STEP_GPIO_Port GPIOB
#define MOTOR_1_STEP_Pin GPIO_PIN_1
#define MOTOR_1_STEP_GPIO_Port GPIOB
#define MOTOR_2_DIR_Pin GPIO_PIN_10
#define MOTOR_2_DIR_GPIO_Port GPIOB
#define MOTOR_1_DIR_Pin GPIO_PIN_11
#define MOTOR_1_DIR_GPIO_Port GPIOB
#define LIMIT_SWITCH_6_Pin GPIO_PIN_12
#define LIMIT_SWITCH_6_GPIO_Port GPIOB
#define LIMIT_SWITCH_6_EXTI_IRQn EXTI15_10_IRQn
#define LIMIT_SWITCH_5_Pin GPIO_PIN_13
#define LIMIT_SWITCH_5_GPIO_Port GPIOB
#define LIMIT_SWITCH_5_EXTI_IRQn EXTI15_10_IRQn
#define MOTOR_6_DIR_Pin GPIO_PIN_14
#define MOTOR_6_DIR_GPIO_Port GPIOB
#define MOTOR_6_STEP_Pin GPIO_PIN_8
#define MOTOR_6_STEP_GPIO_Port GPIOA
#define MOTOR_5_STEP_Pin GPIO_PIN_9
#define MOTOR_5_STEP_GPIO_Port GPIOA
#define MOTOR_4_STEP_Pin GPIO_PIN_10
#define MOTOR_4_STEP_GPIO_Port GPIOA
#define MOTOR_4_DIR_Pin GPIO_PIN_11
#define MOTOR_4_DIR_GPIO_Port GPIOA
#define MOTOR_5_DIR_Pin GPIO_PIN_15
#define MOTOR_5_DIR_GPIO_Port GPIOA
#define LIMIT_SWITCH_4_Pin GPIO_PIN_4
#define LIMIT_SWITCH_4_GPIO_Port GPIOB
#define LIMIT_SWITCH_4_EXTI_IRQn EXTI4_IRQn
#define MPU_9250_I2C_SCL_Pin GPIO_PIN_8
#define MPU_9250_I2C_SCL_GPIO_Port GPIOB
#define MPU_9250_I2C_SDA_Pin GPIO_PIN_9
#define MPU_9250_I2C_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
