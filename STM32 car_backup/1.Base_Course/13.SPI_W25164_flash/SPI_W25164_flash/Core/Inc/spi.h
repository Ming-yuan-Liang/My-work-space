/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN Private defines */
#define FLASH_SPI_CS_PIN_Pin 			GPIO_PIN_12
#define FLASH_SPI_CS_PIN_GPIO_Port		GPIOB
#define FLASH_SPI_SCK_PIN_Pin 			GPIO_PIN_13
#define FLASH_SPI_SCK_PIN_GPIO_Port		GPIOB
#define FLASH_SPI_MISO_PIN_Pin 			GPIO_PIN_14
#define FLASH_SPI_MISO_PIN_GPIO_Port 	GPIOB
#define FLASH_SPI_MOSI_PIN_Pin 			GPIO_PIN_15
#define FLASH_SPI_MOSI_PIN_GPIO_Port	GPIOB

#define CS_LOW							HAL_GPIO_WritePin(FLASH_SPI_CS_PIN_GPIO_Port, FLASH_SPI_CS_PIN_Pin, GPIO_PIN_RESET);
#define CS_HIGH                         HAL_GPIO_WritePin(FLASH_SPI_CS_PIN_GPIO_Port, FLASH_SPI_CS_PIN_Pin, GPIO_PIN_SET);

/* USER CODE END Private defines */

void MX_SPI2_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
