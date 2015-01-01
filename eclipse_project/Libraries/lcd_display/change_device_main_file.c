/*
 * ChangeDevice.c
 *
 * Created: 18.01.2013 3:04:47
 *  Author: Олексій
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "pictures.h"
#include "macroces.h"

//--------------------Global Variables-----------------------------------------------------------
char activeMeasuring;							//flag for choose active ADC line
double uFromAKB;								//voltage of AKB
double uSigToAKB;								//voltage of charge signal
double chargeCurrent;							//current of charge signal
double temperature;								//temperature

long int bufer1ForAdc[2];						//for measure voltage of AKB
long int bufer2ForAdc[2];

int chargeTemperatureAdc[2];					//

volatile unsigned long currentTimeMs;							//current time in ms

unsigned long timeForEndMeasuring;					//time when end current measuring
unsigned long timeForEncoder;

unsigned char currentPowerValue = 0;
unsigned char lastPowerImageNumber;

//processing interrupt from ADC
ISR(ADC_vect)
{
	switch (activeMeasuring) {
		//if measuring voltage on AKB
		case (VOLT_MEASURING): measuringVoltageOnAkb(); break;
		case (CURRENT_MEASURING): measuringCurrentOfChargeSig(); break;
		case (TEMPER_MEASUTING): measuringTemperature(); break;
	}
	setADCChanal(activeMeasuring);
	ADC_START_CONVERTATION;
}

ISR (INT0_vect) {

}

ISR (TIMER2_OVF_vect) {
	TCNT2=NTC2;
	currentTimeMs++;
}

//measuring voltage on AKB
void measuringVoltageOnAkb() {
	//if time for current measuring is not released save result else calculate result
	if (currentTimeMs < timeForEndMeasuring) {
		if (ADC<VOTAGE_OF_CHARGED_AKB_ADC) {
			//first element save values of convert
			bufer1ForAdc[0] += ADC;
			//last element of uFromAKBAdc is count of measuring and show next index for save in array
			bufer1ForAdc[1]++;
		} else {
			//first element save values of convert
			bufer2ForAdc[0] += ADC;
			//last element of uFromAKBAdc is count of measuring and show next index for save in array
			bufer2ForAdc[1]++;
		}
	} else {
		//calculate result as average of each value
		if (bufer1ForAdc[1]!=0) {
			uFromAKB = bufer1ForAdc[0]*KOEF_FOR_ADC_VOLTAGE/bufer1ForAdc[1];
		}		
		if (bufer2ForAdc[1]!=0) {
			uSigToAKB = bufer2ForAdc[0]*KOEF_FOR_ADC_VOLTAGE/bufer2ForAdc[1];
		}		
		//clear buffers
		clearBufers();
		//next measuring is current of charge signal
		activeMeasuring = CURRENT_MEASURING;
		//set period of measuring
		timeForEndMeasuring = currentTimeMs + ADC_MEASURING_TIMEOUT;
	}
}

//measuring current of charge signal
void measuringCurrentOfChargeSig() {
	if (currentTimeMs < timeForEndMeasuring) {
		bufer1ForAdc[0] += ADC;
		bufer1ForAdc[1]++;
	} else {
		//calculate result as average of each value
		chargeCurrent = bufer1ForAdc[0]*KOEF_FOR_ADC_CURRENT/bufer1ForAdc[1];
		//clear buffers
		clearBufers();
		//next measuring is temperature
		activeMeasuring = TEMPER_MEASUTING;
	}
}

//measuring temperature
void measuringTemperature() {
	//get 3 values from ADC and calculate average
	if (bufer1ForAdc[1]<3) {
		bufer1ForAdc[0]+=ADC;
		bufer1ForAdc[1]++;
	} else {
		temperature=bufer1ForAdc[0]/bufer1ForAdc[1]*KOEF_FOR_ADC_TEMPERATURE;
		//clear buffers
		clearBufers();
		//next measuring is voltage
		activeMeasuring = VOLT_MEASURING;
		//set period of measuring
		timeForEndMeasuring = currentTimeMs + ADC_MEASURING_TIMEOUT;
	}
}

//clear buffer arrays witch are used for ADC calculations.
void clearBufers() {
	bufer1ForAdc[0]=0;
	bufer1ForAdc[1]=0;
	bufer2ForAdc[0]=0;
	bufer2ForAdc[1]=0;
}

void setADCChanal(int chanal) {
	switch(chanal){
		case (1): ADMUX&=~(1<<1); ADMUX&=~(1<<0); break;
		case (2): ADMUX&=~(1<<1); ADMUX|=(1<<0); break; 
		case (3): ADMUX|=(1<<1); ADMUX&=~(1<<0); break;
	}
}

//initialization timer ТС0 for interrupt every 1 ms
void InitCountTimer()
{
	currentTimeMs=0;
	TC2_SET_NORMAL_MODE;
	TC2_EN_INTERRUPT_FOR_COUNT;
	TCNT2=NTC2;
	TC2_START_WITH_FREQ_DIV_64;
}

void initPWM() {
	TC3_SET_OC1A_AS_NOT_INV_PWM_OUT;
	TC3_SET_OC1B_AS_NOT_INV_PWM_OUT;
	TC3_SET_OC1C_AS_NOT_INV_PWM_OUT;
	TC3_PWM_PHASE_COR_ICR;
	ICR3=TC3_TOP_VALUE;
	OCR3A=0;
	TC3_START_WITH_FREQ_DIV_8;
}

void initADC() {
	ADC_ENABLE_INTERUPT;
	ADC_SET_FREQ_DIV_4;
	ADC_SET_INT_VREF;
	activeMeasuring = VOLT_MEASURING;
	setADCChanal(VOLT_MEASURING);
	timeForEndMeasuring=currentTimeMs+ADC_MEASURING_TIMEOUT;
	ADC_ENABLE_MODULE;
	ADC_START_CONVERTATION;
}

//check if battery is connected right and print message if not
void batteryConnectionCheck() {
	if (uFromAKB<=MIN_VOLTAGE_FROM_AKB) {
			nlcd_Pict(0, 0, bat_not_conn_image);		
	}
	while (uFromAKB<=MIN_VOLTAGE_FROM_AKB);	
	
	//clear display and return
	nlcd_Clear();

}

void encoderInit() {
	short temp = ((1<<ENCODER_LEFT_CONTACT_PIN)|(1<<ENCODER_MENU_CONTACT_PIN)|(1<<ENCODER_RIGHT_CONTACT_PIN));
	ENCODER_DDR &= ~(temp);
	ENCODER_PORT |= temp;
}

//initialization of resources
void initResurses() {
	InitCountTimer();
	nlcd_Init();
	encoderInit();
	initPWM();
	initADC();
}

//set current value (power value)
setPowerValue(char powerValue) {
	OCR3A = powerValue*MAX_POWER_VALUE/TC3_TOP_VALUE;
}

void menu() {
	nlcd_Clear();
	//to do!!!!!!!!!
	//print current
	unsigned long timeForMenu = currentTimeMs + MENU_PAUSE_MS;
	char currentPowerImageNumber = currentPowerValue*POWER_IMAGE_NUMBER_COEF;
	for (char i=0; i<=currentPowerImageNumber; i++) {
		char powerImageXPosition = POWER_IMAGE_LEFT_INDENT + POWER_IMAGE_WIDTH*i;
		nlcd_Pict(powerImageXPosition, POWER_IMAGE_Y_POSITION, power_images[currentPowerImageNumber]);
	}
	lastPowerImageNumber = currentPowerImageNumber;
	
	while (timeForMenu<currentTimeMs) {
		int encoderValue = getEncoderValue();
		if (encoderValue==ENCODER_DERCREMENT) {
			currentPowerValue-=DELTA_POWER_VALUE;
			if (currentPowerValue<0) {
				currentPowerValue = 0;
			}
			setPowerValue(currentPowerValue);
			
			currentPowerImageNumber = currentPowerValue*POWER_IMAGE_NUMBER_COEF;
			if (currentPowerImageNumber<lastPowerImageNumber) {
				char powerImageXPosition = POWER_IMAGE_LEFT_INDENT + POWER_IMAGE_WIDTH*lastPowerImageNumber;
				nlcd_Pict(powerImageXPosition, POWER_IMAGE_Y_POSITION, power_images[0]);
				lastPowerImageNumber = currentPowerImageNumber;
			}
			timeForMenu = currentTimeMs + MENU_PAUSE_MS;
		} else if (encoderValue==ENCODER_INCREMENT) {
			currentPowerValue+=DELTA_POWER_VALUE;
			if (currentPowerValue>MAX_POWER_VALUE) {
				currentPowerValue = MAX_POWER_VALUE;
			}
			setPowerValue(currentPowerValue);
			
			currentPowerImageNumber = currentPowerValue*POWER_IMAGE_NUMBER_COEF;
			if (currentPowerImageNumber>lastPowerImageNumber) {
				char powerImageXPosition = POWER_IMAGE_LEFT_INDENT + POWER_IMAGE_WIDTH*currentPowerImageNumber;
				nlcd_Pict(powerImageXPosition, POWER_IMAGE_Y_POSITION, power_images[currentPowerImageNumber]);
				lastPowerImageNumber = currentPowerImageNumber;
			}
			timeForMenu = currentTimeMs + MENU_PAUSE_MS;
		} else if (encoderValue==ENCODER_MENU) {
			break;
		}
		
		while ((!ENCODER_IS_ACTIVE)&&(timeForMenu<currentTimeMs)) {
			//todo!!!!!!!!!!
			//print value of current
		}
	}
	nlcd_Clear();
	printMainImageTemplate();
		
}

void recalculateTimeVariables() 
{
	timeForEndMeasuring=timeForEndMeasuring-currentTimeMs;
	timeForEncoder=timeForEncoder-currentTimeMs;
	currentTimeMs=0;
}

unsigned int getTimeByTimeOut(unsigned int timeout) 
{
	unsigned int result = currentTimeMs + timeout;
	if (result<currentTimeMs) {
		recalculateTimeVariables();
	}
	return currentTimeMs + timeout;
}

int getEncoderValue() {
	char str[10];
	if (ENCODER_IS_MENU_CONTACT) {
		return ENCODER_MENU;
	} else if (ENCODER_IS_LEFT_CONTACT) {
		timeForEncoder = getTimeByTimeOut(ENCODER_TIMEOUT);
		while (ENCODER_IS_LEFT_CONTACT){
			if (timeForEncoder<=currentTimeMs) {
				return ENCODER_NOTHING;
			}
		}			
		timeForEncoder=getTimeByTimeOut(ENCODER_TIMEOUT);
		while (!ENCODER_IS_RIGHT_CONTACT) {
			if (timeForEncoder<=currentTimeMs) {
				return ENCODER_NOTHING;
			}
		}
		return ENCODER_DERCREMENT;
	} else if (ENCODER_IS_RIGHT_CONTACT) {
		timeForEncoder = getTimeByTimeOut(ENCODER_TIMEOUT);
		while (ENCODER_IS_RIGHT_CONTACT){
			if (timeForEncoder<=currentTimeMs) {
				return ENCODER_NOTHING;
			}
		}		
		timeForEncoder = getTimeByTimeOut(ENCODER_TIMEOUT);
		while ((!ENCODER_IS_LEFT_CONTACT)&&(timeForEncoder>currentTimeMs)){
			if (timeForEncoder<=currentTimeMs) {
				return ENCODER_NOTHING;
			}
		} 
		return ENCODER_INCREMENT;
	} else {
		return ENCODER_NOTHING;
	}
}

int main(void)
{
	sei();
	initResurses();
	//bootMessage();
//	batteryConnectionCheck();
//	unsigned long timeForButteryImageRefresh = currentTimeMs + BUTTERY_IMAGE_REFRESH_PAUSE_MS;
//	unsigned char currentBatteryImageNumber = 0;
//	printBattaryImage(currentBatteryImageNumber);
	while (1) {
//		if (ENCODER_IS_ACTIVE) {
	//		menu();
		//}
//		if (currentTimeMs>=timeForButteryImageRefresh) {
//			currentBatteryImageNumber++;
	//		if ((currentBatteryImageNumber>uFromAKB*5/15)||(currentBatteryImageNumber>5)) {
//				currentBatteryImageNumber = 0;
//			}
	//		printBattaryImage(currentBatteryImageNumber);
	//		timeForButteryImageRefresh = currentTimeMs + BUTTERY_IMAGE_REFRESH_PAUSE_MS;
		printMainImageTemplate();
		printDigitals(1,uFromAKB);
		printDigitals(2,chargeCurrent);
		OCR3A=800;
		//}
	}
	
	
}
