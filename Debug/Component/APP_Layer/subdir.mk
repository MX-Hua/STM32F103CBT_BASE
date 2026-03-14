################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# 将这些工具调用的输入和输出添加到构建变量 
C_SRCS += \
../Component/APP_Layer/app_user_task.c 

OBJS += \
./Component/APP_Layer/app_user_task.o 

C_DEPS += \
./Component/APP_Layer/app_user_task.d 


# 每个子目录必须为构建它所贡献的源提供规则
Component/APP_Layer/%.o Component/APP_Layer/%.su Component/APP_Layer/%.cyclo: ../Component/APP_Layer/%.c Component/APP_Layer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component" -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component/APP_Layer" -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component/Driver_Layer" -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component/Middle_Layer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Component-2f-APP_Layer

clean-Component-2f-APP_Layer:
	-$(RM) ./Component/APP_Layer/app_user_task.cyclo ./Component/APP_Layer/app_user_task.d ./Component/APP_Layer/app_user_task.o ./Component/APP_Layer/app_user_task.su

.PHONY: clean-Component-2f-APP_Layer

