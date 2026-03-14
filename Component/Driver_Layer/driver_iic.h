/*
 * driver_iic.h
 *
 *  Created on: Mar 11, 2026
 *      Author: hea
 */

#ifndef DRIVER_LAYER_DRIVER_IIC_H_
#define DRIVER_LAYER_DRIVER_IIC_H_

#include "stm32f1xx_hal.h"
#include "driver_delay.h"

#define iic_delay()  delay_us(500)

#define IIC_H 1
#define IIC_L 0

#define SCL_PORT GPIOB
#define SCL_PIN GPIO_PIN_6

#define SDA_PORT GPIOB
#define SDA_PIN GPIO_PIN_7


#define  RCC_IIC_PIN_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()

#define IIC_SCL(x) x?HAL_GPIO_WritePin(SCL_PORT, SCL_PIN, GPIO_PIN_SET):HAL_GPIO_WritePin(SCL_PORT, SCL_PIN, GPIO_PIN_RESET)
#define IIC_SDA(x) x?HAL_GPIO_WritePin(SDA_PORT, SDA_PIN, GPIO_PIN_SET):HAL_GPIO_WritePin(SDA_PORT, SDA_PIN, GPIO_PIN_RESET)
#define IIC_READ_SDA() HAL_GPIO_ReadPin(SDA_PORT, SDA_PIN)

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);

void I2C_SDA_OUT(void);
void I2C_SDA_IN(void);

void I2C_ACK(void);
void I2C_NACK(void);

uint8_t I2C_GetACK(void);


uint8_t I2C_SendByte(uint8_t data);
uint8_t I2C_ReadByte(uint8_t ack);


#endif /* DRIVER_LAYER_DRIVER_IIC_H_ */
