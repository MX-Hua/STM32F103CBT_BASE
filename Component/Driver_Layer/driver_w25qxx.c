/*
 * driver_w2qxx.c
 *
 *  Created on: 2026年3月14日
 *      Author: hea
 */

#include "driver_w25qxx.h"


void SPI1_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	NSS_RCC_EN();

	GPIO_InitStruct.Pin = NSS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(NSS_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(NSS_PORT, NSS_PIN, GPIO_PIN_SET);
}


/*读取制造商和设备ID*/
uint32_t SPI_FLASH_ReadID(void)
{
	uint8_t W25X_JEDEC_ID=0X9F;
	uint8_t temp0[3];
	uint32_t temp;

	NSS_LOW();//选择FLASH:NSS低电平

	HAL_SPI_Transmit(&hspi1,&W25X_JEDEC_ID,1,10);//发送指令

	HAL_SPI_Receive(&hspi1,temp0,3, 10);//读取制造商和设备ID

	NSS_HIGH();//停止信号 FLASH:NSS高电平

	temp=(temp0[0])<<16|(temp0[1]<<8)|temp0[2];//把数据组合起来，作为函数的返回值

	return temp;
}

/*写使能*/
void SPI_FLASH_WriteEnable(void)
{
	uint8_t W25X_WriteEnable=0x06;

	NSS_LOW();//选择FLASH:NSS低电平

	HAL_SPI_Transmit(&hspi1,&W25X_WriteEnable,1,10);//发送指令

	NSS_HIGH();//停止信号 FLASH:NSS高电平
}

/*扇区擦除*/
void SPI_FLASH_SectorErase(uint32_t SectorAddr)
{
	uint8_t W25X_SectorErase=0x20;
	uint8_t temp1,temp2,temp3;

	SPI_FLASH_WriteEnable();//写使能

	NSS_LOW();//选择FLASH:NSS低电平

	HAL_SPI_Transmit(&hspi1,&W25X_SectorErase,1,10);//发送指令

	temp1=(SectorAddr&(0xFF0000))>>16;//发送地址
	HAL_SPI_Transmit(&hspi1,&temp1,1,10);
	temp2=(SectorAddr&(0x00FF00))>>8;
	HAL_SPI_Transmit(&hspi1,&temp2,1,10);
	temp3=(SectorAddr&(0x0000FF));
	HAL_SPI_Transmit(&hspi1,&temp3,1,10);
	NSS_HIGH();//停止信号 FLASH:NSS高电平

	SPI_FLASH_WaitForWriteEnd();//等待擦除完毕
}

/*等待 WIP(BUSY) 标志被置 0，即等待到 FLASH 内部数据写入完毕*/
void SPI_FLASH_WaitForWriteEnd(void)
{
	uint8_t W25X_ReadStatusReg=0x05;
	uint8_t temp;

	NSS_LOW();//选择FLASH:NSS低电平

	HAL_SPI_Transmit(&hspi1,&W25X_ReadStatusReg,1,10);//发送指令
	do
	{
		HAL_SPI_Receive(&hspi1,&temp,1,10);// 读取 FLASH 芯片的状态寄存器
	}
	while((temp&0x01)==1);

	NSS_HIGH();//停止信号 FLASH:NSS高电平
}

/*在FLASH的一个写循环中可以写多个字节，但一次写入
的字节数不能超过FLASH页的大小，W25Q64每页有256个字节*/
void SPI_FLASH_PageWrite(uint8_t * pBuffer, uint32_t WriteAddr,uint16_t NumByteToWrite)
{
	uint8_t W25X_PageProgram=0x02;
	uint8_t temp1,temp2,temp3;

	SPI_FLASH_WriteEnable();//写使能

	NSS_LOW();//选择FLASH:NSS低电平

	HAL_SPI_Transmit(&hspi1,&W25X_PageProgram,1,10);//发送指令

	temp1=(WriteAddr&(0xFF0000))>>16;//发送地址
	HAL_SPI_Transmit(&hspi1,&temp1,1,10);

	temp2=(WriteAddr&(0x00FF00))>>8;
	HAL_SPI_Transmit(&hspi1,&temp2,1,10);

	temp3=(WriteAddr&(0x0000FF));
	HAL_SPI_Transmit(&hspi1,&temp3,1,10);

	HAL_SPI_Transmit(&hspi1,pBuffer,NumByteToWrite,10);//发送数据

	NSS_HIGH();//停止信号 FLASH:NSS高电平

	SPI_FLASH_WaitForWriteEnd();//等待写入完毕
}

