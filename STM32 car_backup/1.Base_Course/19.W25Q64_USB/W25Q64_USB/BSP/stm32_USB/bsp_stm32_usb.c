#include "bsp_stm32_usb.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

// USB接口状态初始化
// USB interface status initialization
void USB_Init(void)
{
    //	USBD_DeInit(&hUsbDeviceFS);

    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOA_CLK_ENABLE();                          /*Enable PORTA clock 使能PORTA时钟 */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET); /* PA11 = 0 */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET); /* PA12 = 0 */

    /* PA11 pin mode setting, push pull output PA11引脚模式设置,推挽输出 */
    GPIO_Initure.Pin = GPIO_PIN_11;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initure.Pull = GPIO_PULLDOWN;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);

    /* PA12 pin mode setting, push pull output PA12引脚模式设置,推挽输出 */
    GPIO_Initure.Pin = GPIO_PIN_12;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initure.Pull = GPIO_PULLDOWN;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);

    HAL_Delay(2);
}

// 检测usb连接的情况
// Detecting USB connection
void VCP_Status(void)
{
    static uint8_t old_status = 0;

    if (hUsbDeviceFS.dev_state != old_status)
    {
        if (hUsbDeviceFS.dev_state == USBD_STATE_CONFIGURED)
        {
            OLED_Draw_Line("USB connect     ", 2, false, true); // Successfully connected 连接成功
        }
        else if (hUsbDeviceFS.dev_state == USBD_STATE_SUSPENDED)
        {
            OLED_Draw_Line("USB disconnect", 2, false, true); // Connection disconnected 连接断开
        }
        old_status = hUsbDeviceFS.dev_state;
    }
}
