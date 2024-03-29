/*
 * bhuan019_lab8_part3.c
 *
 * Created: 05-May-19 20:55:24
 * Author : Boi-Hien Huang
 */ 

#include <avr/io.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	// in Free Running Mode, a new conversion will trigger
	// whenever the previous conversion completes.
}


unsigned short MAX = 0x050;
unsigned short temp = 0x00;

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	ADC_init();
	
	while(1)
	{
		temp = ADC;
		if (temp >= MAX/2) {
			PORTB = 0x01;
		}
		else {
			PORTB = 0x00;
		}
	}
}

