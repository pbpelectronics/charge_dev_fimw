//------------------------------tuning constants-----------------------------------------------------------
#define KOEF_FOR_ADC_VOLTAGE		0.05343		//koef for convert ADC value to real voltage
#define KOEF_FOR_ADC_CURRENT		0.0075		//koef for convert ADC value to real current
#define KOEF_FOR_ADC_TEMPERATURE	1			//koef for convert ADC value to real temperature

#define MIN_VOLTAGE_FROM_AKB		1	//minimal voltage from AKB in V. If current voltage is less then this value, it is error 

#define CHARGE_SIG_PERIOD			500	//charging signal period ms

//for ADC
#define VOLT_MEASURING				1			//voltage in AKB measuring is active
#define CURRENT_MEASURING			2			//charging signal current measuring is active
#define TEMPER_MEASUTING			3			//temperature measuring is active

#define VOTAGE_OF_CHARGED_AKB		0			//VOTAGE_OF_CHARGED_AKB
#define VOTAGE_OF_CHARGED_AKB_ADC	1000		//VOTAGE_OF_CHARGED_AKB converted for ADC

#define ADC_MEASURING_TIMEOUT		500		//time for measuring of voltage or current
//------------------------------------------------------------------------------------------

//-------------------------Encoder connection-----------------------------------------------
#define ENCODER_PORT				PORTA
#define ENCODER_DDR					DDRA
#define ENCODER_PIN					PINA	

#define ENCODER_LEFT_CONTACT_PIN		0		//number of port pin for left encoder contact (A or 1 contact)
#define ENCODER_RIGHT_CONTACT_PIN		1		//number of port pin for right encoder contact (C or 3 contact)
#define ENCODER_MENU_CONTACT_PIN		2		//number of port pin for menu button encoder contact 

#define ENCODER_TIMEOUT				1000			//timeout between contacts circuiting (in ms)

//------------------------NOT CHANGE!!!-----------------------------------------------------
#define ENCODER_IS_LEFT_CONTACT		(bit_is_clear(ENCODER_PIN,ENCODER_LEFT_CONTACT_PIN)&&bit_is_set(ENCODER_PIN, ENCODER_RIGHT_CONTACT_PIN)&&bit_is_set(ENCODER_PIN, ENCODER_MENU_CONTACT_PIN))	//return true if left contact closed on ground
#define ENCODER_IS_RIGHT_CONTACT	(bit_is_set(ENCODER_PIN,ENCODER_LEFT_CONTACT_PIN)&&bit_is_clear(ENCODER_PIN, ENCODER_RIGHT_CONTACT_PIN)&&bit_is_set(ENCODER_PIN, ENCODER_MENU_CONTACT_PIN))	//return true if right contact closed on ground
#define ENCODER_IS_MENU_CONTACT		(bit_is_set(ENCODER_PIN,ENCODER_LEFT_CONTACT_PIN)&&bit_is_set(ENCODER_PIN, ENCODER_RIGHT_CONTACT_PIN)&&bit_is_clear(ENCODER_PIN, ENCODER_MENU_CONTACT_PIN))	//return true if menu contact closed on ground

#define ENCODER_BIT_MASK			((1<<ENCODER_LEFT_CONTACT_PIN)|(1<<ENCODER_MENU_CONTACT_PIN)|(1<<ENCODER_RIGHT_CONTACT_PIN))
#define ENCODER_IS_ACTIVE			((ENCODER_PIN&ENCODER_BIT_MASK)!=ENCODER_BIT_MASK)		//return true if some contact is closed on ground

#define ENCODER_NOTHING				0
#define ENCODER_INCREMENT			1
#define ENCODER_DERCREMENT			2
#define ENCODER_MENU				3
//------------------------------------------------------------------------------------------

//----------------------Output power control (menu settings)------------------------------------------------
#define MAX_POWER_VALUE				1000
#define DELTA_POWER_VALUE			1
#define DEFAULT_POWER_VALUE			10
#define POWER_IMAGE_NUMBER_COEF		10/MAX_POWER_VALUE

