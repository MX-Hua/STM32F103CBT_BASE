/*
 * driver_led.c
 *
 *  Created on: Mar 7, 2026
 *      Author: hea
 */

#include "driver_led.h"



uint8_t led_status=0;

void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct={0};

	LED_CLK_ENABLE();

	GPIO_InitStruct.Pin = LED_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_GPIOx, &GPIO_InitStruct);

	lED_Switch(OFF);

}


void Led_Toggle(void)
{

	if(led_status==0)
	{
		//开灯
		lED_Switch(ON);
		led_status=1;


	}
	else
	{
		//关灯
		lED_Switch(OFF);
		led_status=0;

	}


}
