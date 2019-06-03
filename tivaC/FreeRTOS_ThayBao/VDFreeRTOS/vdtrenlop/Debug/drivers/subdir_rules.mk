################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
drivers/buttons.obj: ../drivers/buttons.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.9.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop" --include_path="D:/BAO/EmbeddedProgExample/FreeRTOS/FreeRTOSv10.0.1/FreeRTOS/Source/include" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop/Application" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop/driver" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop/FreeRTOS" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.9.0.STS/include" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="drivers/buttons.d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

drivers/led.obj: ../drivers/led.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.9.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop" --include_path="D:/BAO/EmbeddedProgExample/FreeRTOS/FreeRTOSv10.0.1/FreeRTOS/Source/include" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop/Application" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop/driver" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop/FreeRTOS" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.9.0.STS/include" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="drivers/led.d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

drivers/rgb.obj: ../drivers/rgb.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.9.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop" --include_path="D:/BAO/EmbeddedProgExample/FreeRTOS/FreeRTOSv10.0.1/FreeRTOS/Source/include" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop/Application" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop/driver" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop/FreeRTOS" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.9.0.STS/include" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="drivers/rgb.d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

drivers/switches.obj: ../drivers/switches.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.9.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop" --include_path="D:/BAO/EmbeddedProgExample/FreeRTOS/FreeRTOSv10.0.1/FreeRTOS/Source/include" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop/Application" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop/driver" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop/FreeRTOS" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.9.0.STS/include" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="drivers/switches.d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

drivers/uartstdio.obj: ../drivers/uartstdio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.9.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop" --include_path="D:/BAO/EmbeddedProgExample/FreeRTOS/FreeRTOSv10.0.1/FreeRTOS/Source/include" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop/Application" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop/driver" --include_path="D:/BAO/EmbeddedProgExample/TVALab/vdtrenlop/FreeRTOS" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_17.9.0.STS/include" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="drivers/uartstdio.d_raw" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


