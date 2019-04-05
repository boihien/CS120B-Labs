/*
 * bhuan019_lab2_part2.c
 *
 * Created: 04-Apr-19 17:12:18
 * Author : Boi-Hien Huang
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;//set Port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00;//set Port C's 8 pins as outputs
	//PORTC initialized to 0
	unsigned char space0 = 0x00;
	unsigned char space1 = 0x00;
	unsigned char space2 = 0x00;
	unsigned char space3 = 0x00;
	unsigned char cntavail = 0x00;
    while (1) 
    {
		//read in input
		space0 = PINA & 0x01;
		space1 = PINA & 0x02;
		space2 = PINA & 0x04;
		space3 = PINA & 0x08;
		
		if(
    }
}

