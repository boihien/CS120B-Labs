/*
 * bhuan019_lab9_part1.c
 *
 * Created: 05-May-19 12:24:57
 * Author : Boi-Hien Huang
 */ 
#include <avr/io.h>
// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(double frequency) {
	static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR0B &= 0x08; } //stops timer/counter
		else { TCCR0B |= 0x03; } // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR3A = 0xFFFF; }
		
		// prevents OCR0A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR0A = 0x0000; }
		
		// set OCR3A based on desired frequency
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT0 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR0A = (1 << COM0A0);
	// COM3A0: Toggle PB3 on compare match between counter and OCR0A
	TCCR0B = (1 << WGM02) | (1 << CS01) | (1 << CS30);
	// WGM02: When counter (TCNT0) matches OCR0A, reset counter
	// CS01 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR0A = 0x00;
	TCCR0B = 0x00;
}

enum States{init, start, on, off} state;
void tick(){
	switch(state){//transitions
		case init:
			state = start;
			break;
		case start:
			if(!(~PINA & 0x07)){
				state = off;
			}
			else{
				state = on;
			}
			break;
		case on:
			if(~PINA & 0x01){
				state = on;
			}
			else if(!(~PINA & 0x01)){
				state = off;
			}
			else if (~PINA & 0x02){
				state = on;
			}
			else if(!(~PINA & 0x02)){
				state = off;
			}
			else if (~PINA & 0x03){
				state = on;
			}
			else if(!(~PINA & 0x03)){
				state = off;
			}
			break;
		case off:
			state = start;
			break;
			
	}
	switch(state){//actions
		case init:
			break;
		case start:
			set_PWM(0);
			break;
		case on:
			PORTB = 0x02;
			if(~PINA & 0x01){
				set_PWM(261.63);
			}
			else if(~PINA & 0x02){
				set_PWM(293.66);
			}
			else if(~PINA & 0x03){
				set_PWM(329.63);
			}
			break;
		case off:
			PORTB = 0x01;
			set_PWM(0);
			break;
	}
}
int main(void){
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = init;
	PWM_on();
	while(1){
		tick();
	}
}