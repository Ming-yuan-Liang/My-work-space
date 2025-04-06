/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId myTask_RGBHandle;
osThreadId myTask_BeepHandle;
osThreadId myTask_KEYHandle;
osThreadId myTask_LEDHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartTask_RGB(void const * argument);
void StartTask_Beep(void const * argument);
void StartTask_KEY(void const * argument);
void StartTask_LED(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of myTask_RGB */
  osThreadDef(myTask_RGB, StartTask_RGB, osPriorityNormal, 0, 128);
  myTask_RGBHandle = osThreadCreate(osThread(myTask_RGB), NULL);

  /* definition and creation of myTask_Beep */
  osThreadDef(myTask_Beep, StartTask_Beep, osPriorityIdle, 0, 128);
  myTask_BeepHandle = osThreadCreate(osThread(myTask_Beep), NULL);

  /* definition and creation of myTask_KEY */
  osThreadDef(myTask_KEY, StartTask_KEY, osPriorityIdle, 0, 128);
  myTask_KEYHandle = osThreadCreate(osThread(myTask_KEY), NULL);

  /* definition and creation of myTask_LED */
  osThreadDef(myTask_LED, StartTask_LED, osPriorityIdle, 0, 128);
  myTask_LEDHandle = osThreadCreate(osThread(myTask_LED), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartTask_RGB */
/**
* @brief Function implementing the myTask_RGB thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_RGB */
void StartTask_RGB(void const * argument)
{
  /* USER CODE BEGIN StartTask_RGB */
	/* Infinite loop */
	Task_Entity_RGB();
  /* USER CODE END StartTask_RGB */
}

/* USER CODE BEGIN Header_StartTask_Beep */
/**
* @brief Function implementing the myTask_Beep thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_Beep */
void StartTask_Beep(void const * argument)
{
  /* USER CODE BEGIN StartTask_Beep */
	/* Infinite loop */
	Task_Entity_BEEP();
  /* USER CODE END StartTask_Beep */
}

/* USER CODE BEGIN Header_StartTask_KEY */
/**
* @brief Function implementing the myTask_KEY thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_KEY */
void StartTask_KEY(void const * argument)
{
  /* USER CODE BEGIN StartTask_KEY */
	/* Infinite loop */
	Task_Entity_KEY();
  /* USER CODE END StartTask_KEY */
}

/* USER CODE BEGIN Header_StartTask_LED */
/**
* @brief Function implementing the myTask_LED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_LED */
void StartTask_LED(void const * argument)
{
  /* USER CODE BEGIN StartTask_LED */
	/* Infinite loop */
	Task_Entity_LED();
  /* USER CODE END StartTask_LED */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

