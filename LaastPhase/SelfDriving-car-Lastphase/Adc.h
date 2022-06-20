/*
 * Adc.h
 *
 * Created: 6/20/2022 9:46:33 PM
 *  Author: DELL
 */ 


#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
void adc_init(void);
uint16_t read_adc(uint8_t channel);
void seed_init();





#endif /* ADC_H_ */