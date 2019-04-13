/*
 * bhuan019_lab4_part4.c
 *
 * Created: 12-Apr-19 16:37:40
 * Author : Boi-Hien Huang
 */ 

#include <avr/io.h>
enum states {init, start, pass, wait, unlock, incorrect, wait2, pass2} state;

void lock() {
	switch (state) {
		case init:
			state = start;
			break;
		
		case start:
			if (PINA & 0x04) {
				state = wait;
			}
			break;
		
		case wait:
			if (!(PINA & 0x04)) {
				state = pass;
			}
			break;
		
		case pass:
			if (PINA & 0x02) {
				state = unlock;
			}
			else  if (!PINA){
				state = pass;
			}
			else {
				state = incorrect;
			}
			break;
		
		case unlock:
			if (PINA & 0x80) {
				state = start;
			}
			else if(PINA & 0x04){
				state = wait2;
			}
			break;
		
		case incorrect:
			if (!PINA) {
				state = start;
			}
			break;
		
		case wait2:
			if (!(PINA & 0x04)) {
				state = pass2;
			}
			break;
		
		case pass2:
			if (PINA & 0x02) {
				state = start;
			}
			else if (!PINA){
				state = pass2;
			}
			else {
				state = incorrect;
			}
			break;
		
	}
	switch (state) {
		case init:
			PORTC = state;
			break;
		
		case start:
			PORTC = state;
			PORTB = PORTB & 0xFE;
			break;
		
		case pass:
			PORTC = state;
			break;
		
		case wait:
			PORTC = state;
			break;
		
		case incorrect:
			PORTC = state;
			break;
		
		case unlock:
			PORTC = state;
			PORTB = PORTB | 0x01;
			break;
		
		case wait2:
			PORTC = state;
			break;
		
		case pass2:
			PORTC = state;
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0x00; PORTC = 0xFF;
	/* Replace with your application code */
	state = init;
	while (1)
	{
		lock();
	}
}

