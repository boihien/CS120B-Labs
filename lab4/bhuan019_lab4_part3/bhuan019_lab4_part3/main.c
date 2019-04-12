/*
 * bhuan019_lab4_part3.c
 *
 * Created: 11-Apr-19 22:54:36
 * Author : Boi-Hien Huang
 */ 

#include <avr/io.h>

enum States {init, start, hashtag, y, wait1, wait2, lock} state;

void tick() {
	switch (state) { // Transitions
		case init:
			state = start;
			break;
		case start:
			if((PINA & 0x04) == 0x04){
				state = wait1;
				break;
			}
			else if((PINA & 0x80) == 0x80){
				state = lock;
				break;
			}
			else{
				state = start;
				break;
			}
		case wait1:
			if((PINA & 0x04) == 0x00){
				state = hashtag;
				break;
			}
			else if((PINA & 0x80) == 0x80){
				state = lock;
				break;
			}
			else{
				state = start;
				break;
			}
			
		case hashtag:
			if((PINA & 0x02) == 0x02){
				state = wait2;
				break;
			}
			else if((PINA & 0x80) == 0x80){
				state = lock;
				break;
			}
			else{
				state = start;
				break;
			}
		case wait2:
			if((PINA & 0x02) == 0x00){
				state = y;
				break;
			}
			else if((PINA & 0x80) == 0x80){
				state = lock;
				break;
			}
			else{
				state = start;
				break;
			}
		case y:
			if((PINA & 0x80) == 0x80){
				state = lock;
				break;
			}
			
		default:
			break;
	} // Transitions

	switch(state) { // Actions
		case init: 
			PORTB = 0x00;
			PORTC = 0x00;
			break;
		case start:
			PORTC = 0x01;
			break;
		case hashtag:
			PORTC = 0x02;
			break;
		case wait1:
			PORTC = 0x03;
			break;
		case y:
			PORTB = 0x01;
			PORTC = 0x04;
			break;
		case wait2:
			PORTC = 0x05;
			break;
		case lock:
			PORTB = 0x00;
			PORTC = 0x06;
			break;
			
	} // Actions
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	state = init; // Initial state
	while(1) { tick(); }
}