#define MENU_PAUSE_MS				1000

//---------------------------ADC------------------------------------------------------------
#define ADC_SET_FREQ_DIV_128		ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)
#define ADC_SET_FREQ_DIV_64			ADCSRA|=(1<<ADPS2)|(1<<ADPS1); ADCSRA&=~(1<<ADPS0)
#define ADC_SET_FREQ_DIV_32			ADCSRA|=(1<<ADPS2)|(1<<ADPS0); ADCSRA&=~(1<<ADPS1)
#define ADC_SET_FREQ_DIV_16			ADCSRA|=(1<<ADPS2); ADCSRA&=~((1<<ADPS1)|(1<<ADPS0))
#define ADC_SET_FREQ_DIV_8			ADCSRA|=(1<<ADPS1)|(1<<ADPS0); ADCSRA&=~(1<<ADPS2)
#define ADC_SET_FREQ_DIV_4			ADCSRA|=(1<<ADPS1); ADCSRA&=~((1<<ADPS2)|(1<<ADPS0))
#define ADC_SET_FREQ_DIV_2			ADCSRA&=~((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0))
//------------------------------------------------------------------------------------------
#define ADC_ENABLE_INTERUPT			ADCSRA|=(1<<ADIE)										//enable ADC interrupt
#define ADC_DISABLE_INTERUPT		ADCSRA&=~(1<<ADIE)										//disable ADC interrupt
//------------------------------------------------------------------------------------------
#define ADC_SET_EXT_VREF			ADMUX&=~((1<<REFS1)|(1<<REFS0))							//Vref is external, internal is disabled
#define ADC_SET_INT_VREF			ADMUX|=(1<<REFS1)|(1<<REFS0)							//Vref is internal 2.56 V
#define ADC_SET_VCC_VREF			ADMUX&=~(1<<REFS1); ADMUX|=(1<<REFS0)					//Vref is VCC
//------------------------------------------------------------------------------------------
#define ADC_ENABLE_MODULE			ADCSRA|=(1<<ADEN)										//enable ADC module
#define ADC_DISABLE_MODULE			ADCSRA&=~(1<<ADEN)										//disable ADC module
#define ADC_START_CONVERTATION		ADCSRA|=(1<<ADSC)										//start convertation
//------------------------------------------------------------------------------------------

//------------------------TIMER TC0---------------------------------------------------------
#define NTC0						125														//init value for TCNT0
#define TC0_SET_NORMAL_MODE			TCCR0A=0												//set normal mode
#define TC0_EN_INTERRUPT_FOR_COUNT	TIMSK0=_BV(TOIE0)										//enable interrupt for TC0 when counter is fully
#define TC0_DIS_INTERRUPT_FOR_COUNT	TIMSK0=0												//disable interrupt for TC0
#define TC0_START_WITH_FREQ_DIV_64	TCCR0B=(_BV(CS00)|_BV(CS01))							//start TC0 with div main frequency = 64
#define TC0_STOP					TCCR0B=0
//------------------------------------------------------------------------------------------

//------------------------TIMER TC2---------------------------------------------------------
#define NTC2						131														//init value for TCNT0
#define TC2_SET_NORMAL_MODE			TCCR2A=0												//set normal mode
#define TC2_EN_INTERRUPT_FOR_COUNT	TIMSK2=_BV(TOIE2)										//enable interrupt for TC0 when counter is fully
#define TC2_DIS_INTERRUPT_FOR_COUNT	TIMSK2=0												//disable interrupt for TC0
#define TC2_START_WITH_FREQ_DIV_64	TCCR2B=(_BV(CS22))							//start TC0 with div main frequency = 64
#define TC2_STOP					TCCR2B=0
//------------------------------------------------------------------------------------------

