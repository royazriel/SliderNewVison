################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
bridge_tcp2uart.obj: ../bridge_tcp2uart.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/include" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/source" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/oslib" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/inc" -g --define=ccs --define=USE_TIRTOS --define=SL_PLATFORM_MULTI_THREADED --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="bridge_tcp2uart.pp" --cmd_file="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/ti_rtos/ti_rtos_config/ccs/Default/configPkg/compiler.opt" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

gpio_if.obj: ../gpio_if.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/include" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/source" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/oslib" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/inc" -g --define=ccs --define=USE_TIRTOS --define=SL_PLATFORM_MULTI_THREADED --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="gpio_if.pp" --cmd_file="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/ti_rtos/ti_rtos_config/ccs/Default/configPkg/compiler.opt" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/include" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/source" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/oslib" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/inc" -g --define=ccs --define=USE_TIRTOS --define=SL_PLATFORM_MULTI_THREADED --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" --cmd_file="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/ti_rtos/ti_rtos_config/ccs/Default/configPkg/compiler.opt" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pinmux.obj: ../pinmux.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/include" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/source" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/oslib" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/inc" -g --define=ccs --define=USE_TIRTOS --define=SL_PLATFORM_MULTI_THREADED --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="pinmux.pp" --cmd_file="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/ti_rtos/ti_rtos_config/ccs/Default/configPkg/compiler.opt" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart_if.obj: ../uart_if.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/include" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/simplelink/source" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/example/common" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/oslib" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/driverlib" --include_path="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/inc" -g --define=ccs --define=USE_TIRTOS --define=SL_PLATFORM_MULTI_THREADED --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="uart_if.pp" --cmd_file="C:/ti/CC3200SDK_1.0.0/cc3200-sdk/ti_rtos/ti_rtos_config/ccs/Default/configPkg/compiler.opt" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


