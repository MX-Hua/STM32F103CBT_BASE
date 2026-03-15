################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# 将这些工具调用的输入和输出添加到构建变量 
C_SRCS += \
../Component/Driver_Layer/driver_adc_temperature.c \
../Component/Driver_Layer/driver_crc.c \
../Component/Driver_Layer/driver_delay.c \
../Component/Driver_Layer/driver_eeprom.c \
../Component/Driver_Layer/driver_iic.c \
../Component/Driver_Layer/driver_interior_flash.c \
../Component/Driver_Layer/driver_led.c \
../Component/Driver_Layer/driver_ntc.c \
../Component/Driver_Layer/driver_rgb.c \
../Component/Driver_Layer/driver_ringbuffer.c \
../Component/Driver_Layer/driver_rs485.c \
../Component/Driver_Layer/driver_uid.c \
../Component/Driver_Layer/driver_w25qxx.c 

OBJS += \
./Component/Driver_Layer/driver_adc_temperature.o \
./Component/Driver_Layer/driver_crc.o \
./Component/Driver_Layer/driver_delay.o \
./Component/Driver_Layer/driver_eeprom.o \
./Component/Driver_Layer/driver_iic.o \
./Component/Driver_Layer/driver_interior_flash.o \
./Component/Driver_Layer/driver_led.o \
./Component/Driver_Layer/driver_ntc.o \
./Component/Driver_Layer/driver_rgb.o \
./Component/Driver_Layer/driver_ringbuffer.o \
./Component/Driver_Layer/driver_rs485.o \
./Component/Driver_Layer/driver_uid.o \
./Component/Driver_Layer/driver_w25qxx.o 

C_DEPS += \
./Component/Driver_Layer/driver_adc_temperature.d \
./Component/Driver_Layer/driver_crc.d \
./Component/Driver_Layer/driver_delay.d \
./Component/Driver_Layer/driver_eeprom.d \
./Component/Driver_Layer/driver_iic.d \
./Component/Driver_Layer/driver_interior_flash.d \
./Component/Driver_Layer/driver_led.d \
./Component/Driver_Layer/driver_ntc.d \
./Component/Driver_Layer/driver_rgb.d \
./Component/Driver_Layer/driver_ringbuffer.d \
./Component/Driver_Layer/driver_rs485.d \
./Component/Driver_Layer/driver_uid.d \
./Component/Driver_Layer/driver_w25qxx.d 


# 每个子目录必须为构建它所贡献的源提供规则
Component/Driver_Layer/%.o Component/Driver_Layer/%.su Component/Driver_Layer/%.cyclo: ../Component/Driver_Layer/%.c Component/Driver_Layer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component" -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component/APP_Layer" -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component/Driver_Layer" -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component/Middle_Layer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Component-2f-Driver_Layer

clean-Component-2f-Driver_Layer:
	-$(RM) ./Component/Driver_Layer/driver_adc_temperature.cyclo ./Component/Driver_Layer/driver_adc_temperature.d ./Component/Driver_Layer/driver_adc_temperature.o ./Component/Driver_Layer/driver_adc_temperature.su ./Component/Driver_Layer/driver_crc.cyclo ./Component/Driver_Layer/driver_crc.d ./Component/Driver_Layer/driver_crc.o ./Component/Driver_Layer/driver_crc.su ./Component/Driver_Layer/driver_delay.cyclo ./Component/Driver_Layer/driver_delay.d ./Component/Driver_Layer/driver_delay.o ./Component/Driver_Layer/driver_delay.su ./Component/Driver_Layer/driver_eeprom.cyclo ./Component/Driver_Layer/driver_eeprom.d ./Component/Driver_Layer/driver_eeprom.o ./Component/Driver_Layer/driver_eeprom.su ./Component/Driver_Layer/driver_iic.cyclo ./Component/Driver_Layer/driver_iic.d ./Component/Driver_Layer/driver_iic.o ./Component/Driver_Layer/driver_iic.su ./Component/Driver_Layer/driver_interior_flash.cyclo ./Component/Driver_Layer/driver_interior_flash.d ./Component/Driver_Layer/driver_interior_flash.o ./Component/Driver_Layer/driver_interior_flash.su ./Component/Driver_Layer/driver_led.cyclo ./Component/Driver_Layer/driver_led.d ./Component/Driver_Layer/driver_led.o ./Component/Driver_Layer/driver_led.su ./Component/Driver_Layer/driver_ntc.cyclo ./Component/Driver_Layer/driver_ntc.d ./Component/Driver_Layer/driver_ntc.o ./Component/Driver_Layer/driver_ntc.su ./Component/Driver_Layer/driver_rgb.cyclo ./Component/Driver_Layer/driver_rgb.d ./Component/Driver_Layer/driver_rgb.o ./Component/Driver_Layer/driver_rgb.su ./Component/Driver_Layer/driver_ringbuffer.cyclo ./Component/Driver_Layer/driver_ringbuffer.d ./Component/Driver_Layer/driver_ringbuffer.o ./Component/Driver_Layer/driver_ringbuffer.su ./Component/Driver_Layer/driver_rs485.cyclo ./Component/Driver_Layer/driver_rs485.d ./Component/Driver_Layer/driver_rs485.o ./Component/Driver_Layer/driver_rs485.su ./Component/Driver_Layer/driver_uid.cyclo ./Component/Driver_Layer/driver_uid.d ./Component/Driver_Layer/driver_uid.o ./Component/Driver_Layer/driver_uid.su ./Component/Driver_Layer/driver_w25qxx.cyclo ./Component/Driver_Layer/driver_w25qxx.d ./Component/Driver_Layer/driver_w25qxx.o ./Component/Driver_Layer/driver_w25qxx.su

.PHONY: clean-Component-2f-Driver_Layer

