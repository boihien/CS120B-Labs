/*
 * bhuan019_lab9_part3.c
 *
 * Created: 05-May-19 20:45:47
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
		else { OCR0A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT0 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR0A = (1 << COM0A0 | 1 << WGM00);
	// COM3A0: Toggle PB3 on compare match between counter and OCR0A
	TCCR0B = (1 << WGM02) | (1 << CS01) | (1 << CS00);
	// WGM02: When counter (TCNT0) matches OCR0A, reset counter
	// CS01 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR0A = 0x00;
	TCCR0B = 0x00;
}
enum States{init, off, on, buttonON, increase, wait1, decrease, wait2}state;

void tick(){
	const double scale[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
	unsigned char counter = 0;
	unsigned char temp = ~PINA & 0x07;
	switch(state){//transitions
		case init:
		if(temp == 0x01){
			state = on;
		}
		else{
			state = init;
		}
		break;
		case off:
		if(!(temp == 0x01)){
			state = init;
		}
		else{
			state = off;
		}
		break;
		case on:
		if(temp == 0x01){
			state = on;
		}
		else{
			state = buttonON;
		}
		break;
		case buttonON:
		if(temp == 0x02){
			if(counter < 7){
				counter++;
			}
			state = increase;
		}
		else if(temp == 0x04){
			if(counter > 0){
				counter--;
			}
			state = decrease;
		}
		else if(temp == 0x01){
			state = off;
		}
		else{
			state = buttonON;
		}
		break;
		case increase:
		state = wait1;
		break;
		case wait1:
		if(temp == 0x02){
			state = wait1;
		}
		else{
			state = buttonON;
		}
		break;
		case decrease:
		state = wait2;
		break;
		case wait2:
		if(temp == 0x04){
			state = wait2;
		}
		else{
			state = buttonON;
		}
		break;
	}
	switch(state){//actions
		case init:
		PWM_off();
		break;
		case off:
		PORTB = 0x01;
		break;
		case on:
		PORTB = 0x02;
		PWM_on();
		break;
		case buttonON:
		PORTB = 0x03;
		break;
		case increase:
		PORTB = 0x04;
		set_PWM(scale[counter]);
		break;
		case wait1:
		PORTB = 0x05;
		break;
		case decrease:
		PORTB = 0x06;
		set_PWM(scale[counter]);
		break;
		case wait2:
		PORTB = 0x07;
		break;
	}
}

int main(void){
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	PWM_on();
	state = init;
	while(1){
		tick();
	}
}

