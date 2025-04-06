#ifndef __BSP_MPU6050_H__
#define __BSP_MPU6050_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"


#define  I2C_Direction_Transmitter      ((uint8_t)0x00)
#define  I2C_Direction_Receiver         ((uint8_t)0x01)

#define CLI()      __set_PRIMASK(1)
#define SEI()      __set_PRIMASK(0)

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

#define TRUE  0
#define FALSE -1
/*
#define MPU6050_READRATE			1000	//6050 read frequency 6050读取频率
#define MPU6050_READTIME			0.001	//6050 read interval 6050读取时间间隔
#define EE_6050_ACC_X_OFFSET_ADDR	0
#define EE_6050_ACC_Y_OFFSET_ADDR	1
#define EE_6050_ACC_Z_OFFSET_ADDR	2
#define EE_6050_GYRO_X_OFFSET_ADDR	3
#define EE_6050_GYRO_Y_OFFSET_ADDR	4
#define EE_6050_GYRO_Z_OFFSET_ADDR	5
*/
////0表示写
//#define	I2C_Direction_Transmitter   0
////１表示读
//#define	I2C_Direction_Receiver      1

bool i2cWriteBuffer_mpu(uint8_t addr_, uint8_t reg_, uint8_t len_, uint8_t *data);
bool i2cWrite_mpu(uint8_t addr_, uint8_t reg_, uint8_t data);
bool i2cRead_mpu(uint8_t addr_, uint8_t reg_, uint8_t len, uint8_t* buf);
void i2cInit_mpu(void);

uint16_t i2cGetErrorCounter_mpu(void);
//static void i2cUnstick_mpu(void);

int8_t i2cwrite_mpu(uint8_t addr, uint8_t reg, uint8_t len, uint8_t * data);
int8_t i2cread_mpu(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);


void MPU6050_GPIO_Init(void);

#ifdef __cplusplus
}
#endif
#endif

