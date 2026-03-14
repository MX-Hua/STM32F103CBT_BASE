/*
 * driver_iic.c
 *
 *  Created on: Mar 11, 2026
 *      Author: hea
 */

#include "driver_iic.h"



void I2C_Init(void)
{
	//初始化GPIO

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	RCC_IIC_PIN_CLK_ENABLE();

	//初始化SCL线

	GPIO_InitStruct.Pin=SCL_PIN;
	GPIO_InitStruct.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull=GPIO_NOPULL;
	GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SCL_PORT,&GPIO_InitStruct);

	//初始化SDA线

	GPIO_InitStruct.Pin=SDA_PIN;

	HAL_GPIO_Init(SDA_PORT,&GPIO_InitStruct);

	//设置默认电平
	IIC_SCL(IIC_H);
	IIC_SDA(IIC_H);

}



//设置SDA为输出模式
void I2C_SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};


	//初始化SDA线
	GPIO_InitStruct.Pin=SDA_PIN;
	GPIO_InitStruct.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull=GPIO_PULLUP;
	GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(SDA_PORT,&GPIO_InitStruct);


}


//设置SDA为输入模式
void I2C_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	RCC_IIC_PIN_CLK_ENABLE();

	//初始化SDA线
	GPIO_InitStruct.Pin=SDA_PIN;
	GPIO_InitStruct.Mode=GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SDA_PORT,&GPIO_InitStruct);

}



void I2C_Start(void)
{
	//SCL为高电平，SDA由高变低
	I2C_SDA_OUT();

	IIC_SCL(IIC_H);

	IIC_SDA(IIC_H);
	iic_delay();

	IIC_SDA(IIC_L);
	iic_delay();

	IIC_SCL(IIC_L);

}



void I2C_Stop(void)
{
	I2C_SDA_OUT();

	//SCL为高电平，SDA由低变高

	IIC_SDA(IIC_L);

	IIC_SCL(IIC_H);
	iic_delay();

	IIC_SDA(IIC_H);
	iic_delay();

	IIC_SCL(IIC_L);

}



//IIC发出应答信号

void I2C_ACK(void)
{
	I2C_SDA_OUT();

	//在SCL为底电平时拉低SDA,然后将SCL拉高后，才会读取SDA上的数据
	IIC_SCL(IIC_L);


	IIC_SDA(IIC_L);
	iic_delay();

	IIC_SCL(IIC_H);
	iic_delay();

	IIC_SCL(IIC_L);

}


void I2C_NACK(void)
{
	I2C_SDA_OUT();

	//在SCL为底电平时拉低SDA,然后将SCL拉高后，才会读取SDA上的数据
	IIC_SCL(IIC_L);

	IIC_SDA(IIC_H);
	iic_delay();

	IIC_SCL(IIC_H);
	iic_delay();

	IIC_SCL(IIC_L);


}


//IIC获取应答信号 0：应答 1：非应答
uint8_t I2C_GetACK(void)
{
	uint8_t time=0;

	I2C_SDA_IN();

	IIC_SCL(IIC_L);
	iic_delay();

	IIC_SDA(IIC_H);
	iic_delay();


	IIC_SCL(IIC_H);
	iic_delay();

	//获取SDA上是电平

	while(IIC_READ_SDA())
	{
		time++;
		if(time>1000)
		{
			I2C_Stop();
			return 1;
		}

	}
	IIC_SCL(IIC_L);
	return 0;

}





uint8_t I2C_SendByte(uint8_t data)
{
	I2C_SDA_OUT();

	uint8_t cnt=0;

	IIC_SCL(IIC_L);

	for(cnt=0; cnt<8; cnt++)
	{
		if((data&0x80)>>7)
		{
			IIC_SDA(IIC_H);
		}
		else
		{
			IIC_SDA(IIC_L);
		}
		data=data<<1;
		IIC_SCL(IIC_H);
		iic_delay();
		IIC_SCL(IIC_L);
		iic_delay();
	}

	return I2C_GetACK();

}


uint8_t I2C_ReadByte(uint8_t ack)
{
	I2C_SDA_IN();

	uint8_t cnt;
	uint8_t data = 0;

	for(cnt=0; cnt<8; cnt++)
	{
		IIC_SCL(IIC_L);
		iic_delay();
		IIC_SCL(IIC_H);
		data<<=1;

		if(IIC_READ_SDA())
		{
			data++;
		}
		iic_delay();
	}


	//发送ack应答 或者非应答

	if(ack==0)
	{
		I2C_ACK();
	}

	else
	{
		I2C_NACK();

	}

	return data;
}
