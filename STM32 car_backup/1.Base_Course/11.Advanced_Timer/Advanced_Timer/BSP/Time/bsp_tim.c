#include "bsp_tim.h"

//计算占空比时的全局表变量
__IO uint16_t IC2Value;
__IO uint16_t IC1Value;
__IO float DutyCycle;
__IO float Frequency;

/* TIM1 init function */
// 定时器1初始化
void TIM1_PWM_Init(void)
{
	// 使能捕获/比较2中断请求
	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_2);
}


/* TIM3 init function */
// 定时器3初始化
void TIM3_PWM_Init(void)
{
  // Activate TIM3 encoder mode 启动tim3的pwm输出
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}



//高级定时器中断回调函数
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
        /* 获取输入捕获值 */
        IC1Value = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);
        IC2Value = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_2);
        if (IC1Value != 0)
        {
            /* 占空比计算 */
            DutyCycle = (float)((IC2Value+1) * 100) / (IC1Value+1);
            /* 频率计算 */
            Frequency = 72000000/72/(float)(IC1Value+1);
        }
        else
        {
            DutyCycle = 0;
            Frequency = 0;
        }

    }
}
