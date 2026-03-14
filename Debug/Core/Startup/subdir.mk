################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# 将这些工具调用的输入和输出添加到构建变量 
S_SRCS += \
../Core/Startup/startup_stm32f103cbtx.s 

OBJS += \
./Core/Startup/startup_stm32f103cbtx.o 

S_DEPS += \
./Core/Startup/startup_stm32f103cbtx.d 


# 每个子目录必须为构建它所贡献的源提供规则
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -DDEBUG -c -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component" -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component/APP_Layer" -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component/Driver_Layer" -I"E:/STM32/F103CBT6Project/STM32F103CBT6_LED/Component/Middle_Layer" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f103cbtx.d ./Core/Startup/startup_stm32f103cbtx.o

.PHONY: clean-Core-2f-Startup

