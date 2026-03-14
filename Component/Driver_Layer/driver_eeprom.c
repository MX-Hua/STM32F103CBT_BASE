/*
 * driver_eeprom.c
 *
 *  Created on: Mar 10, 2026
 *      Author: hea
 */


#include "driver_eeprom.h"
#include "i2c.h"
#include "driver_iic.h"
#include "driver_delay.h"



#define HARDWARE_IIC 0

void EEPROM_WriteByte(uint16_t addr, uint8_t data)
{

    uint8_t write_data[10];
	uint8_t data_num;

	//AT24C01/02的数据地址长度为8位
	//AT24C04/08/16数据地址长度为16位

	if(EEPROM_WORD_ADDR_SIZE==0x08)
	{
		write_data[0] = (uint8_t)(addr & 0x00FF);
		write_data[1] = data;
		data_num = 2;
	}
	else
	{
		write_data[0] = (uint8_t)(addr>>8);
		write_data[1] = (uint8_t)(addr & 0x00FF);
		write_data[2] = data;
		data_num = 3;
	}

#if HARDWARE_IIC
	//发送数据和地址
	if(HAL_I2C_Master_Transmit(&hi2c1,EEPROM_DEV_ADDR|EEPROM_WR,write_data,data_num,300)!= HAL_OK)
	{
		 Error_Handler();
	}
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);

#else

	//0:成功收到ack
	I2C_Start();
	I2C_SendByte(EEPROM_DEV_ADDR|EEPROM_WR);

	for(uint16_t i=0;i<data_num;i++)
	{
		I2C_SendByte(write_data[i]);

	}

	I2C_Stop();


#endif

}


/*
 *  函数名：uint8_t EEPROM_ReadByte(uint16_t addr, uint8_t *pdata)
 *  输入参数：addr -> 读一个字节的EEPROM初始地址
 *            data -> 要读的数据指针
 *  输出参数：无
 *  返回值：无
 *  函数作用：EEPROM读一个字节
*/
void EEPROM_ReadByte(uint16_t addr, uint8_t *pdata)
{
    uint8_t write_data[10];
	uint8_t data_num;

	//AT24C01/02的数据地址长度为8位
	//AT24C04/08/16数据地址长度为16位
	if(EEPROM_WORD_ADDR_SIZE==0x08)
    {
		write_data[0] = (uint8_t)(addr & 0x00FF);
		data_num = 1;
    }
    else
    {
		write_data[0] = (uint8_t)(addr>>8);
		write_data[1] = (uint8_t)(addr & 0x00FF);
		data_num = 2;
    }
#if HARDWARE_IIC
	//发送数据和地址
    if(HAL_I2C_Master_Transmit(&hi2c1, EEPROM_DEV_ADDR | EEPROM_WR , (uint8_t*)write_data, data_num, 300) != HAL_OK)
    {
        Error_Handler();
    }
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);

	//接收数据
    if(HAL_I2C_Master_Receive(&hi2c1, EEPROM_DEV_ADDR | EEPROM_RD, (uint8_t*)pdata, 1, 300) != HAL_OK)
    {
        Error_Handler();
    }
#else
    I2C_Start();
    I2C_SendByte(EEPROM_DEV_ADDR|EEPROM_WR);
    for(uint16_t i=0;i<data_num;i++)
	{
		I2C_SendByte(write_data[i]);
	}

    //读数据
    I2C_Start();
    I2C_SendByte(EEPROM_DEV_ADDR|EEPROM_RD);

    *pdata=I2C_ReadByte(0);
    I2C_Stop();



#endif
}

/*
 *  函数名：void EEPROM_Write_NBytes(uint16_t addr, uint8_t *pdata, uint16_t sz)
 *  输入参数：addr -> 写一个字节的EEPROM初始地址
 *            data -> 要写的数据指针
 *            sz   -> 要写的字节个数
 *  输出参数：无
 *  返回值：无
 *  函数作用：EEPROM写N个字节
*/

void EEPROM_Write_NBytes(uint16_t addr, uint8_t *pdata, uint16_t sz)
{
    uint16_t i = 0;

    for(i=0; i<sz; i++)
    {
        EEPROM_WriteByte(addr, pdata[i]);
        addr++;
        HAL_Delay(10); // Write Cycle Time 5ms
    }
}


/*
 *  函数名：void EEPROM_Read_NBytes(uint16_t addr, uint8_t *pdata, uint16_t sz)
 *  输入参数：addr -> 读一个字节的EEPROM初始地址
 *            data -> 要读的数据指针
 *            sz   -> 要读的字节个数
 *  输出参数：无
 *  返回值：无
 *  函数作用：EEPROM读N个字节
*/
void EEPROM_Read_NBytes(uint16_t addr, uint8_t *pdata, uint16_t sz)
{
    uint16_t i = 0;

    for(i=0; i<sz; i++)
    {
        EEPROM_ReadByte(addr, &pdata[i]);
        addr++;
    }
}
