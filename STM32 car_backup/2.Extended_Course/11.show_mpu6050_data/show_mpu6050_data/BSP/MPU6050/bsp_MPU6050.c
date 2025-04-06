#include "bsp_MPU6050.h"

#define SCL_H GPIOB->BSRR = GPIO_PIN_10
#define SCL_L GPIOB->BRR = GPIO_PIN_10

#define SDA_H GPIOB->BSRR = GPIO_PIN_11
#define SDA_L GPIOB->BRR = GPIO_PIN_11

#define SCL_read GPIOB->IDR &GPIO_PIN_10
#define SDA_read GPIOB->IDR &GPIO_PIN_11

// 函数功能:软件i2c延迟函数
// 传递参数:无
// Function function: software i2c delay function
// Pass parameters: None
static void I2C_delay(void)
{
    volatile int i = 7;
    while (i)
        i--;
}

// 初始化mpu的设备地址引脚 AD0=0:0x68(本工程选择)  AD0=1:0x69
// Initialize the device address pin AD0 of mpu=0:0x68 (selected for this project) AD0=1:0x69
void MPU6050_AD0_Init(void)
{
    HAL_GPIO_WritePin(MPU6050_AD0_GPIO_Port, MPU6050_AD0_Pin, GPIO_PIN_RESET);
}

void MPU6050_GPIO_Init(void)
{
    // AD0引脚初始化
    // 其它引脚配置在gpio.c里面，使用软件i2c
    // AD0 pin initialization
    // Other pins are configured in gpio. c using software i2c
    MPU6050_AD0_Init();
}

// 函数功能:i2c开始
// Function function: i2c start function
static bool I2C_Start(void)
{
    SDA_H;
    SCL_H;
    I2C_delay();
    if (!(SDA_read))
        return false;
    SDA_L;
    I2C_delay();
    if (SDA_read)
        return false;
    SDA_L;
    I2C_delay();
    return true;
}

// 函数功能:i2c停止
// Function function: i2c stop function
static void I2C_Stop(void)
{
    SCL_L;
    I2C_delay();
    SDA_L;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SDA_H;
    I2C_delay();
}

// 函数功能:i2c应答
// Function function: I2c response function
static void I2C_Ack(void)
{
    SCL_L;
    I2C_delay();
    SDA_L;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
    I2C_delay();
}

// 函数功能:i2c非应答
// Function function: i2c non responsive
static void I2C_NoAck(void)
{
    SCL_L;
    I2C_delay();
    SDA_H;
    I2C_delay();
    SCL_H;
    I2C_delay();
    SCL_L;
    I2C_delay();
}

// 函数功能:等待i2c应答
// Function function: Wait for i2c response
static bool I2C_WaitAck(void)
{
    SCL_L;
    I2C_delay();
    SDA_H;
    I2C_delay();
    SCL_H;
    I2C_delay();
    if (SDA_read)
    {
        SCL_L;
        return false;
    }
    SCL_L;
    return true;
}

// 函数功能:i2c发送一个字节
// 传入参数:byte:1个byte的数据
// Function function: i2c sends a byte
// Incoming parameter: byte: 1 byte of data
static void I2C_SendByte(uint8_t byte)
{
    uint8_t i = 8;
    while (i--)
    {
        SCL_L;
        I2C_delay();
        if (byte & 0x80)
            SDA_H;
        else
            SDA_L;
        byte <<= 1;
        I2C_delay();
        SCL_H;
        I2C_delay();
    }
    SCL_L;
}

// 函数功能:i2c接收数据
// Function function: i2c receiving data
static uint8_t I2C_ReceiveByte(void)
{
    uint8_t i = 8;
    uint8_t byte = 0;

    SDA_H;
    while (i--)
    {
        byte <<= 1;
        SCL_L;
        I2C_delay();
        SCL_H;
        I2C_delay();
        if (SDA_read)
        {
            byte |= 0x01;
        }
    }
    SCL_L;
    return byte;
}

// 函数功能：i2c发送数据函数
// addr:i2c设备地址
// reg:寄存器
// len:数据长度
// data:数据首地址
// Function function: i2c send data function
// Addr: i2c device address
// Reg: Register
// Len: data length
// Data: data header address
bool i2cWriteBuffer_mpu(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data)
{
    int i;
    if (!I2C_Start())
        return false;
    I2C_SendByte(addr << 1 | I2C_Direction_Transmitter);
    if (!I2C_WaitAck())
    {
        I2C_Stop();
        return false;
    }
    I2C_SendByte(reg);
    I2C_WaitAck();
    for (i = 0; i < len; i++)
    {
        I2C_SendByte(data[i]);
        if (!I2C_WaitAck())
        {
            I2C_Stop();
            return false;
        }
    }
    I2C_Stop();
    return true;
}
/////////////////////////////////////////////////////////////////////////////////
int8_t i2cwrite_mpu(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data)
{
    if (i2cWriteBuffer_mpu(addr, reg, len, data))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    // return FALSE;
}
int8_t i2cread_mpu(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    if (i2cRead_mpu(addr, reg, len, buf))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    // return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
bool i2cWrite_mpu(uint8_t addr, uint8_t reg, uint8_t data)
{
    if (!I2C_Start())
        return false;
    I2C_SendByte(addr << 1 | I2C_Direction_Transmitter);
    if (!I2C_WaitAck())
    {
        I2C_Stop();
        return false;
    }
    I2C_SendByte(reg);
    I2C_WaitAck();
    I2C_SendByte(data);
    I2C_WaitAck();
    I2C_Stop();
    return true;
}

// 函数功能：i2c读取数据函数
// addr:i2c设备地址
// reg:寄存器
// len:数据长度
// buf:保留数据首地址
// Function Function: i2c Read Data Function
// Addr: i2c device address
// Reg: Register
// Len: data length
// Buf: Preserve the first address of the data
bool i2cRead_mpu(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    if (!I2C_Start())
        return false;
    I2C_SendByte(addr << 1 | I2C_Direction_Transmitter);
    if (!I2C_WaitAck())
    {
        I2C_Stop();
        return false;
    }
    I2C_SendByte(reg);
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(addr << 1 | I2C_Direction_Receiver);
    I2C_WaitAck();
    while (len)
    {
        *buf = I2C_ReceiveByte();
        if (len == 1)
            I2C_NoAck();
        else
            I2C_Ack();
        buf++;
        len--;
    }
    I2C_Stop();
    return true;
}

uint16_t i2cGetErrorCounter_mpu(void)
{
    // TODO maybe fix this, but since this is test code, doesn't matter.
    return 0;
}
