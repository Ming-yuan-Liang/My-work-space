

#ifndef W25Q64_BSP_SPI_DMA_H_
#define W25Q64_BSP_SPI_DMA_H_

#include "bsp.h"


#define CS_LOW	 HAL_GPIO_WritePin(FLASH_SPI_CS_PIN_GPIO_Port, FLASH_SPI_CS_PIN_Pin, GPIO_PIN_RESET);
#define CS_HIGH  HAL_GPIO_WritePin(FLASH_SPI_CS_PIN_GPIO_Port, FLASH_SPI_CS_PIN_Pin, GPIO_PIN_SET);



void SPI_DMA_Stop(void);
uint16_t SPI_Write_DMA(uint8_t *pTxData, uint16_t Size);
void SPI_DMA_Stop2(void);


#endif /* W25Q64_BSP_SPI_DMA_H_ */