/*不定量数据写入*/
void SPI_FLASH_BufferWrite(uint8_t * pBuffer, uint32_t WriteAddr,uint16_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;

  Addr = WriteAddr % FLASH_PAGESIZE;//判断写入的首地址是否与EEPROM页的首地址对齐，0为对齐
  count = FLASH_PAGESIZE - Addr;//计算从写入的首地址需要写多少数据才能填满当前页
  NumOfPage =  NumByteToWrite / FLASH_PAGESIZE;//计算写入数据需要写几个完整页（地址对齐的情况）
  NumOfSingle = NumByteToWrite % FLASH_PAGESIZE;//计算写完完整页剩下的数据个数（地址对齐的情况）

  if(Addr == 0) //判断写入的首地址是否与页地址对齐
  {
    if(NumOfPage == 0) //如果页对齐，判断数据是否不满一页
    {
      SPI_FLASH_PageWrite(pBuffer,WriteAddr,NumOfSingle);//如果不满一页，直接写入数据
    }
    else  //在数据满一页的情况下，通过地址自增方式，循环写入数据（页写入的形式）
    {
      while(NumOfPage--)//循环写入数据：先写入完整页
      {
				SPI_FLASH_PageWrite(pBuffer, WriteAddr, FLASH_PAGESIZE);
        WriteAddr +=  FLASH_PAGESIZE;
        pBuffer += FLASH_PAGESIZE;
      }

      if(NumOfSingle!=0)//循环写入数据：再写入不满一页的数据
      {
				SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
  else
  {
    if(NumOfPage== 0) //如果页不对齐，判断数据是否不满一页
    {
			if(NumOfSingle<=count)//如果不满一页，判断数据是否跨页
			{
				SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);//如果不跨页，直接写入数据
			}
			else
			{
				SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);//如果跨页，先写首页数据，再写次页数据
				SPI_FLASH_PageWrite(pBuffer+count, WriteAddr+count, NumOfSingle-count);
			}
    }

    else
    {
			/*如果数据满一页，对数据进行分离*/
      NumByteToWrite -= count;//扣除第一页数据个数
      NumOfPage =  NumByteToWrite / FLASH_PAGESIZE;//计算写入数据需要写几个完整页
      NumOfSingle = NumByteToWrite % FLASH_PAGESIZE;	//计算写完完整页剩下的数据个数

      if(count != 0)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);//写入首页数据
        WriteAddr += count;//写地址自增
        pBuffer += count;//缓冲区指针自增
      }

      while(NumOfPage--)//依次写入完整页的数据
      {
				SPI_FLASH_PageWrite(pBuffer, WriteAddr, FLASH_PAGESIZE);
        WriteAddr +=  FLASH_PAGESIZE;//写地址自增
        pBuffer += FLASH_PAGESIZE; //缓冲区指针自增
      }
      if(NumOfSingle != 0)//判断最后一页的数据是否是填满完整一页的
      {
				SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);//写入最后一页的数据
      }
    }
  }
}

/*读取FLASH数据,读取的数据量没有限制*/
void SPI_FLASH_BufferRead(uint8_t * pBuffer, uint32_t  ReadAddr,uint16_t NumByteToWrite)
{
	uint8_t W25X_ReadData=0x03;
	uint8_t temp1,temp2,temp3;

	SPI_FLASH_WriteEnable();//写使能

	NSS_LOW();//选择FLASH:NSS低电平

	HAL_SPI_Transmit(&hspi1,&W25X_ReadData,1,10);//发送指令

	temp1=(ReadAddr&(0xFF0000))>>16;//发送地址
	HAL_SPI_Transmit(&hspi1,&temp1,1,10);

	temp2=(ReadAddr&(0x00FF00))>>8;
	HAL_SPI_Transmit(&hspi1,&temp2,1,10);

	temp3=(ReadAddr&(0x0000FF));
	HAL_SPI_Transmit(&hspi1,&temp3,1,10);

	HAL_SPI_Receive(&hspi1,pBuffer,NumByteToWrite, 10);//这里超时时间不能设置为1，否则会读取错误

	NSS_HIGH();//停止信号 FLASH:NSS高电平
}


