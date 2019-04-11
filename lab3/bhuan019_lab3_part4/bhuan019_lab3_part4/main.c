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
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    
	unsigned char numB;
	unsigned char numA;
	unsigned char numC;
    while (1) 
    {
		numA = PINA;
		
		numB = (numA & 0xF0) >> 4;
		
		numC = (numA & 0x0F) << 4;
		
		PORTB = numB;
		PORTC = numC;
		
    }
}

