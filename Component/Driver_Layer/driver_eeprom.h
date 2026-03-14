/*
 * driver_eeprom.h
 *
 *  Created on: Mar 10, 2026
 *      Author: hea
 */

#ifndef DRIVER_LAYER_DRIVER_EEPROM_H_
#define DRIVER_LAYER_DRIVER_EEPROM_H_

#include "stm32f1xx_hal.h"

#define EEPROM_DEV_ADDR             (0xA0)
#define EEPROM_WR                   (0x00)
#define EEPROM_RD                   (0x01)

#define EEPROM_WORD_ADDR_SIZE 8

/*
 *  函数名：uint8_t EEPROM_WriteByte(uint16_t addr, uint8_t data)
 *  输入参数：addr -> 写一个字节的EEPROM初始地址
 *            data -> 要写的数据
 *  输出参数：无
 *  返回值：无
 *  函数作用：EEPROM写一个字节
*/
extern void EEPROM_WriteByte(uint16_t addr, uint8_t data);

/*
 *  函数名：uint8_t EEPROM_ReadByte(uint16_t addr, uint8_t *pdata)
 *  输入参数：addr -> 读一个字节的EEPROM初始地址
 *            data -> 要读的数据指针
 *  输出参数：无
 *  返回值：无
 *  函数作用：EEPROM读一个字节
*/
extern void EEPROM_ReadByte(uint16_t addr, uint8_t *pdata);

/*
 *  函数名：void EEPROM_Write_NBytes(uint16_t addr, uint8_t *pdata, uint16_t sz)
 *  输入参数：addr -> 写一个字节的EEPROM初始地址
 *            data -> 要写的数据指针
 *            sz   -> 要写的字节个数
 *  输出参数：无
 *  返回值：无
 *  函数作用：EEPROM写N个字节
*/
extern void EEPROM_Write_NBytes(uint16_t addr, uint8_t *pdata, uint16_t sz);

/*
 *  函数名：void EEPROM_Read_NBytes(uint16_t addr, uint8_t *pdata, uint16_t sz)
 *  输入参数：addr -> 读一个字节的EEPROM初始地址
 *            data -> 要读的数据指针
 *            sz   -> 要读的字节个数
 *  输出参数：无
 *  返回值：无
 *  函数作用：EEPROM读N个字节
*/
extern void EEPROM_Read_NBytes(uint16_t addr, uint8_t *pdata, uint16_t sz);


#endif /* DRIVER_LAYER_DRIVER_EEPROM_H_ */
