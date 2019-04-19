/*
 * bhuan019_lab5_part1.c
 *
 * Created: 18-Apr-19 19:38:54
 * Author : Boi-Hien Huang
 */ 

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	unsigned char levelA = 0x00;
	unsigned char levelC = 0x00;
	unsigned char lowFuel = 0x00;
	/* Replace with your application code */
	while (1)
	{
		levelA = ~PINA & 0x0F;
		if (levelA == 0x00) {
			levelC = 0x00;
			lowFuel = 0x40;
		}
		else if (levelA <= 0x02) {
			levelC = 0x20;
			lowFuel = 0x40;
		}
		else if (levelA <= 0x04) {
			levelC = 0x30;
			lowFuel = 0x40;
		}
		else if (levelA <= 0x06) {
			levelC = 0x38;
			lowFuel = 0x00;
		}
		else if (levelA <= 0x09) {
			levelC = 0x3C;
			lowFuel = 0x00;
		}
		else if (levelA <= 0x0C) {
			levelC = 0x3E;
			lowFuel = 0x00;
		}
		else if (levelA <= 0x0F) {
			levelC = 0x3F;
			lowFuel = 0x00;
		}
		
		PORTB = levelC | lowFuel;
		

	}
}