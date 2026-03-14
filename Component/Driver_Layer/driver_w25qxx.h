/*
 * driver_wq25xx.h
 *
 *  Created on: 2026年3月14日
 *      Author: hea
 */

#ifndef DRIVER_LAYER_DRIVER_WQ25XX_H_
#define DRIVER_LAYER_DRIVER_WQ25XX_H_


#include "main.h"


#define FLASH_PAGESIZE	 256			  //W25Q64的页面大小
#define _Flash_ID	0xEF4018

#define NSS_PORT GPIOA
#define NSS_PIN GPIO_PIN_4
#define NSS_RCC_EN() __HAL_RCC_GPIOA_CLK_ENABLE()

#define NSS_HIGH() HAL_GPIO_WritePin(NSS_PORT, NSS_PIN, GPIO_PIN_SET)
#define NSS_LOW()  HAL_GPIO_WritePin(NSS_PORT, NSS_PIN, GPIO_PIN_RESET)


extern SPI_HandleTypeDef hspi1;

void SPI1_Init(void);
uint32_t SPI_FLASH_ReadID(void);
void SPI_FLASH_WaitForWriteEnd(void);
void SPI_FLASH_WriteEnable(void);

void SPI_FLASH_SectorErase(uint32_t SectorAddr);
void SPI_FLASH_PageWrite(uint8_t * pBuffer, uint32_t WriteAddr,uint16_t NumByteToWrite);
void SPI_FLASH_BufferWrite(uint8_t * pBuffer, uint32_t WriteAddr,uint16_t NumByteToWrite);
void SPI_FLASH_BufferRead(uint8_t * pBuffer, uint32_t  ReadAddr,uint16_t NumByteToWrite);
#endif /* DRIVER_LAYER_DRIVER_W25QXX_H_ */
