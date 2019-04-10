/*
 * bhuan019_lab3_part2.c
 *
 * Created: 09-Apr-19 19:22:11
 * Author : Boi-Hien Huang
 * Partner: Tommy Ngo
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; //Configure port A's 8 pins as input
	DDRB = 0xFF; PORTB = 0x00; //Configure port B's 8 pin as output
    /* Replace with your application code */
	
    while (1) 
    {
		
    }
}

