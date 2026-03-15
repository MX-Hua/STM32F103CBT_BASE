/*
 * driver_rs485.c
 *
 *  Created on: 2026年3月15日
 *      Author: hea
 */


#include "driver_rs485.h"
#include "stdarg.h"
#include "stdio.h"


void RS485_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct={0};

	RS485_DE_CLK_EN();

	GPIO_InitStruct.Pin = RS485_DE_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RS485_DE_GPIO_PORT, &GPIO_InitStruct);

}

/*****************  发送指定长度的字符串 **********************/
void RS485_SendStr_length(uint8_t *str,uint32_t strlen)
{

	RS485_TX_EN(); //设置当前位 发送模式

	HAL_UART_Transmit(&RS485_HUART,str,strlen,10);

	RS485_RX_EN(); //设置当前位 接受模式
}



uint8_t RS485_UserTxBuffer[256];
void RS485_Printf(const char *format, ...)
{
	va_list args;
	uint32_t length;

	va_start(args, format);
	length = vsnprintf((char *)RS485_UserTxBuffer, 512, (char *)format, args);
	va_end(args);
	RS485_SendStr_length(RS485_UserTxBuffer,length);
}
