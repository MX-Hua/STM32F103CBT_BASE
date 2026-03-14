/*
 * driver_uid.c
 *
 *  Created on: Mar 7, 2026
 *      Author: hea
 */


#include "driver_uid.h"
#include "stm32f1xx_hal.h"

#define STM32F103_UID_ADDR 0x1FFFF7E8

void Get_HAL_UID(uint32_t *UID)
{
	UID[0]=HAL_GetUIDw0(); //低32位
	UID[1]=HAL_GetUIDw1(); //中32位
	UID[2]=HAL_GetUIDw2(); //高32位

}


void Read_UID(uint8_t *UID)
{
	volatile uint32_t *uid_addr=(volatile uint32_t*)STM32F103_UID_ADDR;

	//读取32位数据并才拆分为字节
	UID[3]=(uid_addr[0]>>0)&0xFF;//低字节
	UID[2]=(uid_addr[0]>>8)&0xFF;
	UID[1]=(uid_addr[0]>>16)&0xFF;
	UID[0]=(uid_addr[0]>>24)&0xFF;


	UID[7]=(uid_addr[1]>>0)&0xFF;//中字节
	UID[6]=(uid_addr[1]>>8)&0xFF;
	UID[5]=(uid_addr[1]>>16)&0xFF;
	UID[4]=(uid_addr[1]>>24)&0xFF;


	UID[11]=(uid_addr[2]>>0)&0xFF;//高字节
	UID[10]=(uid_addr[2]>>8)&0xFF;
	UID[9]=(uid_addr[2]>>16)&0xFF;
	UID[8]=(uid_addr[2]>>24)&0xFF;


}
