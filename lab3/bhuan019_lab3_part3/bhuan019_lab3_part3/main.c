/*
 * bhuan019_lab3_part3.c
 *
 * Created: 10-Apr-19 15:56:13
 * Author : Boi-Hien Huang
 * Partner: Tommy Ngo
 */ 

#include <avr/io.h>


unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char levelA = 0x00;
	unsigned char levelC = 0x00;
	unsigned char lowFuel = 0x00;
	unsigned char seat = 0x00;
	unsigned char fasten = 0x00;
	/* Replace with your application code */
	while (1)
	{
		levelA = PINA & 0x0F;
		seat = PINA & 0x70;
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

		if (GetBit(seat, 4) && GetBit(seat, 5) && !GetBit(seat,6)) {
			fasten = SetBit(fasten, 7, 1);
		}
		else {
			fasten = SetBit(fasten, 7, 0);
		}

		PORTC = levelC | lowFuel | fasten;

	}
}


