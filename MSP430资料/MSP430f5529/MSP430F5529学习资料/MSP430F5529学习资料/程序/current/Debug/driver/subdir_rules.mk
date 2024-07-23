################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
driver/DELAY.obj: ../driver/DELAY.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/ccs/ccsv8/ccs_base/msp430/include" --include_path="D:/cefclient/CCSworkspace/current/app" --include_path="D:/cefclient/CCSworkspace/current/user" --include_path="D:/cefclient/CCSworkspace/current/driver" --include_path="D:/cefclient/CCSworkspace/current" --include_path="D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="driver/DELAY.d_raw" --obj_directory="driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

driver/GPIO.obj: ../driver/GPIO.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/ccs/ccsv8/ccs_base/msp430/include" --include_path="D:/cefclient/CCSworkspace/current/app" --include_path="D:/cefclient/CCSworkspace/current/user" --include_path="D:/cefclient/CCSworkspace/current/driver" --include_path="D:/cefclient/CCSworkspace/current" --include_path="D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="driver/GPIO.d_raw" --obj_directory="driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

driver/Interrupt.obj: ../driver/Interrupt.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/ccs/ccsv8/ccs_base/msp430/include" --include_path="D:/cefclient/CCSworkspace/current/app" --include_path="D:/cefclient/CCSworkspace/current/user" --include_path="D:/cefclient/CCSworkspace/current/driver" --include_path="D:/cefclient/CCSworkspace/current" --include_path="D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="driver/Interrupt.d_raw" --obj_directory="driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

driver/Key.obj: ../driver/Key.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/ccs/ccsv8/ccs_base/msp430/include" --include_path="D:/cefclient/CCSworkspace/current/app" --include_path="D:/cefclient/CCSworkspace/current/user" --include_path="D:/cefclient/CCSworkspace/current/driver" --include_path="D:/cefclient/CCSworkspace/current" --include_path="D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="driver/Key.d_raw" --obj_directory="driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

driver/LED.obj: ../driver/LED.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/ccs/ccsv8/ccs_base/msp430/include" --include_path="D:/cefclient/CCSworkspace/current/app" --include_path="D:/cefclient/CCSworkspace/current/user" --include_path="D:/cefclient/CCSworkspace/current/driver" --include_path="D:/cefclient/CCSworkspace/current" --include_path="D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="driver/LED.d_raw" --obj_directory="driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

driver/OLED.obj: ../driver/OLED.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/ccs/ccsv8/ccs_base/msp430/include" --include_path="D:/cefclient/CCSworkspace/current/app" --include_path="D:/cefclient/CCSworkspace/current/user" --include_path="D:/cefclient/CCSworkspace/current/driver" --include_path="D:/cefclient/CCSworkspace/current" --include_path="D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="driver/OLED.d_raw" --obj_directory="driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

driver/PWM.obj: ../driver/PWM.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/ccs/ccsv8/ccs_base/msp430/include" --include_path="D:/cefclient/CCSworkspace/current/app" --include_path="D:/cefclient/CCSworkspace/current/user" --include_path="D:/cefclient/CCSworkspace/current/driver" --include_path="D:/cefclient/CCSworkspace/current" --include_path="D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="driver/PWM.d_raw" --obj_directory="driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

driver/TIME.obj: ../driver/TIME.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/ccs/ccsv8/ccs_base/msp430/include" --include_path="D:/cefclient/CCSworkspace/current/app" --include_path="D:/cefclient/CCSworkspace/current/user" --include_path="D:/cefclient/CCSworkspace/current/driver" --include_path="D:/cefclient/CCSworkspace/current" --include_path="D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="driver/TIME.d_raw" --obj_directory="driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

driver/USART.obj: ../driver/USART.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/ccs/ccsv8/ccs_base/msp430/include" --include_path="D:/cefclient/CCSworkspace/current/app" --include_path="D:/cefclient/CCSworkspace/current/user" --include_path="D:/cefclient/CCSworkspace/current/driver" --include_path="D:/cefclient/CCSworkspace/current" --include_path="D:/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="driver/USART.d_raw" --obj_directory="driver" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


