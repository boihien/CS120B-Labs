/*
 * bhuan019_lab2_part1.c
 *
 * Created: 03-Apr-19 18:31:00
 * Author : Boi-Hien Huang
 */ 

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; //Configure port A's 8 pins as input
	DDRB = 0xFF; PORTB = 0x00; //Configure port B's 8 pin as output
	//initialized output on PORTB to 0x00
	
	unsigned char input1 = 0x00;
	unsigned char input2 = 0x00;

	
	while(1){
		//read input
		input1 = PINA & 0x01;//PA0
		input2 = PINA & 0x02;//PA1
		if(input1 == 0x01 && input2 == 0x00){
			PORTB = 0x01;//writing to registers
		}
		else{
			PORTB = 0x00;
		}
	}
	return 0;
}




