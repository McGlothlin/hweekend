// adc.c
// Kyle Dillon 4/30/14
// Simple init and read ADC library for Teensy 2.0.
#include "adc.h"

//	init_adc
// Initalize ADC for single shot mode
void init_adc() {
	DDRF &= 0b11111110; // Pin F0 as inputs.
	PORTF &= 0b11111110; // Turn off F0 pull up.
	ADMUX |= (1<<REFS0); // Single-ended, right adjusted for 10 bits, AVCC as ref voltage
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<< ADPS1) | (1<<ADPS0); //ADC enabled, single shot mode, division factor is 128 (125khz)
}

//	read_adc
// Read specificed adc 0-7
uint16_t read_adc(uint8_t adc) {
	ADMUX &= 0b11100000; // Clear the adc select bits
	ADMUX |= adc; // Set the selected adc bits
	asm("nop"); asm("nop"); // Slight delay
	ADCSRA |= (1<<ADSC); // Poke ADSC and start conversion
  	while(bit_is_clear(ADCSRA, ADIF)); // Spin while interrupt flag not set (conversion not done)
  	ADCSRA |= (1<<ADIF); // When done, clear flag by writing a one 
  	uint16_t adc_result = ADC; // Read the ADC output as 16 bits
	return adc_result;	
}

