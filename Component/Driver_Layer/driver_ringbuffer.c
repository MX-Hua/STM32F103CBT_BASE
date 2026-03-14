/*
 * driver_ringbuffer.c
 *
 *  Created on: Mar 10, 2026
 *      Author: hea
 */
#include "driver_ringbuffer.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

RingBuffer USERRxDataBuffer1; //定义用户缓冲区
RingBuffer USERRxDataBuffer2;

/* 初始化环形缓冲区 */

int Driver_Buffer_Init(ptRingBuffer buffer,uint16_t size)
{
	if(buffer==NULL||size==0)
	{
		 return -1;//判断合法性
	}
	if(buffer->fifo=NULL) //判断内存大小是否是空
	{
		buffer->fifo=(uint8_t *)malloc(size);/* 动态分配内存 */
		if(buffer->fifo=NULL)
		{
			//printf("Malloc %d bytes failed.\r\n", size);
			return -1;
		}
	}
	buffer->pw = buffer->pr = 0;
	buffer->buf_size = size;
	return 0;

}



/* 环形缓冲区写一个字节 */
int Driver_Buffer_Write(ptRingBuffer buffer, const uint8_t data)
{
	if (buffer == NULL || buffer->fifo == NULL)
	{
		return -1; /* 判断合法性 */
	}

	int i=(buffer->pw+1)%(buffer->buf_size);
	if(i!=buffer->pr)
	{
		buffer->fifo[buffer->pw] = data; /* */
		buffer->pw = i;                  /* 重置写指针 */
		return 0;
	}
	return -1;
}

/* 环形缓冲区写多个字节 */
int Driver_Buffer_WriteBytes(ptRingBuffer buffer, const uint8_t *data_stream, uint8_t len)
{
	int i;
	if (buffer == NULL || buffer->fifo == NULL)
	{
		return -1; /* 判断合法性 */
	}

	if (data_stream == NULL || len == 0)
	        return -1;

	for (i = 0; i < len; i++)
	{
		if (Driver_Buffer_Write(buffer, data_stream[i]) != 0)
			break;
	}

	return i;
}


/* 环形缓冲区 读一个字节 */
int Driver_Buffer_Read(ptRingBuffer buffer, uint8_t *data)
{
	if (buffer == NULL || buffer->fifo == NULL)
	{
		return -1; /* 判断合法性 */
	}
	if (data == NULL)
	{
		return -1;
	}

	if (buffer->pr == buffer->pw)
	{
		return -1; /* 满 */
	}
	*data = buffer->fifo[buffer->pr];
	buffer->pr = (buffer->pr + 1) % buffer->buf_size; /* 自增 */
	return 0;

}

/* 环形缓冲区 读多个字节 */
int Driver_Buffer_ReadBytes(ptRingBuffer buffer, uint8_t *data_stream, uint8_t len)
{
    int i = 0;
    if (buffer == NULL || buffer->fifo == NULL)
        return -1; /* 判断合法性 */
    if (data_stream == NULL || len == 0)
        return -1;
    for (i = 0; i < len; i++)
    {
        if (Driver_Buffer_Read(buffer, &data_stream[i]) != 0)
            break;
    }
    return i;
}

/*  清空环形缓冲区 */
int Driver_Buffer_Clean(ptRingBuffer buffer)
{
    if (buffer == NULL || buffer->fifo == NULL)
        return -1;                             /* 判断合法性 */
    memset(buffer->fifo, 0, buffer->buf_size); /* 清空 */
    buffer->pr = buffer->pw = 0;               /* 归零 */
    return 0;
}
/**
 * @brief 更新数据到数组
 * @param buffer
 * @param data_stream
 * @return 返回更新的数据长度
 */
int Driver_Buffer_RefreshData(ptRingBuffer buffer, uint8_t *data_stream)
{
    uint16_t len = 0;
    if (buffer->pw == buffer->buf_size)
        buffer->pw = 0;

    while (buffer->pw != buffer->pr)
    {
        data_stream[len++] = buffer->fifo[buffer->pr];
        buffer->fifo[buffer->pr] = 0;
        buffer->pr++;
        if (buffer->pr >= buffer->buf_size)
            buffer->pr = 0;
        if (len >= buffer->buf_size)
            break;
    }
    return len;
}