//------------------------TIMER TC1----------------------------------------------------------------------------------
#define TC1_NORMAL_MODE				TCCR1B&=~(1<<WGM13); TCCR1B&=~(1<<WGM12); TCCR1A&=~(1<<WGM11); TCCR1A&=~(1<<WGM10)	//set normal mode
#define TC1_PWM_PHASE_COR_8_BIT		TCCR1B&=~(1<<WGM13); TCCR1B&=~(1<<WGM12); TCCR1A&=~(1<<WGM11); TCCR1A|= (1<<WGM10)	//set 8 bit phase correct PWM mode
#define TC1_PWM_PHASE_COR_9_BIT		TCCR1B&=~(1<<WGM13); TCCR1B&=~(1<<WGM12); TCCR1A|= (1<<WGM11); TCCR1A&=~(1<<WGM10)	//set 9 bit phase correct PWM mode
#define TC1_PWM_PHASE_COR_10_BIT	TCCR1B&=~(1<<WGM13); TCCR1B&=~(1<<WGM12); TCCR1A|= (1<<WGM11); TCCR1A|= (1<<WGM10)	//set 10 bit phase correct PWM mode
#define TC1_CTC_FROM_OCR			TCCR1B&=~(1<<WGM13); TCCR1B|= (1<<WGM12); TCCR1A&=~(1<<WGM11); TCCR1A&=~(1<<WGM10)	//set CTC mode, TOP from OCR1A
#define TC1_FAST_PWM_8_BIT			TCCR1B&=~(1<<WGM13); TCCR1B|= (1<<WGM12); TCCR1A&=~(1<<WGM11); TCCR1A|= (1<<WGM10)	//set 8-bit Fast PWM mode
#define TC1_FAST_PWM_9_BIT			TCCR1B&=~(1<<WGM13); TCCR1B|= (1<<WGM12); TCCR1A|= (1<<WGM11); TCCR1A&=~(1<<WGM10)	//set 9-bit Fast PWM mode
#define TC1_FAST_PWM_10_BIT			TCCR1B&=~(1<<WGM13); TCCR1B|= (1<<WGM12); TCCR1A|= (1<<WGM11); TCCR1A|= (1<<WGM10)	//set 10-bit Fast PWM mode
#define TC1_PWM_FREQ_PHASE_COR_ICR	TCCR1B|= (1<<WGM13); TCCR1B&=~(1<<WGM12); TCCR1A&=~(1<<WGM11); TCCR1A&=~(1<<WGM10)	//set Phase and Frequency Correct PWM mode, TOP from ICR1
#define TC1_PWM_FREQ_PHASE_COR_OCR	TCCR1B|= (1<<WGM13); TCCR1B&=~(1<<WGM12); TCCR1A&=~(1<<WGM11); TCCR1A|= (1<<WGM10)	//set Phase and Frequency Correct PWM mode, TOP from OCR1A
#define TC1_PWM_PHASE_COR_ICR		TCCR1B|= (1<<WGM13); TCCR1B&=~(1<<WGM12); TCCR1A|= (1<<WGM11); TCCR1A&=~(1<<WGM10)	//set Phase Correct PWM mode, TOP from ICR1
#define TC1_PWM_PHASE_COR_OCR		TCCR1B|= (1<<WGM13); TCCR1B&=~(1<<WGM12); TCCR1A|= (1<<WGM11); TCCR1A|= (1<<WGM10)	//set Phase Correct PWM mode, TOP from OCR1A
#define TC1_CTC_FROM_ICR			TCCR1B|= (1<<WGM13); TCCR1B|= (1<<WGM12); TCCR1A&=~(1<<WGM11); TCCR1A&=~(1<<WGM10)	//set CTC mode, TOP from ICR1
#define TC1_FAST_PWM_ICR			TCCR1B|= (1<<WGM13); TCCR1B|= (1<<WGM12); TCCR1A|= (1<<WGM11); TCCR1A&=~(1<<WGM10)	//set Fast PWM mode, TOP from ICR1
#define TC1_FAST_PWM_OCR			TCCR1B|= (1<<WGM13); TCCR1B|= (1<<WGM12); TCCR1A|= (1<<WGM11); TCCR1A|= (1<<WGM10)	//set Fast PWM mode, TOP from OCR1

