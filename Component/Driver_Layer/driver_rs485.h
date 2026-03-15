/*
 * driver_rs485.h
 *
 *  Created on: 2026年3月15日
 *      Author: hea
 */

#ifndef DRIVER_LAYER_DRIVER_RS485_H_
#define DRIVER_LAYER_DRIVER_RS485_H_


#include "driver_delay.h"
#include "usart.h"



#define RS485_Delay(x) delay_ms(x)

#define RS485_DE_GPIO_PORT GPIOA
#define RS485_DE_GPIO_PIN GPIO_PIN_1
#define RS485_DE_CLK_EN() __HAL_RCC_GPIOA_CLK_ENABLE()
#define RS485_HUART huart2


/*控制收发引脚*/
//进入发送模式,必须要有延时等待485处理完数据  high
#define RS485_TX_EN() RS485_Delay(2);HAL_GPIO_WritePin(RS485_DE_GPIO_PORT,RS485_DE_GPIO_PIN,GPIO_PIN_SET);RS485_Delay(2);

//进入接收模式,必须要有延时等待485处理完数据 low
#define RS485_RX_EN() RS485_Delay(2);HAL_GPIO_WritePin(RS485_DE_GPIO_PORT,RS485_DE_GPIO_PIN,GPIO_PIN_RESET);RS485_Delay(2);


void RS485_Init(void);
void RS485_Printf(const char *format,...);



#endif /* DRIVER_LAYER_DRIVER_RS485_H_ */
