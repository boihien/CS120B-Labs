#include <avr/io.h>
enum States { start, PB0_OFF, Wait1, PB0_ON, Wait2 } state;

void tick() {
	switch (state) { // Transitions
		case start:
		state = PB0_ON;
		break;
		
		case PB0_OFF:
		if((PINA & 0x01) == 0x00){
			state = PB0_OFF;
			break;
		}
		else{
			state = Wait2;
			break;
		}
		case Wait1:
		if((PINA & 0x01) == 0x01){
			state = Wait1;
			break;
		}
		else{
			state = PB0_OFF;
			break;
		}
		case Wait2:
		if((PINA & 0x01) == 0x01){
			state = Wait2;
			break;
		}
		else{
			state = PB0_ON;
			break;
		}
		
		case PB0_ON:
		if((PINA & 0x01) == 0x00){
			state = PB0_ON;
			break;
		}
		else{
			state = Wait1;
			break;
		}
		
	} // Transitions

	switch(state) { // Actions
		case start:
		PORTB = 0x01;
		break;
		
		case PB0_OFF:
		PORTB = 0x02;
		break;
		
		case Wait1:
		PORTB = 0x02;
		break;
		
		case PB0_ON:
		PORTB = 0x01;
		break;
		
		case Wait2:
		PORTB = 0x01;
		break;
		
		default:
		break;
	} // Actions
}

int main() { // Initialize all outputs
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = start; // Initial state
	while(1) { tick(); }
}