/*
 * driver_ntc.c
 *
 *  Created on: Mar 7, 2026
 *      Author: hea
 */


#include "driver_ntc.h"
#include "adc.h"
#include <stdlib.h>
#include <math.h>


/* 使用查表法的温度表（可选优化） */
typedef struct {
    float resistance;
    float temperature;
} TempTableEntry;

/* 简化温度表（实际使用时可以扩展） */
static const TempTableEntry temp_table[] = {
    {33000.0f, -20.0f},  // -20℃
    {20000.0f, -10.0f},  // -10℃
    {10000.0f, 25.0f},   // 25℃
    {4700.0f,  50.0f},   // 50℃
    {2200.0f,  80.0f},   // 80℃
    {1000.0f,  110.0f}   // 110℃
};
#define TEMP_TABLE_SIZE (sizeof(temp_table) / sizeof(TempTableEntry))



/**
  * @brief  初始化NTC温度传感器
  * @param  sensor: 温度传感器结构体指针
  * @param  hadc: ADC句柄
  * @param  channel: ADC通道
  * @param  filter_size: 滤波窗口大小
  * @retval None
  */
void NTC_Init(NTC_Sensor *sensor,ADC_HandleTypeDef *hadc,uint32_t channel,uint16_t filter_size)
{
	 /* 初始化结构体成员 */
	sensor->hadc = hadc;
	sensor->channel = channel;
	sensor->last_temperature = 25.0f;  // 默认25℃
	sensor->filter_samples = (filter_size > 0) ? filter_size : 1;
	sensor->buffer_index = 0;
	sensor->adc_raw = 0;
	sensor->resistance = NTC_NOMINAL_RESISTANCE;

	/* 分配滤波缓冲区 */
	if (sensor->filter_samples > 1) {
		sensor->adc_buffer = (float*)malloc(sensor->filter_samples * sizeof(float));
		if (sensor->adc_buffer) {
			for (int i = 0; i < sensor->filter_samples; i++) {
				sensor->adc_buffer[i] = 0.0f;
			}
		} else {
			sensor->filter_samples = 1;  // 分配失败，禁用滤波
		}
	} else {
		sensor->adc_buffer = NULL;
	}

	/* 初始化Steinhart-Hart系数 */
	// 使用Beta参数简化计算：1/T = 1/T0 + (1/B) * ln(R/R0)
	sensor->coeff.A = 1.0f / NTC_NOMINAL_TEMP;
	sensor->coeff.B = 1.0f / NTC_BETA_VALUE;
	sensor->coeff.C = 0.0f;  // 简化模型不使用C系数

}

uint32_t NTC_ReadRawADC(NTC_Sensor* sensor)
{
	HAL_StatusTypeDef status;
	uint32_t adc_value = 0;

	/* 启动ADC转换 */
	status=HAL_ADC_Start(sensor->hadc);

	if (status != HAL_OK) {
		return 0;
	}

	/* 等待转换完成 */
	if (HAL_ADC_PollForConversion(sensor->hadc, 10) == HAL_OK) {
		 adc_value = HAL_ADC_GetValue(sensor->hadc);
	 }

	/* 停止ADC转换 */
	HAL_ADC_Stop(sensor->hadc);

	sensor->adc_raw = adc_value;
	return adc_value;
}



/**
  * @brief  获取ADC电压值
  * @param  sensor: 温度传感器结构体指针
  * @retval 电压值(伏特)
  */

float NTC_GetVoltage(NTC_Sensor *sensor)
{
	if (sensor->adc_raw == 0) {
	        NTC_ReadRawADC(sensor);
	    }

	return (sensor->adc_raw * NTC_REF_VOLTAGE) / NTC_ADC_RESOLUTION;
}


/**
  * @brief  获取NTC电阻值
  * @param  sensor: 温度传感器结构体指针
  * @retval 电阻值(欧姆)
  *
  */

float NTC_GetResistance(NTC_Sensor *sensor)
{
	float voltage, resistance;

	/* 读取ADC值 */
	NTC_ReadRawADC(sensor);

	/* 计算电压 */
	voltage = NTC_GetVoltage(sensor);


	/* 防止除零错误 */
	if (voltage < 0.001f) {
		voltage = 0.001f;
	} else if (voltage > (NTC_REF_VOLTAGE - 0.001f)) {
		voltage = NTC_REF_VOLTAGE - 0.001f;
	}

	/* 计算电阻：电压分压公式
	     * Vout = Vref * (R_ntc / (R_series + R_ntc))
	     * R_ntc = R_series * Vout / (Vref - Vout)
	     */
	resistance = NTC_SERIES_RESISTOR * voltage / (NTC_REF_VOLTAGE - voltage);

	sensor->resistance = resistance;
	return resistance;

}


/**
  * @brief  通过Beta公式计算温度
  * @param  resistance: NTC电阻值
  * @retval 温度值(摄氏度)
  */

float NTC_CalculateTemperature(float resistance)
{
	float steinhart, kelvin_temp;

	/* 使用Beta公式计算：
	 * 1/T = 1/T0 + (1/B) * ln(R/R0)
	 * 其中：
	 * T0 = 25℃ = 298.15K
	 * B = 3950K
	 * R0 = 10KΩ
	 */

	 /* 防止非法值 */
	if (resistance <= 0.0f) {
		return -273.15f;  // 绝对零度
	}

	/* 计算开尔文温度 */
	steinhart = resistance/NTC_NOMINAL_RESISTANCE ;          // R/R0
	steinhart = logf(steinhart);                             // ln(R/R0)
	steinhart /= NTC_BETA_VALUE;                             // (1/B)*ln(R/R0)
	steinhart += 1.0f / NTC_NOMINAL_TEMP;                   // 1/T0 + (1/B)*ln(R/R0)

	kelvin_temp = 1.0f / steinhart;                         // T(K)

	/* 转换为摄氏度 */
	return kelvin_temp - 273.15f;

}

/**
  * @brief  通过查表法计算温度（线性插值）
  * @param  resistance: NTC电阻值
  * @retval 温度值(摄氏度)
  */
static float NTC_CalculateByLookup(float resistance)
{
    uint8_t i;

    if (resistance >= temp_table[0].resistance) {
        return temp_table[0].temperature;  // 低于最低温度
    }

    if (resistance <= temp_table[TEMP_TABLE_SIZE-1].resistance) {
        return temp_table[TEMP_TABLE_SIZE-1].temperature;  // 高于最高温度
    }

    /* 查找相邻的两个点进行线性插值 */
    for (i = 0; i < TEMP_TABLE_SIZE - 1; i++) {
        if (resistance <= temp_table[i].resistance &&
            resistance >= temp_table[i+1].resistance) {
            float R1 = temp_table[i].resistance;
            float R2 = temp_table[i+1].resistance;
            float T1 = temp_table[i].temperature;
            float T2 = temp_table[i+1].temperature;

            /* 线性插值 */
            return T1 + (T2 - T1) * ((resistance - R1) / (R2 - R1));
        }
    }

    return 25.0f;  // 默认返回25℃
}


/**
  * @brief  读取温度值
  * @param  sensor: 温度传感器结构体指针
  * @retval 温度值(摄氏度)
**/

float NTC_ReadTemperature(NTC_Sensor *sensor)
{
	float resistance, temperature;

	/* 获取电阻值 */
	resistance = NTC_GetResistance(sensor);

	/* 计算温度 */
	temperature = NTC_CalculateTemperature(resistance);

}

