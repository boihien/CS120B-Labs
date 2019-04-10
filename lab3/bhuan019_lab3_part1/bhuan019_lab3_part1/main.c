/*
 * bhuan019_lab3_part1.c
 *
 * Created: 09-Apr-19 15:53:31
 * Author : Boi-Hien Huang 
 * Partner : Tommy Ngo
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; //Configure port A's 8 pins as input
	DDRB = 0x00; PORTB = 0xFF; //Configure port B's 8 pin as input
	DDRC = 0xFF; PORTC = 0x00; //COnfigure port C's 8 pin as output
	//initialized output on PORTB to 0x00
	
	unsigned char P0 = 0x00;
	unsigned char P1 = 0x00;
	unsigned char numA = 0x00;
	unsigned char numB = 0x00;
	
    while (1) 
    {
		P0 = PINA & 0xFF;
		P1 = PINB & 0xFF;
		numA = (P0 & 0x01) + ((P0 & 0x02) >> 1) + ((P0 & 0x04) >> 2 ) + ((P0 & 0x08) >> 3) + ((P0 & 0x010) >> 4) + ((P0 & 0x20) >> 5) + ((P0 & 0x40) >> 6) + ((P0 & 0x80) >> 7);
		numB = (P1 & 0x01) + ((P1 & 0x02) >> 1) + ((P1 & 0x04) >> 2 ) + ((P1 & 0x08) >> 3) + ((P1 & 0x010) >> 4) + ((P1 & 0x20) >> 5) + ((P1 & 0x40) >> 6) + ((P1 & 0x80) >> 7);
		PORTC = numA + numB;
		
    }
}

