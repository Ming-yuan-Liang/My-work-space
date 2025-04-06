


#include "bsp_spi_dma.h"

/*
 * 通过Dma发送数据
 * pBuffer:数据发送存储区
 * Size:数据大小
 *
 * Send data via DMA
 * pBuffer: data sending storage area
 * Size: data size
 * */

uint16_t SPI_Write_DMA(uint8_t *pTxData, uint16_t Size)
{
    SPI_DMA_Stop();
    uint16_t retval =  HAL_SPI_Transmit_DMA(&hspi2,pTxData,Size);
    return retval;
}
/*
 * 以DMA发送标志状态做判断
 *
 * Judgment based on DMA send flag status
 * */

void SPI_DMA_Stop(void)
{
	while(__HAL_DMA_GET_FLAG(&hdma_spi2_tx,DMA_FLAG_TC4));
	while (hspi2.State != HAL_SPI_STATE_READY);
}
/*
 * DMA发送、接收标志一起做判断
 *
 * DMA send and receive flags are judged together.
 * */

void SPI_DMA_Stop2(void)
{
	while(__HAL_DMA_GET_FLAG(&hdma_spi2_tx,DMA_FLAG_TC4));
	while(__HAL_DMA_GET_FLAG(&hdma_spi2_rx,DMA_FLAG_TC5));
	while (hspi2.State != HAL_SPI_STATE_READY);
}