#define TC1_START_WITH_FREQ_DIV_1		TCCR1B&=~(1<<CS12); TCCR1B&=~(1<<CS11); TCCR1B|= (1<<CS10)		//start TC0 with div main frequency to 1
#define TC1_START_WITH_FREQ_DIV_8		TCCR1B&=~(1<<CS12); TCCR1B|= (1<<CS11); TCCR1B&=~(1<<CS10)		//start TC0 with div main frequency to 8
#define TC1_START_WITH_FREQ_DIV_64		TCCR1B&=~(1<<CS12); TCCR1B|= (1<<CS11); TCCR1B|= (1<<CS10)		//start TC0 with div main frequency to 64
#define TC1_START_WITH_FREQ_DIV_256		TCCR1B|= (1<<CS12); TCCR1B&=~(1<<CS11); TCCR1B&=~(1<<CS10)		//start TC0 with div main frequency to 256
#define TC1_START_WITH_FREQ_DIV_1024	TCCR1B|= (1<<CS12); TCCR1B&=~(1<<CS11); TCCR1B|= (1<<CS10)		//start TC0 with div main frequency to 1024
#define TC1_START_WITH_EXT_FREQ_ON_FAL	TCCR1B|= (1<<CS12); TCCR1B|= (1<<CS11); TCCR1B&=~(1<<CS10)		//start TC0 with external clock source on Tn pin. Clock on falling edge
#define TC1_START_WITH_EXT_FREQ_ON_RIS	TCCR1B|= (1<<CS12); TCCR1B|= (1<<CS11); TCCR1B|= (1<<CS10)		//start TC0 with external clock source on Tn pin. Clock on rising edge

#define TC1_SET_OC1A_AS_NOT_INV_PWM_OUT			TCCR1A|= (1<<COM1A1); TCCR1A&=~(1<<COM1A0); DDRB|=(1<<PB5)		//set OC1A as not invert PWM output
#define TC1_SET_OC1B_AS_NOT_INV_PWM_OUT			TCCR1A|= (1<<COM1B1); TCCR1A&=~(1<<COM1B0); DDRB|=(1<<PB6)		//set OC1B as not invert PWM output
#define TC1_SET_OC1C_AS_NOT_INV_PWM_OUT			TCCR1A|= (1<<COM1C1); TCCR1A&=~(1<<COM1C0); DDRB|=(1<<PB7)		//set OC1C as not invert PWM output
#define TC1_SET_OC1A_AS_INV_PWM_OUT				TCCR1A|= (1<<COM1A1); TCCR1A|= (1<<COM1A0); DDRB|=(1<<PB5)		//set OC1A as invert PWM output
#define TC1_SET_OC1B_AS_INV_PWM_OUT				TCCR1A|= (1<<COM1B1); TCCR1A|= (1<<COM1B0); DDRB|=(1<<PB6)		//set OC1B as invert PWM output
#define TC1_SET_OC1C_AS_INV_PWM_OUT				TCCR1A|= (1<<COM1C1); TCCR1A|= (1<<COM1C0); DDRB|=(1<<PB7)		//set OC1C as invert PWM output
#define TC1_DISCONNECT_OC1C						TCCR1A&=~(1<<COM1A1); TCCR1A&=~(1<<COM1A0)							//disconnect OC1A
#define TC1_DISCONNECT_OC1C						TCCR1A&=~(1<<COM1B1); TCCR1A&=~(1<<COM1B0)							//disconnect OC1B
#define TC1_DISCONNECT_OC1C						TCCR1A&=~(1<<COM1C1); TCCR1A&=~(1<<COM1C0)							//disconnect OC1C

#define TC1_TOP_VALUE			MAX_POWER_VALUE		//TOP value for PWM. TOP from ICR1 calculate as: TOP = Fclk/(2*Kdivfreq*Fpwm).
//--------------------------------------------------------------------------------------------------------------------

//------------------------TIMER TC3-----------------------------------------------------------------------------------
#define TC3_NORMAL_MODE				TCCR3B&=~(1<<WGM13); TCCR3B&=~(1<<WGM12); TCCR3A&=~(1<<WGM11); TCCR3A&=~(1<<WGM10)	//set normal mode
#define TC3_PWM_PHASE_COR_8_BIT		TCCR3B&=~(1<<WGM13); TCCR3B&=~(1<<WGM12); TCCR3A&=~(1<<WGM11); TCCR3A|= (1<<WGM10)	//set 8 bit phase correct PWM mode
#define TC3_PWM_PHASE_COR_9_BIT		TCCR3B&=~(1<<WGM13); TCCR3B&=~(1<<WGM12); TCCR3A|= (1<<WGM11); TCCR3A&=~(1<<WGM10)	//set 9 bit phase correct PWM mode
#define TC3_PWM_PHASE_COR_10_BIT	TCCR3B&=~(1<<WGM13); TCCR3B&=~(1<<WGM12); TCCR3A|= (1<<WGM11); TCCR3A|= (1<<WGM10)	//set 10 bit phase correct PWM mode
#define TC3_CTC_FROM_OCR			TCCR3B&=~(1<<WGM13); TCCR3B|= (1<<WGM12); TCCR3A&=~(1<<WGM11); TCCR3A&=~(1<<WGM10)	//set CTC mode, TOP from OCR1A
#define TC3_FAST_PWM_8_BIT			TCCR3B&=~(1<<WGM13); TCCR3B|= (1<<WGM12); TCCR3A&=~(1<<WGM11); TCCR3A|= (1<<WGM10)	//set 8-bit Fast PWM mode
#define TC3_FAST_PWM_9_BIT			TCCR3B&=~(1<<WGM13); TCCR3B|= (1<<WGM12); TCCR3A|= (1<<WGM11); TCCR3A&=~(1<<WGM10)	//set 9-bit Fast PWM mode
#define TC3_FAST_PWM_10_BIT			TCCR3B&=~(1<<WGM13); TCCR3B|= (1<<WGM12); TCCR3A|= (1<<WGM11); TCCR3A|= (1<<WGM10)	//set 10-bit Fast PWM mode
#define TC3_PWM_FREQ_PHASE_COR_ICR	TCCR3B|= (1<<WGM13); TCCR3B&=~(1<<WGM12); TCCR3A&=~(1<<WGM11); TCCR3A&=~(1<<WGM10)	//set Phase and Frequency Correct PWM mode, TOP from ICR1
#define TC3_PWM_FREQ_PHASE_COR_OCR	TCCR3B|= (1<<WGM13); TCCR3B&=~(1<<WGM12); TCCR3A&=~(1<<WGM11); TCCR3A|= (1<<WGM10)	//set Phase and Frequency Correct PWM mode, TOP from OCR1A
#define TC3_PWM_PHASE_COR_ICR		TCCR3B|= (1<<WGM13); TCCR3B&=~(1<<WGM12); TCCR3A|= (1<<WGM11); TCCR3A&=~(1<<WGM10)	//set Phase Correct PWM mode, TOP from ICR1
#define TC3_PWM_PHASE_COR_OCR		TCCR3B|= (1<<WGM13); TCCR3B&=~(1<<WGM12); TCCR3A|= (1<<WGM11); TCCR3A|= (1<<WGM10)	//set Phase Correct PWM mode, TOP from OCR1A
#define TC3_CTC_FROM_ICR			TCCR3B|= (1<<WGM13); TCCR3B|= (1<<WGM12); TCCR3A&=~(1<<WGM11); TCCR3A&=~(1<<WGM10)	//set CTC mode, TOP from ICR1
#define TC3_FAST_PWM_ICR			TCCR3B|= (1<<WGM13); TCCR3B|= (1<<WGM12); TCCR3A|= (1<<WGM11); TCCR3A&=~(1<<WGM10)	//set Fast PWM mode, TOP from ICR1
#define TC3_FAST_PWM_OCR			TCCR3B|= (1<<WGM13); TCCR3B|= (1<<WGM12); TCCR3A|= (1<<WGM11); TCCR3A|= (1<<WGM10)	//set Fast PWM mode, TOP from OCR1

#define TC3_START_WITH_FREQ_DIV_1		TCCR3B&=~(1<<CS12); TCCR3B&=~(1<<CS11); TCCR3B|= (1<<CS10)		//start TC0 with div main frequency to 1
#define TC3_START_WITH_FREQ_DIV_8		TCCR3B&=~(1<<CS12); TCCR3B|= (1<<CS11); TCCR3B&=~(1<<CS10)		//start TC0 with div main frequency to 8
#define TC3_START_WITH_FREQ_DIV_64		TCCR3B&=~(1<<CS12); TCCR3B|= (1<<CS11); TCCR3B|= (1<<CS10)		//start TC0 with div main frequency to 64
#define TC3_START_WITH_FREQ_DIV_256		TCCR3B|= (1<<CS12); TCCR3B&=~(1<<CS11); TCCR3B&=~(1<<CS10)		//start TC0 with div main frequency to 256
#define TC3_START_WITH_FREQ_DIV_1024	TCCR3B|= (1<<CS12); TCCR3B&=~(1<<CS11); TCCR3B|= (1<<CS10)		//start TC0 with div main frequency to 1024
#define TC3_START_WITH_EXT_FREQ_ON_FAL	TCCR3B|= (1<<CS12); TCCR3B|= (1<<CS11); TCCR3B&=~(1<<CS10)		//start TC0 with external clock source on Tn pin. Clock on falling edge
#define TC3_START_WITH_EXT_FREQ_ON_RIS	TCCR3B|= (1<<CS12); TCCR3B|= (1<<CS11); TCCR1B|= (1<<CS10)		//start TC0 with external clock source on Tn pin. Clock on rising edge

#define TC3_SET_OC1A_AS_NOT_INV_PWM_OUT			TCCR3A|= (1<<COM1A1); TCCR3A&=~(1<<COM1A0); DDRC|=(1<<PC6)		//set OC1A as not invert PWM output
#define TC3_SET_OC1B_AS_NOT_INV_PWM_OUT			TCCR3A|= (1<<COM1B1); TCCR3A&=~(1<<COM1B0); DDRC|=(1<<PC5)		//set OC1B as not invert PWM output
#define TC3_SET_OC1C_AS_NOT_INV_PWM_OUT			TCCR3A|= (1<<COM1C1); TCCR3A&=~(1<<COM1C0); DDRC|=(1<<PC4)		//set OC1C as not invert PWM output
#define TC3_SET_OC1A_AS_INV_PWM_OUT				TCCR3A|= (1<<COM1A1); TCCR3A|= (1<<COM1A0); DDRC|=(1<<PC6)		//set OC1A as invert PWM output
#define TC3_SET_OC1B_AS_INV_PWM_OUT				TCCR3A|= (1<<COM1B1); TCCR3A|= (1<<COM1B0); DDRC|=(1<<PC5)		//set OC1B as invert PWM output
#define TC3_SET_OC1C_AS_INV_PWM_OUT				TCCR3A|= (1<<COM1C1); TCCR3A|= (1<<COM1C0); DDRC|=(1<<PC4)		//set OC1C as invert PWM output
#define TC3_DISCONNECT_OC1C						TCCR3A&=~(1<<COM1A1); TCCR3A&=~(1<<COM1A0)							//disconnect OC1A
#define TC3_DISCONNECT_OC1C						TCCR3A&=~(1<<COM1B1); TCCR3A&=~(1<<COM1B0)							//disconnect OC1B
#define TC3_DISCONNECT_OC1C						TCCR3A&=~(1<<COM1C1); TCCR3A&=~(1<<COM1C0)							//disconnect OC1C

#define TC3_TOP_VALUE			MAX_POWER_VALUE			//TOP value for PWM. TOP from ICR1 calculate as: TOP = Fclk/(2*Kdivfreq*Fpwm).
//--------------------------------------------------------------------------------------------------------------------