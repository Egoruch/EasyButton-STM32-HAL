/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define WKUP_Pin GPIO_PIN_0
#define WKUP_GPIO_Port GPIOA
#define WKUP_EXTI_IRQn EXTI0_IRQn
#define VIBRO_Pin GPIO_PIN_2
#define VIBRO_GPIO_Port GPIOA
#define CTR_BAT_VOL_Pin GPIO_PIN_3
#define CTR_BAT_VOL_GPIO_Port GPIOA
#define BAT_BOL_Pin GPIO_PIN_4
#define BAT_BOL_GPIO_Port GPIOA
#define OUT_VOL_Pin GPIO_PIN_0
#define OUT_VOL_GPIO_Port GPIOB
#define CURRENT_Pin GPIO_PIN_1
#define CURRENT_GPIO_Port GPIOB
#define SA2_BUT_Pin GPIO_PIN_12
#define SA2_BUT_GPIO_Port GPIOB
#define SA2_BUT_EXTI_IRQn EXTI15_10_IRQn
#define SA1_BUT_Pin GPIO_PIN_13
#define SA1_BUT_GPIO_Port GPIOB
#define SA1_BUT_EXTI_IRQn EXTI15_10_IRQn
#define IPS_BRIGHT_Pin GPIO_PIN_11
#define IPS_BRIGHT_GPIO_Port GPIOA
#define BOOST_Pin GPIO_PIN_15
#define BOOST_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_9
#define BUZZER_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* Enumerations BEGIN */

typedef enum ButtonName
{
	/* SET BUTTON'S NAMES ↓: */
	/*_____________________*/
	BUT_SA2,
	BUT_SA1,
	BUT_WKUP,
	/*_____________________*/

	BUT_QUANTITY /* ← DON'T TOUCH IT! (uses to count buttons) */
}butname_t;

/* Enumerations END */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
