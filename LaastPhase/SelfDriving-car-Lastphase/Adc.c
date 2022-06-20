/*
 * Adc.c
 *
 * Created: 6/20/2022 9:46:22 PM
 *  Author: DELL
 */ 
#include "Adc.h"
#include <avr/io.h>



void adc_init(void){
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));   // 16Mhz/128 = 125Khz the ADC reference clock
	ADMUX |= (1<<REFS0);                            // Voltage reference from Avcc (5v)
	ADCSRA |= (1<<ADEN);                            // Turn on ADC
	ADCSRA |= (1<<ADSC);                            // Do an initial conversion because this one is the slowest and to ensure that everything is up and running
}
uint16_t read_adc(uint8_t channel){
	ADMUX &= 0xF0;                            // Clear the older channel that was read
	ADMUX |= channel;                            // Defines the new ADC channel to be read
	ADCSRA |= (1<<ADSC);                            // Starts a new conversion
	while(ADCSRA & (1<<ADSC));                        // Wait until the conversion is done
	return ADCW;                                // Returns the ADC value of the chosen channel
}
void seed_init()
{
	uint16_t u_rand_val = 0;
	uint16_t u_seed_rand_val = 0;
	adc_init();
	//Note we're assuming the channel that you are reading from is FLOATING or hooked up to something very noisy.
	//Gather bits from the adc, pushing them into your pseudorandom seed.
	for(uint8_t i=0; i<16; i++){
		u_seed_rand_val = u_seed_rand_val<<1 | (read_adc(i)&0b1);
	}
	srand (u_seed_rand_val);

}