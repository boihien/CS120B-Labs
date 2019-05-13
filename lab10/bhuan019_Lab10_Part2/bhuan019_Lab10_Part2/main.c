/*
 * bhuan019_Lab10_Part2.c
 *
 * Created: 12-May-19 22:04:05
 * Author : Boi-Hien Huang
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

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

enum TL_States{tl_start, tl_seq0, tl_seq1, tl_seq2} tl_state;
enum BL_States{start, light3, light0} bl_state;
unsigned char tl_temp = 0x00;
unsigned char bl_temp = 0x00;
void TL_tick(){
	switch(tl_state){//transitions
		case tl_start:
		tl_state = tl_seq0;
		break;
		case tl_seq0:
		tl_state = tl_seq1;
		break;
		case tl_seq1:
		tl_state = tl_seq2;
		break;
		case tl_seq2:
		tl_state = tl_seq0;
		break;
		default:
		tl_state = start;
		break;
	}
	switch(tl_state){//actions
		case tl_start:
		break;
		case tl_seq0:
		tl_temp = 0x01;
		break;
		case tl_seq1:
		tl_temp = 0x02;
		break;
		case tl_seq2:
		tl_temp = 0x04;
		break;
		
	}
}
void BL_tick(){
	switch(bl_state){//transitions
		case start:
		bl_state = light3;
		break;
		case light3:
		bl_state = light0;
		break;
		case light0:
		bl_state = light3;
		break;
		default:
		bl_state = start;
		break;
	}
	switch(bl_state){//actions
		case start:
		break;
		case light3:
		bl_temp = 0x08;
		break;
		case light0:
		bl_temp = 0x01;
		break;
	}
	
}
enum Concur{concur_start} concur;

void Concur_tick(){
	switch(concur){//transitions
		case concur_start:
		concur = concur_start;
		break;
	}
	switch(concur){//actions
		case concur_start:
		PORTB = tl_temp | bl_temp;
		break;
	}
}
int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(125);
	TimerOn();
	tl_state = tl_start;
	bl_state = start;
	/* Replace with your application code */
	while (1){
		TL_tick();
		BL_tick();
		Concur_tick();
		while(!TimerFlag){
			TimerFlag = 0;
		}
	}
}
