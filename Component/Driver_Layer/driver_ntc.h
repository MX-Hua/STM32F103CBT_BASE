/*
 * driver_ntc.h
 *
 *  Created on: Mar 7, 2026
 *      Author: hea
 */

#ifndef DRIVER_LAYER_DRIVER_NTC_H_
#define DRIVER_LAYER_DRIVER_NTC_H_

#include "main.h"


/* 定义参数 */
#define NTC_BETA_VALUE        3950.0f     // B值(3950K)
#define NTC_NOMINAL_RESISTANCE 10000.0f   // 25℃时的电阻值(10K)
#define NTC_NOMINAL_TEMP       298.15f    // 标称温度(25℃ = 298.15K)
#define NTC_SERIES_RESISTOR   10000.0f    // 串联电阻(10K)
#define NTC_REF_VOLTAGE        3.3f       // 参考电压(3.3V)
#define NTC_ADC_RESOLUTION     4095.0f    // 12位ADC分辨率(2^12-1)


/* 温度计算使用的Steinhart-Hart系数 */
typedef struct {
    float A;
    float B;
    float C;
} NTC_Coefficients;


/* 温度传感器结构体 */
typedef struct
{
	ADC_HandleTypeDef *hadc;      // ADC句柄
	uint32_t channel;             // ADC通道
    float last_temperature;       // 最后读取的温度
	uint16_t filter_samples;      // 滤波采样数
	float *adc_buffer;            // ADC缓存
	uint8_t buffer_index;         // 缓存索引
	uint32_t adc_raw;             // 原始ADC值
	float resistance;             // 计算出的电阻值
	NTC_Coefficients coeff;       // 温度计算系数

} NTC_Sensor;

void NTC_Init(NTC_Sensor *,ADC_HandleTypeDef *,uint32_t ,uint16_t);
float NTC_ReadTemperature(NTC_Sensor*);

float NTC_GetVoltage(NTC_Sensor*);
float NTC_GetResistance(NTC_Sensor*);
uint32_t NTC_ReadRawADC(NTC_Sensor*);
float NTC_CalculateTemperature(float resistance);


#endif /* DRIVER_LAYER_DRIVER_NTC_H_ */
