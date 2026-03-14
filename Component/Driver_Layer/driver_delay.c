/*
 * driver_delay.c
 *
 *  Created on: Mar 7, 2026
 *      Author: hea
 */


#include "driver_delay.h"

#include "tim.h"


#define DelayHtim htim3
//微秒延迟
void delay_us(uint16_t us)
{

	uint32_t counter=0;

	__HAL_TIM_SET_AUTORELOAD(&DelayHtim,us);
	__HAL_TIM_SET_COUNTER(&DelayHtim,counter);

	HAL_TIM_Base_Start(&DelayHtim);

	while(counter!=us)
	{
		counter=__HAL_TIM_GET_COUNTER(&DelayHtim);
	}

	HAL_TIM_Base_Stop(&DelayHtim);

}


//毫秒延迟
void delay_ms(uint32_t ms)
{
	while(ms--)
	{
		delay_us(1000);
	}
}
