/*
 * driver_rgb.h
 *
 *  Created on: Mar 9, 2026
 *      Author: hea
 */



#ifndef DRIVER_WS2812B_H

#define DRIVER_WS2812B_H



#include "main.h"
#include "tim.h"

#define WS2812_TIM htim1
#define WS2812_TIM_CH TIM_CHANNEL_4



/*这里是上文计算所得CCR的宏定义*/

#define CODE_1  (58)       //1码定时器计数次数

#define CODE_0  (29)       //0码定时器计数次数



/*建立一个定义单个LED三原色值大小的结构体*/

typedef struct

{

uint8_t R;

uint8_t G;

uint8_t B;

}RGB_Color_TypeDef;

extern const RGB_Color_TypeDef RED     ;

extern const RGB_Color_TypeDef ORANGE   ;

extern const RGB_Color_TypeDef YELLOW   ;

extern const RGB_Color_TypeDef BLUE     ;

extern const RGB_Color_TypeDef GREEN    ;

extern const RGB_Color_TypeDef BLACK    ;

extern const RGB_Color_TypeDef WHITE   ;

/*Some Static Colors------------------------------*/

extern const RGB_Color_TypeDef CYAN  ;

extern const RGB_Color_TypeDef PURPLE ;

extern const RGB_Color_TypeDef MAGENTA  ;

#define LED_NUM 1                            //LED数量宏定义，这里我使用一个LED



void RGB_SetColor(uint8_t LedId,RGB_Color_TypeDef Color);//给一个LED装载24个颜色数据码（0码和1码）

void RGB_SetnColor(uint8_t LedSrart, uint8_t LedNumber,RGB_Color_TypeDef Color);//给n个LED装载24个颜色数据码（0码和1码）

void Reset_Load(void);             //该函数用于将数组最后24个数据变为0，代表RESET_code

void RGB_SendArray(void);          //发送最终数组

void RGB_RESET(uint16_t Pixel_Len);//数据全部清零

void RGB_RED(uint16_t Pixel_Len);  //显示红灯

void RGB_GREEN(uint16_t Pixel_Len);//显示绿灯

void RGB_BLUE(uint16_t Pixel_Len); //显示蓝灯

void RGB_WHITE(uint16_t Pixel_Len);//显示白灯

void RGB_BLACK(uint16_t Pixel_Len);//显示黑灯

void rgb_yellow_strip(uint16_t Pixel_Len); //流水灯

void rgb_yellow_strip1(uint16_t Pixel_Len); //流水灯

 void rainbowCycle(uint8_t wait);

void rainbow(uint8_t wait);

 void rgb_show(uint32_t Pixel_Len, RGB_Color_TypeDef rgb);

#endif


