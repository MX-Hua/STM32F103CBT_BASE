/*
 * middle_printf.c
 *
 *  Created on: Mar 7, 2026
 *      Author: hea
 */
#include "middle_printf.h"
#include "main.h"
#include "usart.h"

#include "stdio.h"
#include <stdarg.h>


#define Printf_UART huart1

uint8_t UserTxBuffer[512];

void uart_printf(const char* format,...)
{
	va_list args;

	uint32_t length;

	va_start(args,format);

	length=vsnprintf((char *)UserTxBuffer,512,(char*)format,args);

	va_end(args);

	HAL_UART_Transmit(&Printf_UART, (uint8_t *) &UserTxBuffer, length, 0xffff);

}



/*以下的只能在keil软件中使用 而IDE不能使用*/
/*****************************************************
*function: 写字符文件函数
*param1: 输出的字符
*param2: 文件指针
*return: 输出字符的 ASCII 码
******************************************************/
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&Printf_UART, (uint8_t*)ch,1,10);
    return ch;
}
/*****************************************************
*function: 读字符文件函数
*param1: 文件指针
*return: 读取字符的 ASCII 码
******************************************************/
int fgetc(FILE *f)
{
    uint8_t ch = 0;
    HAL_UART_Receive(&Printf_UART, (uint8_t*)&ch, 1, 10);
    return (int)ch;
}
