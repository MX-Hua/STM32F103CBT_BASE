/*
 * driver_ringbuffer.h
 *
 *  Created on: Mar 10, 2026
 *      Author: hea
 */

#ifndef DRIVER_LAYER_DRIVER_RINGBUFFER_H_
#define DRIVER_LAYER_DRIVER_RINGBUFFER_H_

#include "stdint.h"

typedef struct
{
	uint8_t *fifo;
	uint16_t pw;
	uint16_t pr;
	uint16_t buf_size;


} RingBuffer,*ptRingBuffer;


extern RingBuffer USERRxDataBuffer1;
extern RingBuffer USERRxDataBuffer2;

int Driver_Buffer_Init(ptRingBuffer buffer, uint16_t size);

int Driver_Buffer_Write(ptRingBuffer buffer, const uint8_t data);

int Driver_Buffer_WriteBytes(ptRingBuffer buffer, const uint8_t *data_stream, uint8_t len);

int Driver_Buffer_Read(ptRingBuffer buffer, uint8_t *data);

int Driver_Buffer_ReadBytes(ptRingBuffer buffer, uint8_t *data_stream, uint8_t len);

int Driver_Buffer_Clean(ptRingBuffer buffer);

int Driver_Buffer_RefreshData(ptRingBuffer buffer, uint8_t *data_stream);

#endif /* DRIVER_LAYER_DRIVER_RINGBUFFER_H_ */
