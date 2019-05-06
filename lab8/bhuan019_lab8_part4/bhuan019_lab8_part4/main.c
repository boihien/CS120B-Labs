/*
 * bhuan019_lab8_part4.c
 *
 * Created: 05-May-19 22:12:14
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
unsigned short ADC_temp = 0x00;
unsigned short temp = MAX / 8;

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	ADC_init();
	
	while(1)
	{
		ADC_temp = ADC;
		if (ADC_temp <= temp)
		{
			PORTB = 0x01;
		}
		else if (ADC_temp <= temp * 2)
		{
			PORTB = 0x03;
		}
		else if (ADC_temp <= temp * 3)
		{
			PORTB = 0x07;
		}
		else if (ADC_temp <= temp * 4)
		{
			PORTB = 0x0F;
		}
		else if (ADC_temp <= temp * 5)
		{
			PORTB = 0x1F;
		}
		else if (ADC_temp <= temp * 6)
		{
			PORTB = 0x3F;
		}
		else if (ADC_temp <= temp * 7)
		{
			PORTB = 0x7F;
		}
		else
		{
			PORTB = 0xFF;
		}
	}
}