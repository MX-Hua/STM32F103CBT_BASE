/*
 * driver_led.h
 *
 *  Created on: Mar 7, 2026
 *      Author: hea
 */

#ifndef DRIVER_LAYER_DRIVER_LED_H_
#define DRIVER_LAYER_DRIVER_LED_H_

#include "main.h"

#define ON GPIO_PIN_SET
#define OFF GPIO_PIN_RESET

#define LED_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
#define LED_GPIOx GPIOC
#define LED_Pin  GPIO_PIN_13
#define lED_Switch(x) x?HAL_GPIO_WritePin(LED_GPIOx,LED_Pin,ON):HAL_GPIO_WritePin(LED_GPIOx,LED_Pin,OFF)

void Led_Init(void);
void Led_Toggle(void);

extern uint8_t led_status;

#endif
