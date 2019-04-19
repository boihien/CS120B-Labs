/*
 * bhuan019_lab5_part2.c
 *
 * Created: 18-Apr-19 21:29:46
 * Author : Boi-Hien Huang
 */ 

#include <avr/io.h>


enum States {start, init, inc, dec, wait_inc, wait_dec, reset} state;

void tick() {
	switch (state) { // Transitions
		case init:
		if (~PINA & 0x01) {
			state = wait_inc;
		}
		else if (~PINA & 0x02) {
			state = wait_dec;
		}
		break;
		
		case start:
		if (~PINA & 0x01) {
			state = wait_inc;
		}
		else if (~PINA & 0x02) {
			state = wait_dec;
		}
		break;
		
		case wait_inc:
		state = inc;
		break;
		
		case inc:
		if (!(~PINA & 0x01)) {
			state = start;
		}
		else if (~PINA & 0x02) {
			state = reset;
		}
		break;
		
		case wait_dec:
		state = dec;
		break;
		
		case dec:
		if (!(~PINA & 0x02)) {
			state = start;
		}
		else if (~PINA & 0x01) {
			state = reset;
		}
		break;
		
		case reset:
		state = start;
		break;
		
		default:
		break;

	} // Transitions
	switch(state) { // Actions
		case init:
		PORTB = 0x07;
		break;
		
		case start:
		break;
		
		case inc:
		break;
		
		case dec:
		break;
		
		case wait_dec:
		if (PORTB > 0){
			PORTB = PORTB - 1;
		}
		break;
		
		case wait_inc:
		if (PORTB < 9){
			PORTB = PORTB + 1;
		}
		break;
		
		case reset:
		PORTB = 0x00;
		break;
		
		default:
		break;
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	state = init;
	while(1) { tick(); }
}