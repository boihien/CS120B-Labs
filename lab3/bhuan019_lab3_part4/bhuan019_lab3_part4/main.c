/*
 * bhuan019_lab3_part4.c
 *
 * Created: 10-Apr-19 16:38:17
 * Author : Boi-Hien Huang
 * Partner : Tommy Ngo
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x0F; PORTB = 0xF0;
	DDRC = 0xF0; PORTC = 0x0F;
	unsigned char PA = 0x00;
	unsigned char topPA = 0x00;
	unsigned char botPA = 0x00;
	/* Replace with your application code */
	while (1)
	{
		PA = PINA & 0xFF;

		topPA = (PA & 0xF0) >> 4;
		botPA = (PA & 0x0F) << 4;

		PORTB = topPA;
		PORTC = botPA;
	}
}

