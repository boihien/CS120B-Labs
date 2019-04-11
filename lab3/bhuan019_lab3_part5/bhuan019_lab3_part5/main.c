/*
 * bhuan019_lab3_part5.c
 *
 * Created: 10-Apr-19 17:01:41
 * Author : Boi-Hien Huang
 */ 

#include <avr/io.h>


int main(void)
{
	DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0x06; PORTB = 0xF9;
	unsigned short weight = 0x000;
	unsigned char airbag = 0x00;
	/* Replace with your application code */
	while (1)
	{
		weight = ((PINB & 0x01) << 8) | (PIND & 0xFF);
		if (weight > 5 && weight < 70) {
			airbag = 0x02;
		}
		else if (weight >= 70) {
			airbag = 0x04;
		}
		else {
			airbag = 0x00;
		}
		
		PORTB = 0xF9 | airbag;

	}
}
