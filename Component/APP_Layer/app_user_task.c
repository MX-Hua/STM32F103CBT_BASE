/*
 * app_user_task.c
 *
 *  Created on: Mar 7, 2026
 *      Author: hea
 */


#include "app_user_task.h"

#include "driver_led.h"
#include "middle_printf.h"
#include "driver_delay.h"
#include "driver_ntc.h"
#include "adc.h"
#include "dma.h"
#include "driver_adc_temperature.h"
#include "driver_eeprom.h"
#include "driver_rgb.h"
#include "driver_uid.h"
#include "driver_crc.h"
#include "driver_iic.h"
#include "driver_w25qxx.h"
#include "driver_rs485.h"

#include "iwdg.h"
#include "main.h"


#define App_Delay(x) delay_ms(x)


uint8_t Buffdata [20]= {0x48,0x65,0x6c,0x6c,0x6f,0x77,0x20,0x77,0x6f,0x72,0x6c,0x64,0x0a};
uint8_t CRC8_C=0;
uint8_t CRC8_T=0;

uint32_t Tx_Dma_Buff[256];
uint32_t Rx_Dma_Buff[256];
uint32_t tickstart;
uint32_t timeout_ms=2000;



uint32_t uid[3]={0};
uint8_t ruid[12]={0};

NTC_Sensor ntc_sensor;


//iic
uint8_t IICBuffdata [20]= {0x48,0x65,0x6c,0xff,0x6f,0x77,0x20,0x77,0x6f,0x72,0x6c,0x64,0x0a};
uint8_t IICRBuffdata [20]={0};

//spi
uint8_t T_Data[5]={0x48,0x65,0x6c,0x11,0x6f};
uint8_t R_Data [5]={0};



extern void APP_RGB_Task(void);
extern void APP_W25Qxx_Task(void);
extern void APP_RS485_Task(void);
extern void APP_NTC_Task(void);
extern void APP_Internal_Temperature(void);
extern void APP_Get_UID(void);
extern void APP_DMA_Task(void);
extern void APP_EEPROM_Task(void);

// 传输完成回调
void HAL_DMA_XferCpltCallback(DMA_HandleTypeDef *hdma)
{
    // 判断是哪个 DMA 通道触发的（如果有多个 DMA 共用同一个回调）
    if (hdma->Instance == DMA1_Channel1)   // 注意：Instance 是外设寄存器基地址
    {
        uart_printf("ok\r\n");
        // 例如：设置标志位、处理数据、通知主循环等
        // 注意：回调函数在中断上下文中执行，尽量简短
    }
}

void App_User_Task_Init(void)
{

	//初始化
	Led_Init();
	NTC_Init(&ntc_sensor,&hadc2,ADC_CHANNEL_0,10); //10点移动平均滤波
	Driver_ADC_Temperature_Init();
	I2C_Init();
	SPI1_Init();
	RS485_Init();



	CRC8_C=Driver_CRC8_Calculate(Buffdata,13);
	CRC8_T=Driver_CRC8_CalculateFast(Buffdata,13);

	for(int i=0;i<0xff;i++)
	{
		Tx_Dma_Buff[i]=i;
	}


	tickstart=HAL_GetTick();

	HAL_DMA_Start_IT(&hdma_memtomem_dma1_channel1,(uint32_t)&Tx_Dma_Buff[0],(uint32_t)&Rx_Dma_Buff[0],256*4);
	//等待传输完成标志
	while(__HAL_DMA_GET_FLAG(&hdma_memtomem_dma1_channel1,DMA_FLAG_TC1)==RESET)
	{
		//注意：避免此处长时间等待
		if((HAL_GetTick()-tickstart)>timeout_ms)
		{
			break;//超时
		}

	}

	//EEPROM
	uint16_t num=8;
	EEPROM_Write_NBytes(0,&IICBuffdata[0],num);

	//SPI
	APP_W25Qxx_Task();




}



void App_User_Task(void)
{

	//NTC读温度
	//APP_NTC_Task();

	//读mcu内部温度
	//APP_Internal_Temperature();

	//获取mcu的uid
	//APP_Get_UID();

	//DMA 内存到内存
	//APP_DMA_Task();

	//EEPROM
	//APP_EEPROM_Task();


	//看门狗 如果不用，记得在main函数里要关闭，不然1s不喂狗 会重启
	//HAL_IWDG_Refresh(&hiwdg);

	//LED
	Led_Toggle();

	//RGB
	APP_RGB_Task();

	//RS485
	APP_RS485_Task();

}

//NTC读温度试任务
void APP_NTC_Task(void)
{
	float Temperature;
	Temperature=NTC_ReadTemperature(&ntc_sensor);
	uart_printf("NTC Temp:%0.2f\r\n",Temperature);
}

//读单片机内部温度测试任务
void APP_Internal_Temperature(void)
{
	float Temperature;
	Temperature=Driver_ADC_Temperature_GetValue();
	uart_printf("NTC Temp:%0.2f\r\n",Temperature);
}

//读单片机内部UID测试任务
void APP_Get_UID(void)
{
	Get_HAL_UID(uid);
	Read_UID(ruid);
	uart_printf("\r\nUID:0x%08X-0x%08X-0x%08X\r\n",uid[0],uid[1],uid[2]);
	uart_printf("RUID:");
	//uart_printf("data:%d\r\n",*uid++);

}

//DMA 内存到内存 测试任务
void APP_DMA_Task(void)
{
	for(int i=0;i<0xff;i++)
	{
		if(Rx_Dma_Buff[i]!=Tx_Dma_Buff[i])
		{
			uart_printf("DMA传输失败！%d\r\n",i);
			break;
		}
		if(i==0xfe)
		{
			uart_printf("DMA传输成功！\r\n");
		}
	}

}

//EMMPROM 测试任务
void APP_EEPROM_Task(void)
{
	EEPROM_Read_NBytes(0,&IICRBuffdata[0],8);
}


//rgb灯测试任务
void APP_RGB_Task(void)
{
	App_Delay(500);
	rgb_show(1,RED);

	App_Delay(500);
	rgb_show(1,YELLOW);

	App_Delay(500);
	rgb_show(1,ORANGE);

	App_Delay(500);
	rgb_show(1,BLUE);

}


//W25qxx测试任务
void APP_W25Qxx_Task(void)
{
	uint32_t id=SPI_FLASH_ReadID();
	uart_printf("FLASH_ID:%x\r\n",id);


	SPI_FLASH_SectorErase(0);
	SPI_FLASH_BufferWrite((uint8_t *)T_Data,0,5);

	SPI_FLASH_BufferRead((uint8_t *)R_Data,0,5);
	uart_printf("data:%d\r\n",R_Data[0]);

}


//RS485测试任务
void APP_RS485_Task(void)
{

	App_Delay(500);
	//打印数据
	RS485_Printf("rs485data:lao tan bie hun!\r\n");

	//接受数据
}

