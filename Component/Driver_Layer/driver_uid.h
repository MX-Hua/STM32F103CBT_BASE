/*
 * driver_uid.h
 *
 *  Created on: Mar 7, 2026
 *      Author: hea
 */

#ifndef DRIVER_LAYER_DRIVER_UID_H_
#define DRIVER_LAYER_DRIVER_UID_H_


#include "stm32f1xx_hal.h"


void Get_HAL_UID(uint32_t *);
void Read_UID(uint8_t *);

#endif /* DRIVER_LAYER_DRIVER_UID_H_ */
