#include "bsp_MPU6050.h"

 //MPU IIC 延时函数
void MPU_IIC_Delay(void)
{
	delay_us(2);
}


//产生IIC起始信号
//Generate IIC start signal
void MPU_IIC_Start(void)
{
	MPU_SDA_OUT();     //sda线输出 SDA line output
	MPU_IIC_SDA=1;
	MPU_IIC_SCL=1;
	MPU_IIC_Delay();
 	MPU_IIC_SDA=0;//START:when CLK is high,DATA change form high to low
	MPU_IIC_Delay();
	MPU_IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 Clamp the I2C bus and prepare to send or receive data
}
//产生IIC停止信号
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT();//sda线输出
	MPU_IIC_SCL=0;
	MPU_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	MPU_IIC_Delay();
	MPU_IIC_SCL=1;
	MPU_IIC_SDA=1;//发送I2C总线结束信号
	MPU_IIC_Delay();
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
//Waiting for the response signal to arrive
//Return value: 1, failed to receive response
//0, received response successfully
u8 MPU_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	MPU_SDA_IN();      //SDA设置为输入 SDA set as input
	MPU_IIC_SDA=1;MPU_IIC_Delay();
	MPU_IIC_SCL=1;MPU_IIC_Delay();
	while(MPU_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MPU_IIC_Stop();
			return 1;
		}
	}
	MPU_IIC_SCL=0;//时钟输出0 Clock output 0
	return 0;
}
//产生ACK应答 Generate ACK response
void MPU_IIC_Ack(void)
{
	MPU_IIC_SCL=0;
	MPU_SDA_OUT();
	MPU_IIC_SDA=0;
	MPU_IIC_Delay();
	MPU_IIC_SCL=1;
	MPU_IIC_Delay();
	MPU_IIC_SCL=0;
}
//不产生ACK应答 No ACK response generated
void MPU_IIC_NAck(void)
{
	MPU_IIC_SCL=0;
	MPU_SDA_OUT();
	MPU_IIC_SDA=1;
	MPU_IIC_Delay();
	MPU_IIC_SCL=1;
	MPU_IIC_Delay();
	MPU_IIC_SCL=0;
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
//IIC sends a byte
//Returns whether the slave has responded or not
//1. There is a response
//0, no response
void MPU_IIC_Send_Byte(u8 txd)
{
    u8 t;
	MPU_SDA_OUT();
    MPU_IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {
        MPU_IIC_SDA=(txd&0x80)>>7;
        txd<<=1;
		    MPU_IIC_SCL=1;
		    MPU_IIC_Delay();
		    MPU_IIC_SCL=0;
		    MPU_IIC_Delay();
    }
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
//Read 1 byte, when ack=1, send ACK, when ack=0, send nACK
u8 MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	MPU_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        MPU_IIC_SCL=0;
        MPU_IIC_Delay();
		MPU_IIC_SCL=1;
        receive<<=1;
        if(MPU_READ_SDA)receive++;
		MPU_IIC_Delay();
    }
    if (!ack)
        MPU_IIC_NAck();//发送nACK
    else
        MPU_IIC_Ack(); //发送ACK
    return receive;
}


























