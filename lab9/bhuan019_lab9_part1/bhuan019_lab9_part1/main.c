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
		if (!frequency) { TCCR3B &= 0x08; } //stops timer/counter
		else { TCCR3B |= 0x03; } // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR3A = 0xFFFF; }
		
		// prevents OCR3A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR3A = 0x0000; }
		
		// set OCR3A based on desired frequency
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT3 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	// COM3A0: Toggle PB6 on compare match between counter and OCR3A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM32: When counter (TCNT3) matches OCR3A, reset counter
	// CS31 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}



enum States{off, button1, button2, button3} state;
void tick(){
	unsigned char temp = ~PINA & 0x07;
	switch(state){//transitions
		case off:
		if(temp == 0x01){
			state = button1;
		}
		else if(temp == 0x02){
			state = button2;
		}
		else if(temp == 0x04){
			state = button3;
		}
		else{
			state = off;
		}
		break;
		case button1:
		if(temp == 0x01){
			state = button1;
		}
		else{
			state = off;
		}
		break;
		case button2:
		if(temp == 0x02){
			state = button2;
		}
		else{
			state = off;
		}
		break;
		case button3:
		if(temp == 0x04){
			state = button3;
		}
		else{
			state = off;
		}
		break;
	}
	switch(state){//actions
		case off:
		PORTB = 0x01;
		set_PWM(0);
		break;
		case button1:
		PORTB = 0x02;
		set_PWM(261.63);
		break;
		case button2:
		PORTB = 0x03;
		set_PWM(293.66);
		break;
		case button3:
		PORTB = 0x04;
		set_PWM(329.63);
		break;
	}
}
int main(void){
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = off;
	PWM_on();
	while(1){
		tick();
	}
}