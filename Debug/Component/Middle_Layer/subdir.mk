################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# 将这些工具调用的输入和输出添加到构建变量 
C_SRCS += \
../Component/Middle_Layer/middle_printf.c 

OBJS += \
./Component/Middle_Layer/middle_printf.o 

C_DEPS += \
./Component/Middle_Layer/middle_printf.d 


# 每个子目录必须为构建它所贡献的源提供规则
Component/Middle_Layer/%.o Component/Middle_Layer/%.su Component/Middle_Layer/%.cyclo: ../Component/Middle_Layer/%.c Component/Middle_Layer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component" -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component/APP_Layer" -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component/Driver_Layer" -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component/Middle_Layer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Component-2f-Middle_Layer

clean-Component-2f-Middle_Layer:
	-$(RM) ./Component/Middle_Layer/middle_printf.cyclo ./Component/Middle_Layer/middle_printf.d ./Component/Middle_Layer/middle_printf.o ./Component/Middle_Layer/middle_printf.su

.PHONY: clean-Component-2f-Middle_Layer

