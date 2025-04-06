#ifndef __BSP_PS2_H__
#define __BSP_PS2_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "bsp.h"

#define DI HAL_GPIO_ReadPin(PS2_DI_GPIO_Port, PS2_DI_Pin)

#define DO_H HAL_GPIO_WritePin(PS2_DO_GPIO_Port, PS2_DO_Pin, GPIO_PIN_SET)   // Command bit high 命令位高
#define DO_L HAL_GPIO_WritePin(PS2_DO_GPIO_Port, PS2_DO_Pin, GPIO_PIN_RESET) // Command bit low 命令位低

#define CS_H HAL_GPIO_WritePin(PS2_CS_GPIO_Port, PS2_CS_Pin, GPIO_PIN_SET)   // CS elevation CS拉高
#define CS_L HAL_GPIO_WritePin(PS2_CS_GPIO_Port, PS2_CS_Pin, GPIO_PIN_RESET) // CS pull down CS拉低

#define CLK_H HAL_GPIO_WritePin(PS2_CLK_GPIO_Port, PS2_CLK_Pin, GPIO_PIN_SET)   // Clock up 时钟拉高
#define CLK_L HAL_GPIO_WritePin(PS2_CLK_GPIO_Port, PS2_CLK_Pin, GPIO_PIN_RESET) // Clock down s时钟拉低

// These are our button constants
#define PSB_SELECT 1
#define PSB_L3 2
#define PSB_R3 3
#define PSB_START 4
#define PSB_PAD_UP 5
#define PSB_PAD_RIGHT 6
#define PSB_PAD_DOWN 7
#define PSB_PAD_LEFT 8
#define PSB_L2 9
#define PSB_R2 10
#define PSB_L1 11
#define PSB_R1 12
#define PSB_GREEN 13
#define PSB_RED 14
#define PSB_BLUE 15
#define PSB_PINK 16

#define PSB_TRIANGLE 13
#define PSB_CIRCLE 14
#define PSB_CROSS 15
#define PSB_SQUARE 16

// #define WHAMMY_BAR		8

// These are stick values
#define PSS_RX 5 // Right joystick X-axis data 右摇杆X轴数据
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8

    extern uint8_t Data[9];
    extern uint16_t MASK[16];
    extern uint16_t Handkey;

    void PS2_GPIO_Init(void);
    uint8_t PS2_RedLight(void);                         // Determine if it is in red light mode 判断是否为红灯模式
    void PS2_ReadData(void);                            // Reading handle data 读手柄数据
    void PS2_Cmd(uint8_t CMD);                          // Send commands to the handle 向手柄发送命令
    uint8_t PS2_DataKey(void);                          // Key value reading 按键值读取
    uint8_t PS2_AnologData(uint8_t button);             // Obtain an analog quantity of a joystick 得到一个摇杆的模拟量
    void PS2_ClearData(void);                           // Clear data buffer 清除数据缓冲区
    void PS2_Vibration(uint8_t motor1, uint8_t motor2); // Vibration setting motor1 0xFF on, others off, motor2 0x40~0xFF 振动设置motor1  0xFF开，其他关，motor2  0x40~0xFF

    void PS2_EnterConfing(void);     // Enter configuration 进入配置
    void PS2_TurnOnAnalogMode(void); // Send analog quantity 发送模拟量
    void PS2_VibrationMode(void);    // Vibration settings 振动设置
    void PS2_ExitConfing(void);      // Completing Configuration 完成配置
    void PS2_SetInit(void);          // Configuration initialization 配置初始化

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */
