#ifndef COOOLER_H_
#define COOOLER_H_

#define TEMPERATURE_FOR_ENABLING_COOL 30
#define TEMPERATURE_FOR_DISABLING_COOL 27

#define COOLER_RCC_PERIPH_PORT RCC_APB2Periph_GPIOB
#define COOLER_PORT GPIOB
#define COOLER_PIN GPIO_Pin_6

void enableCooler();
void disableCooler();
void checkSystemTemperature();
void initCooler();

#endif
