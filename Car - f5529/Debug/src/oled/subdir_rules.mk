################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/oled/%.obj: ../src/oled/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"F:/APP/ti/ccs1271/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="F:/APP/ti/ccs1271/ccs/ccs_base/msp430/include" --include_path="F:/NUEDC/Car - f5529/src/mpu6050" --include_path="F:/NUEDC/Car - f5529/src/mpu6050/eMPL" --include_path="F:/NUEDC/Car - f5529/src/oled" --include_path="F:/NUEDC/Car - f5529/core" --include_path="F:/NUEDC/Car - f5529/src" --include_path="F:/NUEDC/Car - f5529" --include_path="F:/APP/ti/ccs1271/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="src/oled/$(basename $(<F)).d_raw" --obj_directory="src/oled" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


