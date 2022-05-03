################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Final_Project.c \
../source/LM35.c \
../source/MMA8451Q.c \
../source/adc.c \
../source/calibrate.c \
../source/gpio.c \
../source/i2c.c \
../source/init.c \
../source/lcd.c \
../source/led.c \
../source/mtb.c \
../source/pwm.c \
../source/roll_pitch.c \
../source/semihost_hardfault.c \
../source/systick.c 

OBJS += \
./source/Final_Project.o \
./source/LM35.o \
./source/MMA8451Q.o \
./source/adc.o \
./source/calibrate.o \
./source/gpio.o \
./source/i2c.o \
./source/init.o \
./source/lcd.o \
./source/led.o \
./source/mtb.o \
./source/pwm.o \
./source/roll_pitch.o \
./source/semihost_hardfault.o \
./source/systick.o 

C_DEPS += \
./source/Final_Project.d \
./source/LM35.d \
./source/MMA8451Q.d \
./source/adc.d \
./source/calibrate.d \
./source/gpio.d \
./source/i2c.d \
./source/init.d \
./source/lcd.d \
./source/led.d \
./source/mtb.d \
./source/pwm.d \
./source/roll_pitch.d \
./source/semihost_hardfault.d \
./source/systick.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"/Users/prasunbiswas/Desktop/PES-ASSIGNMENT5-main/PBKDF2/source/Final_Project/board" -I"/Users/prasunbiswas/Desktop/PES-ASSIGNMENT5-main/PBKDF2/source/Final_Project/source" -I"/Users/prasunbiswas/Desktop/PES-ASSIGNMENT5-main/PBKDF2/source/Final_Project" -I"/Users/prasunbiswas/Desktop/PES-ASSIGNMENT5-main/PBKDF2/source/Final_Project/drivers" -I"/Users/prasunbiswas/Desktop/PES-ASSIGNMENT5-main/PBKDF2/source/Final_Project/CMSIS" -I"/Users/prasunbiswas/Desktop/PES-ASSIGNMENT5-main/PBKDF2/source/Final_Project/utilities" -I"/Users/prasunbiswas/Desktop/PES-ASSIGNMENT5-main/PBKDF2/source/Final_Project/startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


