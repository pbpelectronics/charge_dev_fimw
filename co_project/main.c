#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "init_periph.h"
int main(void) {
//	enablePorts();
//	initPorts();
	initADC();

	ADC_Cmd(ADC1, ENABLE);
	while (1) {
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
			;
		double convValue = ADC_GetConversionValue(ADC1);
 		double result = 3.3*convValue/4096.0;
	}
}
