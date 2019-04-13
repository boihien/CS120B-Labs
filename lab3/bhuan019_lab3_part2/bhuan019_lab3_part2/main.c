/*
 * bhuan019_lab3_part2.c
 *
 * Created: 09-Apr-19 19:22:11
 * Author : Boi-Hien Huang
 * Partner: Tommy Ngo
 */ 

#include <avr/io.h>


enum States {start, init, inc, dec, wait_inc, wait_dec, reset} state;

void tick() {
	switch (state) { // Transitions
		case init:
		if (PINA & 0x01) {
			state = wait_inc;
		}
		else if (PINA & 0x02) {
			state = wait_dec;
		}
		break;
		
		case start:
		if (PINA & 0x01) {
			state = wait_inc;
		}
		else if (PINA & 0x02) {
			state = wait_dec;
		}
		break;
		
		case wait_inc:
		state = inc;
		break;
		
		case inc:
		if (!(PINA & 0x01)) {
			state = start;
		}
		else if (PINA & 0x02) {
			state = reset;
		}
		break;
		
		case wait_dec:
		state = dec;
		break;
		
		case dec:
		if (!(PINA & 0x02)) {
			state = start;
		}
		else if (PINA & 0x01) {
			state = reset;
		}
		break;
		
		case reset:
		if (!PINA) {
			state = start;
		}
		break;

	} // Transitions
	switch(state) { // Actions
		case init:
		PORTC = 0x07;
		break;
		
		case start:
		break;
		
		case inc:
		break;
		
		case dec:
		break;
		
		case wait_dec:
		if (PORTC > 0){
			PORTC = PORTC - 1;
		}
		break;
		
		case wait_inc:
		if (PORTC < 9){
			PORTC = PORTC + 1;
		}
		break;
		
		case reset:
		PORTC = 0x00;
		break;
		
		default:
		break;
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	state = init;
	while(1) { tick(); }
}

