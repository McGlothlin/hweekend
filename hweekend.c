/*
 * hweekend.c
 * Author: Sean McGlothlin
 * HWeekend Bluetooth R/C Car embedded code
 *
 * This code was written for a Teensy 2.0 microcontroller that receives a
 * byte via Bluetooth as input, catches the signal, and then moves a direction
 * depending on which bits are set. The commands are sent to motor controllers
 * which then transferred the signal to each of the motors for the wheels.
 */
#include <avr/io.h>
#include <util/delay.h>
#include "helper.h"
#include "uart.h"

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00
#define CPU_8MHz        0x01
#define CPU_4MHz        0x02
#define CPU_2MHz        0x03
#define CPU_1MHz        0x04
#define CPU_500kHz      0x05
#define CPU_250kHz      0x06
#define CPU_125kHz      0x07
#define CPU_62kHz       0x08

#if defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB1286__)
#define LED_ON		(PORTD |= (1<<6))
#define LED_OFF		(PORTD &= ~(1<<6))

// Teensy 1.0: LED is active low
#else
#define LED_ON	(PORTD &= ~(1<<6))
#define LED_OFF	(PORTD |= (1<<6))

#endif

#define LED_CONFIG	(DDRD |= (1<<6))
#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))
#define DIT 80		/* unit time for morse code*/


int main()
{	
	uint8_t received_data = -1;
	
	// Make sure the CPU prescaler is set properly for 16MHz
	CPU_PRESCALE(CPU_16MHz);	

	// Init the ADC and the UART
	init_uart();
	
	//Init and enable pins
	// right front
	(PINB |= (1<<3));
	// right back
	(PINB |= (1<<0));
	// left front
	(PINF |= (1<<0));
	// left back
	(PINF |= (1<<5));
	
	DDRB |= (1<<1);
	DDRB |= (1<<2);
	DDRB |= (1<<7);
	DDRD |= (1<<0);
	DDRF |= (1<<1);
	DDRF |= (1<<4);
	DDRF |= (1<<6);
	DDRF |= (1<<7);

	while (1) {
		// Receive new data from Android
		received_data = uart_getc();
		if (received_data >= 0) {
			switch(received_data) {
				// STAHP - correct
				case 0b00000000:
					LED_ON;
					(PORTB |= (1<<7));
					(PORTD |= (1<<0));
					(PORTB |= (1<<1));
					(PORTB |= (1<<2));
					(PORTF |= (1<<1));
					(PORTF |= (1<<4));
					(PORTF |= (1<<6));
					(PORTF |= (1<<7));
					break;
				// full speed ahead - correct
				case 0b00001010:
					LED_ON;
					// right front motor
					(PORTD &= ~(1<<0));
					(PORTB |= (1<<7));
					
					// right rear motor
					(PORTB |= (1<<2));
					(PORTB &= ~(1<<1));
					
					
					// left front motor
					(PORTF |= (1<<7));
					(PORTF &= ~(1<<6));
					
					// left rear motor
					(PORTF &= ~(1<<4));
					(PORTF |= (1<<1));
					break;
				// backward
				case 0b00000101:
					LED_ON;
					
					// right front motor
					(PORTD |= (1<<0));
					(PORTB &= ~(1<<7));
					
					// right rear motor
					(PORTB &= ~(1<<2));
					(PORTB |= (1<<1));
					
					
					// left front motor
					(PORTF &= ~(1<<1));
					(PORTF |= (1<<4));
					
					// left rear motor
					(PORTF &= ~(1<<7));
					(PORTF |= (1<<6));
					break;
				// right spin
				case 0b00001001:
					LED_ON;
					// right front motor
					(PORTD |= (1<<0));
					(PORTB &= ~(1<<7));
					
					// right rear motor
					(PORTB &= ~(1<<2));
					(PORTB |= (1<<1));
					
					
					// left front motor
					(PORTF |= (1<<1));
					(PORTF &= ~(1<<4));
					
					// left rear motor
					(PORTF |= (1<<7));
					(PORTF &= ~(1<<6));
					break;
				// left spin
				case 0b00000110:
					LED_ON;
					// right front motor
					(PORTD &= ~(1<<0));
					(PORTB |= (1<<7));
					
					// right rear motor
					(PORTB |= (1<<2));
					(PORTB &= ~(1<<1));
					
					
					// left front motor
					(PORTF &= ~(1<<1));
					(PORTF |= (1<<4));
					
					// left rear motor
					(PORTF &= ~(1<<7));
					(PORTF |= (1<<6));
					break;
				// right forward
				case 0b00001000:
					LED_ON;
					// right front motor
					(PORTD |= (1<<0));
					(PORTB |= (1<<7));
					
					// right rear motor
					(PORTB |= (1<<2));
					(PORTB |= (1<<1));
					// left front motor
					(PORTF |= (1<<1));
					(PORTF &= ~(1<<4));
					
					// left rear motor
					(PORTF |= (1<<7));
					(PORTF &= ~(1<<6));
					break;
				// right backward
				case 0b00000100:
					LED_ON;
					// right front
					(PORTD |= (1<<0));
					(PORTB &= ~(1<<7));
					// right rear motor
					(PORTB &= ~(1<<2));
					(PORTB |= (1<<1));
					// left front motor
					(PORTF |= (1<<1));
					(PORTF |= (1<<4));
					
					// left rear motor
					(PORTF |= (1<<7));
					(PORTF |= (1<<6));					
					break;
				// left forward
				case 0b00000010:
					LED_ON;
					// right front motor
					(PORTD &= ~(1<<0));
					(PORTB |= (1<<7));
					
					// right rear motor
					(PORTB |= (1<<2));
					(PORTB &= ~(1<<1));
					
					// left front motor
					(PORTF |= (1<<1));
					(PORTF |= (1<<4));
					
					// left rear motor
					(PORTF |= (1<<7));
					(PORTF |= (1<<6));
					break;
				// left backward
				case 0b00000001:
					LED_ON;
					// right front
					(PORTD |= (1<<0));
					(PORTB |= (1<<7));
					// right rear motor
					(PORTB |= (1<<2));
					(PORTB |= (1<<1));
					// left front motor
					(PORTF &= ~(1<<1));
					(PORTF |= (1<<4));
					
					// left rear motor
					(PORTF &= ~(1<<7));
					(PORTF |= (1<<6));		
					break;
				default:
					break;
			}
			_delay_ms(500);
			LED_OFF;
		}
	}
}

