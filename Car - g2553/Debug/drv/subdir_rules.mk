################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
drv/%.obj: ../drv/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"F:/APP/ti/ccs1271/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="F:/APP/ti/ccs1271/ccs/ccs_base/msp430/include" --include_path="F:/NUEDC/Car/bsp" --include_path="F:/NUEDC/Car/drv" --include_path="F:/NUEDC/Car" --include_path="F:/APP/ti/ccs1271/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power="all" --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="drv/$(basename $(<F)).d_raw" --obj_directory="drv" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


