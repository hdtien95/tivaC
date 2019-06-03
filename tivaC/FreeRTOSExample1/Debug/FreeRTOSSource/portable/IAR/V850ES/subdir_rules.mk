################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FreeRTOSSource/portable/IAR/V850ES/%.obj: ../FreeRTOSSource/portable/IAR/V850ES/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/tivaC/FreeRTOSExample1" --include_path="D:/tivaC/FreeRTOSExample1/vdtrenlop/drivers" --include_path="D:/tivaC/FreeRTOSExample1/FreeRTOSSource/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.5.LTS/include" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOSSource/portable/IAR/V850ES/$(basename $(<F)).d_raw" --obj_directory="FreeRTOSSource/portable/IAR/V850ES" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


