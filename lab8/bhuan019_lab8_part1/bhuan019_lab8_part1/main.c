/*
 * bhuan019_lab8_part1.c
 *
 * Created: 02-May-19 16:25:47
 * Author : Boi-Hien Huang
 */ 

#include <avr/io.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}
unsigned short my_short = 0x00;
int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	void ADC_init();
    /* Replace with your application code */
    while (1) 
    {
		my_short = ADC;
		PORTB = (char)my_short;
		PORTD = (char)(my_short >> 8);
    }
}

