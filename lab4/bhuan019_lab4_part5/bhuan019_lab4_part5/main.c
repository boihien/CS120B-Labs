/*
 * bhuan019_lab4_part5.c
 *
 * Created: 12-Apr-19 17:14:39
 * Author : Boi-Hien Huang
 */ 

#include <avr/io.h>
enum states {init, start, pass, wait, unlock, incorrect} state;

void lock() {
    switch (state) {
        case init:
            state = start;
            break;
            
        case start:
            if (PINA & 0x04) {
                state = wait;
            }
            break;
            
        case wait:
            if (!(PINA & 0x04)) {
                state = pass;
            }
            break;
            
        case pass:
            if (PINA & 0x02) {
                state = unlock;
            }
            else  if (!PINA){
                state = pass;
            }
            else {
                state = incorrect;
            }
            break;
            
        case unlock:
            if (PINA & 0x80) {
                state = start;
            }
            break;
        
        case incorrect:
            if (!PINA) {
                state = start;
            }
            break;
    }
    switch (state) {
        case init:
            PORTC = state;
            break;
            
        case start:
            PORTC = state;
            PORTB = PORTB & 0xFE;
            break;
            
        case pass:
            PORTC = state;
            break;
        
        case wait:
            PORTC = state;
            break;
            
        case incorrect:
            PORTC = state;
            break;
        
        case unlock:
            PORTC = state;
            PORTB = PORTB | 0x01;
            break;
            
    }
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0x00; PORTC = 0xFF;
    /* Replace with your application code */
    state = init;
    while (1) 
    {
        lock();
    }
}

