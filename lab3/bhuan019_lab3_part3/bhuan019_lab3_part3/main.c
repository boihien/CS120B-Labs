/*
 * bhuan019_lab3_part3.c
 *
 * Created: 10-Apr-19 15:56:13
 * Author : Boi-Hien Huang
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; //Configure port A's 8 pins as input
	DDRC = 0xFF; PORTC = 0x00; //Configure port B's 8 pin as output
	
	unsigned char fuelLevel = 0x00;
	unsigned char sensor = 0x00;
	unsigned char key = 0x00;
	unsigned char seated = 0x00;
	unsigned char seatBelt = 0x00;
	
	while(1){
		fuelLevel = PINA;
		if((fuelLevel & 0x01) == 0x01){
			sensor = 0x60;
		}
		if((fuelLevel & 0x02) == 0x02){
			sensor = 0x60;
		}
		if((fuelLevel & 0x03) == 0x03){
			sensor = 0x70;
		}
		if((fuelLevel & 0x04) == 0x04){
			sensor = 0x70;
		}
		if((fuelLevel & 0x05) == 0x05){
			sensor = 0x38;
		}
		if((fuelLevel & 0x06) == 0x06){
			sensor = 0x38;
		}
		if((fuelLevel & 0x07) == 0x07){
			sensor = 0x3C;
		}
		if((fuelLevel & 0x08) == 0x08){
			sensor = 0x3C;
		}
		if((fuelLevel & 0x09) == 0x09){
			sensor = 0x3C;
		}
		if((fuelLevel & 0x0A) == 0x0A){
			sensor = 0x3E;
		}
		if((fuelLevel & 0x0B) == 0x0B){
			sensor = 0x3E;
		}
		if((fuelLevel & 0x0C) == 0x0C){
			sensor = 0x3E;
		}
		if((fuelLevel & 0x0D) == 0x0D){
			sensor = 0x3F;
		}
		if((fuelLevel & 0x0E) == 0x0E){
			sensor = 0x3F;
		}
		if((fuelLevel & 0x0F) == 0x0F){
			sensor = 0x3F;
		}
		key = PINA & 0x10;
		seated = PINA & 0x20;
		seatBelt = PINA & 0x40;
		if((key == 0x10) && (seated == 0x20) && (seatBelt == 0x00)){
			PORTC = sensor | 0x80;
		}
		else{
			PORTC = sensor;
		}
	}
}


