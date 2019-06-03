################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FreeRTOSSource/%.obj: ../FreeRTOSSource/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/tivaC/FreeRTOS/FreeRTOS_example9" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="D:/tivaC/FreeRTOS/FreeRTOSSource/include" --include_path="D:/tivaC/FreeRTOS/FreeRTOS_example9/Application" --include_path="D:/tivaC/FreeRTOS/FreeRTOS_example9/driver" --include_path="D:/tivaC/FreeRTOS/FreeRTOS_example9/FreeRTOSSource" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOSSource/$(basename $(<F)).d_raw" --obj_directory="FreeRTOSSource" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOSSource/%.obj: ../FreeRTOSSource/%.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/tivaC/FreeRTOS/FreeRTOS_example9" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="D:/tivaC/FreeRTOS/FreeRTOSSource/include" --include_path="D:/tivaC/FreeRTOS/FreeRTOS_example9/Application" --include_path="D:/tivaC/FreeRTOS/FreeRTOS_example9/driver" --include_path="D:/tivaC/FreeRTOS/FreeRTOS_example9/FreeRTOSSource" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.4.LTS/include" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOSSource/$(basename $(<F)).d_raw" --obj_directory="FreeRTOSSource" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


