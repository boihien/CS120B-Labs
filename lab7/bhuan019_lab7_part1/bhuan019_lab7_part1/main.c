/*
 * bhuan019_lab7_part1.c
 *
 * Created: 25-Apr-19 19:40:38
 * Author : Boi-Hien Huang
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
enum States {init, start, inc, dec, wait_inc, wait_dec, reset} state;
unsigned char counter = 0x00;

void tick(){
	switch(state){//transitions
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
		
		
	}
	switch (state){
		case start:
		LCD_Cursor(1);
		LCD_WriteData('0');
		break;
		case init:
		break;
		case inc:
		break;
		case dec:
		break;
		case wait_dec:
		if(counter <= 0){
			counter = 0;
		}
		else{
			counter--;
		}
		LCD_Cursor(1);
		LCD_WriteData(counter + '0');
		break;
		case wait_inc:
		if(counter >= 9){
			counter = 9;
		}
		else{
			counter++;
		}
		LCD_Cursor(1);
		LCD_WriteData(counter + '0');
		break;
		case reset:
		counter = 0;
		LCD_Cursor(1);
		LCD_WriteData(counter + '0');
		break;
	}
}
int main(void){
	state = start;
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	TimerSet(125);
	TimerOn();
	while(1){
		tick();
		while(!TimerFlag);
		TimerFlag = 0;
	}
}