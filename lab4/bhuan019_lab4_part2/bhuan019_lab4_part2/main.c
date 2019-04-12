/*
 * bhuan019_lab4_part2.c
 *
 * Created: 11-Apr-19 19:40:45
 * Author : Boi-Hien Huang
 */ 

#include <avr/io.h>


enum States {start, init, inc, dec, wait_inc, wait_dec, reset} state;

void tick() {
	switch (state) { // Transitions
		case init:
			state = start;
			break;
		
		case start:
			if((PINA & 0x01) == 0x01){
				state = wait_inc;
				break;
			}
			else{
				state = start;
				break;
			}
			if((PINA & 0x02) == 0x01){
				state = wait_dec;
				break;
			}
			else{
				state = start;
				break;
			}
		
		case wait_inc:
			if((PINA & 0x01) == 0x00){
				state = inc;
				break;
			}
			if((PINA & 0x02) == 0x01){
				state = reset;
				break;
			}
			
		case inc:
			state = start;
			break;
			
		case wait_dec:
			if((PINA & 0x02) == 0x00){
				state = dec;
				break;
			}
			if((PINA & 0x01) == 0x01){
				state = reset;
				break;
			}
			
		case dec:
			state = start;
			break;
			
		case reset:
			state = start;
			break;

	} // Transitions

	switch(state) { // Actions
		case init:
			PORTC = 0x07;
			break;
			
		case start:
			break;
		
		case inc:
			if(PORTC < 0x09){
				PORTC = PORTC + 0x01;
				break;
			}
		
		case dec:
			if(PORTC > 0x00){
				PORTC = PORTC - 0x01;
				break;
			}
			
		case wait_dec:
			break;
			
		case wait_inc:
			break;
			
		case reset:
			PORTC = 0x00;
			break;
			
		default:
			break;
		
		
	} // Actions
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x07;
	
	state = init;
	while(1) { tick(); }
}
