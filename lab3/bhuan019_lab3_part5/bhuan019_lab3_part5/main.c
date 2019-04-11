/*
 * bhuan019_lab3_part5.c
 *
 * Created: 10-Apr-19 17:01:41
 * Author : Boi-Hien Huang
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0x00; PORTB = 0x01;
    while (1) 
    {
    }
}

