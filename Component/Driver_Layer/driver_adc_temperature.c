/*
 * driver_adc_temperature.c
 *
 *  Created on: Mar 7, 2026
 *      Author: hea
 */


#include "driver_adc_temperature.h"
#include "main.h"


extern ADC_HandleTypeDef hadc1;


void Driver_ADC_Temperature_Init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADC_Start(&hadc1);
}


float Driver_ADC_Temperature_GetValue(void)
{
	uint16_t nData=0;
	float nValue=0;
	//连续模式
	//HAL_ADC_Start(&hadc1);					//开启转换
	//HAL_ADC_PollForConversion(&&hadc1,250);//等待adc转换完成

	nData=HAL_ADC_GetValue(&hadc1); //得到转换数据

	nValue=(1.43-nData*3.3/4096)*(1000/4.3)+25;


	//返回模拟电压值
	return nValue;
}
