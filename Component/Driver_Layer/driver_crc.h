/*
 * driver_crc.h
 *
 *  Created on: Mar 7, 2026
 *      Author: hea
 */

#ifndef DRIVER_LAYER_DRIVER_CRC_H_
#define DRIVER_LAYER_DRIVER_CRC_H_

#include "stdint.h"
// CRC8参数配置（可修改）
#define CRC8_POLYNOMIAL     0x07    // x^8 + x^2 + x + 1
#define CRC8_INITIAL        0x00
#define CRC8_XOR_OUT        0x00


void Driver_CRC8_InitTable(void);
uint8_t Driver_CRC8_Calculate(uint8_t *, uint16_t );
uint8_t Driver_CRC8_CalculateFast(uint8_t *data, uint16_t length);

uint16_t Driver_CRC16_Modbus_Table_Fast(const uint8_t *data, uint32_t length);
uint16_t Driver_CRC16_Modbus_Calculate(const uint8_t *data, uint32_t length);

uint32_t Driver_CRC32_Table_Fast(const uint8_t *data, uint32_t length);

uint32_t Driver_CRC32_Calculate_Byte(const uint8_t *data, uint32_t length);

#endif /* DRIVER_LAYER_DRIVER_CRC_H_ */
