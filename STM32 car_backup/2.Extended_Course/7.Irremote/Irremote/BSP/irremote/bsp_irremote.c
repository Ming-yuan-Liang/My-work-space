#include "bsp_irremote.h"

/** Configure pins as
 * Analog
 * Input
 * Output
 * EVENT_OUT
 * EXTI
 */

uint8_t g_hwjs_DATA = 0xFF;
uint8_t g_hwjs_DATA_old = 0xFF;

// 计算低电平的持续时间
uint16_t InfraredRecvLowTime(void)
{
    uint16_t time = 0;
    while (HAL_GPIO_ReadPin(Irremote_GPIO_Port, Irremote_Pin) == 0)
    {
        if (time >= 500)
            break;
        time += 1;
        Delay_US(17);
    }
    return time;
}
// 计算高电平的持续时间
uint16_t InfraredRecvHighTime(void)
{
    uint16_t time = 0;
    while (HAL_GPIO_ReadPin(Irremote_GPIO_Port, Irremote_Pin) == 1)
    {
        if (time >= 250)
            break;
        time += 1;
        Delay_US(17);
    }
    return time;
}

uint8_t InfraredDataRecv(void) // 获取红外遥控数据
{
    uint16_t time;
    uint8_t i, j;
    uint8_t data[4] = {0};
    // 获取引导码
    time = InfraredRecvLowTime();
    if (time < 400 || time >= 500)
        return Irremote_error;
    time = InfraredRecvHighTime();
    if (time < 150 || time > 250)
        return Irremote_error;
    // 获取数据
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 8; j++)
        {
            time = InfraredRecvLowTime();
            if (time < 20 || time > 35)
                return Irremote_error;
            time = InfraredRecvHighTime(); // 通过高电平的时间长短来判断数据0,1
            if (time < 35)                 // 数据0
            {
                data[i] <<= 1;
                data[i] |= 0x0;
            }
            else
            {
                data[i] <<= 1;
                data[i] |= 0x1;
            }
        }
    }
    return data[2];
}

// 中断回调函数 -只要按了按键会进来
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    UNUSED(GPIO_Pin);
    uint8_t data;
    data = InfraredDataRecv();

    if (data != Irremote_error)
    {
    	g_hwjs_DATA  = data;
    }

    //这是能触发长按的写法，但要确保中断是正常触发的
//    g_hwjs_DATA  = data;
//    if (g_hwjs_DATA != Irremote_error)
//       {
//
//           g_hwjs_DATA_old = g_hwjs_DATA;
//       }

    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);//清掉中断

}

void Print_Irrmote(void)
{
	if (g_hwjs_DATA != 0xFF)
	{
//		g_hwjs_DATA = g_hwjs_DATA_old; //这是能触发长按的写法，但要确保中断是正常触发的
		printf("irrmote key is :%X \r\n", g_hwjs_DATA);
		g_hwjs_DATA = 0xFF;
	}

}
