// uart.c
// Kyle Dillon 4/30/14
// Init, read, write functions for using UART1 on Teensy 2.0

#include <avr/io.h>
#include <stdlib.h>

#define USART_BAUDRATE 9600 // Specify desired baudrate here
#define BAUDVALUE  ((F_CPU/(USART_BAUDRATE * 16UL)) - 1 ) 

//	init_uart
// Initialize UART1 for synchronous (non-interrupt) use to the baudrate specified by BAUDVALUE.
void init_uart(){
	DDRD |= (1<<PD3); // Set TX to an output
	UCSR1B |= (1<<RXEN1) | (1<<TXEN1); // RX and TX enable, receive interrupt disabled, 8-bit characters
	UCSR1C |= (1<<UCSZ11) | (1<<UCSZ10); // No parity, one stop bit, 8-bit characters
	UBRR1H = (BAUDVALUE >> 8); // Load upper byte of the baud rate into baud rate register
	UBRR1L = BAUDVALUE; // Load lower byte of the baud rate into baud rate register
}
//	uart_putc
// Wait for previous transmissions to complete, then send the byte data
void uart_putc(char data) {
	while (!(UCSR1A&(1<<UDRE1)));
	UDR1 = data;
}

//	uart_puts
// Send each byte in a string individually
// Make sure that string is null terminated
void uart_puts(char *str) {
    int i = 0;
    while(str[i] != '\0') {
        uart_putc(str[i]);
        i++;
    }
}

//	uart_getc
// Non-blocking read of UART1.
// Returns 0 if no data available.
uint8_t uart_getc(void) {
	if(UCSR1A & (1<<RXC1)) return(UDR1); // If data is available, return it
	else return(-1);
}