/*
 * driver_interior_flash.h
 *
 *  Created on: Mar 9, 2026
 *      Author: hea
 */



#ifndef DRIVE_LAYER_DRIVER_INTERIOR_FLASH_H_
#define DRIVE_LAYER_DRIVER_INTERIOR_FLASH_H_


#include "stdint.h"
#include "main.h"
#define USER_PAGE_ADDR  0x0801FC00  // 最后1页起始地址（页对齐！）
#define PAGE_SIZE       0x400       // 1024 bytes

void Driver_Read_Flash_Word(uint32_t startAddr, uint32_t *pdata, uint32_t length);
HAL_StatusTypeDef Driver_Flash_Write_Safe_Word(uint32_t addr, uint32_t *data, uint32_t len_words);

void Driver_write_flash_HalfWord(uint32_t addr, uint16_t *data, uint16_t len);
void Driver_read_flash_HalfWord(uint32_t addr, uint16_t *buf, uint16_t len);

#endif /* DRIVE_LAYER_DRIVER_INTERIOR_FLASH_H_ */

