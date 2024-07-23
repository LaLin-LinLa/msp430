var jsonInfo = [
	{
		"MCU"    : "MSP430",
		"Device" : "MSP430G2x03",
		"Filter" : "MSP430G2\\d03"
	}
];

var jsonObjC = [
	{"SourcePreview" : "msp430g2xx3_1.c",                                   "Description" : "Software Toggle P1.0"},
	{"SourcePreview" : "msp430g2xx3_1_vlo.c",                               "Description" : "Software Toggle P1.0, MCLK = VLO/8"},
	{"SourcePreview" : "msp430g2xx3_clks.c",                                "Description" : "Basic Clock, Output Buffered SMCLK, ACLK and MCLK/10"},
	{"SourcePreview" : "msp430g2xx3_dco_calib.c",                           "Description" : "Basic Clock with preloaded DCO calibration constants "},
	{"SourcePreview" : "msp430g2xx3_dco_flashcal.c",                        "Description" : "DCO Calibration Constants Programmer"},
	{"SourcePreview" : "msp430g2xx3_flashwrite_01.c",                       "Description" : "Flash In-System Programming, Copy SegC to SegD"},
	{"SourcePreview" : "msp430g2xx3_LFxtal_nmi.c",                          "Description" : "LFXT1 Oscillator Fault Detection"},
	{"SourcePreview" : "msp430g2xx3_lpm3.c",                                "Description" : "Basic Clock, LPM3 Using WDT ISR, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_lpm3_vlo.c",                            "Description" : "Basic Clock, LPM3 Using WDT ISR, VLO ACLK"},
	{"SourcePreview" : "msp430g2xx3_nmi.c",                                 "Description" : "Basic Clock, Configure RST/NMI as NMI"},
	{"SourcePreview" : "msp430g2xx3_P1_01.c",                               "Description" : "Software Poll P1.4, Set P1.0 if P1.4 = 1"},
	{"SourcePreview" : "msp430g2xx3_P1_02.c",                               "Description" : "Software Port Interrupt Service on P1.4 from LPM4"},
	{"SourcePreview" : "msp430g2xx3_P1_03.c",                               "Description" : "Poll P1 With Software with Internal Pull-up"},
	{"SourcePreview" : "msp430g2xx3_P1_04.c",                               "Description" : "P1 Interrupt from LPM4 with Internal Pull-up"},
	{"SourcePreview" : "msp430g2xx3_ta_01.c",                               "Description" : "Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK"},
	{"SourcePreview" : "msp430g2xx3_ta_02.c",                               "Description" : "Timer_A, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK"},
	{"SourcePreview" : "msp430g2xx3_ta_03.c",                               "Description" : "Timer_A, Toggle P1.0, Overflow ISR, DCO SMCLK"},
	{"SourcePreview" : "msp430g2xx3_ta_04.c",                               "Description" : "Timer_A, Toggle P1.0, Overflow ISR, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_ta_05.c",                               "Description" : "Timer_A, Toggle P1.0, CCR0 Up Mode ISR, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_ta_06.c",                               "Description" : "Timer_A, Toggle P1.0, CCR1 Cont. Mode ISR, DCO SMCLK"},
	{"SourcePreview" : "msp430g2xx3_ta_07.c",                               "Description" : "Timer_A, Toggle P1.0-2, Cont. Mode ISR, DCO SMCLK"},
	{"SourcePreview" : "msp430g2xx3_ta_08.c",                               "Description" : "Timer_A, Toggle P1.0-2, Cont. Mode ISR, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_ta_10.c",                               "Description" : "Timer_A, Toggle P1.1/TA0, Up Mode, DCO SMCLK"},
	{"SourcePreview" : "msp430g2xx3_ta_11.c",                               "Description" : "Timer_A, Toggle P1.1/TA0, Up Mode, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_ta_13.c",                               "Description" : "Timer_A, Toggle P1.1/TA0, Up/Down Mode, DCO SMCLK"},
	{"SourcePreview" : "msp430g2xx3_ta_14.c",                               "Description" : "Timer_A, Toggle P1.1/TA0, Up/Down Mode, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_ta_16.c",                               "Description" : "Timer_A, PWM TA1-2, Up Mode, DCO SMCLK"},
	{"SourcePreview" : "msp430g2xx3_ta_17.c",                               "Description" : "Timer_A, PWM TA1, Up Mode, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_ta_19.c",                               "Description" : "Timer_A, PWM TA1, Up/Down Mode, DCO SMCLK"},
	{"SourcePreview" : "msp430g2xx3_ta_20.c",                               "Description" : "Timer_A, PWM TA1, Up/Down Mode, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_ta_21.c",                               "Description" : "Timer_A, Normal Timer Mode Input Period and Duty Cycle Measurement"},
	{"SourcePreview" : "msp430g2xx3_ta_uart2400.c",                         "Description" : "Timer_A, Ultra-Low Pwr UART 2400 Echo, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_ta_uart9600.c",                         "Description" : "Timer_A, Ultra-Low Pwr Full-duplex UART 9600, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_uscia0_irda_01.c",                      "Description" : "USCI_A0 IrDA External Loopback Test, 8MHz SMCLK"},
	{"SourcePreview" : "msp430g2xx3_uscia0_irda_02.c",                      "Description" : "USCI_A0 IrDA Monitor, 8MHz SMCLK"},
	{"SourcePreview" : "msp430g2xx3_uscia0_irda_03.c",                      "Description" : "USCI_A0 IrDA Physical Layer Comm, 8MHz SMCLK"},
	{"SourcePreview" : "msp430g2xx3_uscia0_spi_09.c",                       "Description" : "USCI_A0, SPI 3-Wire Master Incremented Data"},
	{"SourcePreview" : "msp430g2xx3_uscia0_spi_10.c",                       "Description" : "USCI_A0, SPI 3-Wire Slave Data Echo"},
	{"SourcePreview" : "msp430g2xx3_uscia0_uart_01_115k.c",                 "Description" : "USCI_A0, 115200 UART Echo ISR, DCO SMCLK"},
	{"SourcePreview" : "msp430g2xx3_uscia0_uart_01_115k_lpm.c",             "Description" : "USCI_A0, 115200 UART Echo ISR, DCO SMCLK, LPM4"},
	{"SourcePreview" : "msp430g2xx3_uscia0_uart_01_19200.c",                "Description" : "USCI_A0, 19200 UART Echo ISR, DCO SMCLK"},
	{"SourcePreview" : "msp430g2xx3_uscia0_uart_01_9600.c",                 "Description" : "USCI_A0, 9600 UART Echo ISR, DCO SMCLK"},
	{"SourcePreview" : "msp430g2xx3_uscia0_uart_05_9600.c",                 "Description" : "USCI_A0, Ultra-Low Pwr UART 9600 Echo ISR, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_uscia0_uart_06_9600.c",                 "Description" : "USCI_A0, Ultra-Low Pwr UART 9600 String, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_uscia0_uart_07_9600.c",                 "Description" : "USCI_A0, Ultra-Low Pwr UART 9600 RX/TX, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_uscia0_uart_08_9600.c",                 "Description" : "USCI_A0, UART 9600 Full-Duplex Transceiver, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_uscib0_i2c_01.c",                       "Description" : "USCI_B0 I2C Master to TMP100, Set P1.0 if Temp > 28C"},
	{"SourcePreview" : "msp430g2xx3_uscib0_i2c_02.c",                       "Description" : "USCI_B0 I2C Master Interface to PCF8574, Read/Write"},
	{"SourcePreview" : "msp430g2xx3_uscib0_i2c_03.c",                       "Description" : "USCI_B0 I2C Master Interface to DAC8571, Write"},
	{"SourcePreview" : "msp430g2xx3_uscib0_i2c_04.c",                       "Description" : "USCI_B0 I2C Master RX single bytes from MSP430 Slave"},
	{"SourcePreview" : "msp430g2xx3_uscib0_i2c_05.c",                       "Description" : "USCI_B0 I2C Slave TX single bytes to MSP430 Master"},
	{"SourcePreview" : "msp430g2xx3_uscib0_i2c_06.c",                       "Description" : "USCI_B0 I2C Master TX single bytes to MSP430 Slave"},
	{"SourcePreview" : "msp430g2xx3_uscib0_i2c_07.c",                       "Description" : "USCI_B0 I2C Slave RX single bytes from MSP430 Master"},
	{"SourcePreview" : "msp430g2xx3_uscib0_i2c_08.c",                       "Description" : "USCI_B0 I2C Master TX multiple bytes to MSP430 Slave"},
	{"SourcePreview" : "msp430g2xx3_uscib0_i2c_09.c",                       "Description" : "USCI_B0 I2C Slave RX multiple bytes from MSP430 Master"},
	{"SourcePreview" : "msp430g2xx3_uscib0_i2c_10.c",                       "Description" : "USCI_B0 I2C Master RX multiple bytes from MSP430 Slave"},
	{"SourcePreview" : "msp430g2xx3_uscib0_i2c_11.c",                       "Description" : "USCI_B0 I2C Slave TX multiple bytes to MSP430 Master"},
	{"SourcePreview" : "msp430g2xx3_uscib0_i2c_12.c",                       "Description" : "USCI_B0 I2C Master TX/RX multiple bytes from MSP430 Slave with a repeated start in between TX and RX operations."},
	{"SourcePreview" : "msp430g2xx3_uscib0_i2c_13.c",                       "Description" : "USCI_B0 I2C Slave RX/TX multiple bytes to MSP430 Master"},
	{"SourcePreview" : "msp430g2xx3_usci_i2c_standard_master.c",            "Description" : "USCI_B0, I2C Master multiple byte TX/RX"},
	{"SourcePreview" : "msp430g2xx3_usci_i2c_standard_slave.c",             "Description" : "USCI_B0, I2C Slave multiple byte TX/RX"},
	{"SourcePreview" : "msp430g2xx3_usci_spi_standard_master.c",            "Description" : "USCI_A0, SPI 3-Wire Master multiple byte RX/TX"},
	{"SourcePreview" : "msp430g2xx3_usci_spi_standard_slave.c",             "Description" : "USCI_A0, SPI 3-Wire Slave multiple byte RX/TX"},
	{"SourcePreview" : "msp430g2xx3_usci_uart_standard_transceiver.c",      "Description" : "USCI_A0, UART Echo received character"},
	{"SourcePreview" : "msp430g2xx3_wdt_01.c",                              "Description" : "WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK"},
	{"SourcePreview" : "msp430g2xx3_wdt_02.c",                              "Description" : "WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_wdt_04.c",                              "Description" : "WDT+ Failsafe Clock, DCO SMCLK"},
	{"SourcePreview" : "msp430g2xx3_wdt_05.c",                              "Description" : "Reset on Invalid Address fetch, Toggle P1.0"},
	{"SourcePreview" : "msp430g2xx3_wdt_06.c",                              "Description" : "WDT+ Failsafe Clock, 32kHz ACLK"},
	{"SourcePreview" : "msp430g2xx3_wdt_07.c",                              "Description" : "WDT+ periodic reset"}
];

