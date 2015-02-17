// helper.c
// Kyle Dillon 11/7/13
// Simple multi-use-case function library.
#include "helper.h"

void set_bit(uint8_t bit, uint8_t *byte) {
	*byte |= 1<<bit;
}

void clear_bit(uint8_t bit, uint8_t *byte) {
	*byte &= ~(1<<bit);
}

void toggle_bit(uint8_t bit, uint8_t *byte) {
	*byte ^= 1<<bit;
}

uint8_t check_bit(uint8_t bit, uint8_t byte) {
	if(byte & (1<<bit)) return 1;
	else return 0;
}

uint16_t concatenate_ints(uint16_t x, uint16_t y) {
	uint16_t pow = 10;
	while(y >= pow)
		pow *= 10;
    	return x * pow + y;        
}

void reverse_string(char s[]) {
	uint8_t l = strlen(s);
	uint8_t i, j, k;
	k = l/2;
	// Work with half the length
	for (i=0; i<k; i++) {
		// swap the two bytes
		j=s[i];
		s[i]=s[l-1-i];
		s[l-1-i]=j;
	}
}
