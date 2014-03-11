/*
 * Growbox_Timer___Interrupt.cpp
 *
 * Created: 3/6/2014 11:15:42 AM
 *  Author: Crimzon
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL

int spraySetting = 0;
int sprayTime = 0;

ISR(INT0_vect)
{
	_delay_ms(500);
	
	if (spraySetting == 5){
		spraySetting = 0;
	} else {
		spraySetting++;
	}
	
}

void delay_ms(double milliseconds)
{
	do
	{
		_delay_ms(1);
		milliseconds--;
	} while(milliseconds);
}

void sprayCycle()
{
	(PORTB |= (1 << PINB6));
	delay_ms(sprayTime);
	(PORTB &= ~(1 << PINB6));
	delay_ms(60000 - sprayTime);	
}

int main(void)
{
	MCUCR = (1<<ISC01) | (1<<ISC00);
	GIMSK |= (1<<PCINT0);
	
	DDRD = 1<<PD2;
	PORTD = 1<<PD2;
	
    while(1)
    {
        sprayCycle();
		switch(spraySetting){
			case 0:
				PORTB = 0b00000001;
				sprayTime = 0;
				break;
			case 1:
				PORTB = 0b00000010;
				sprayTime = 3000;
				break;
			case 2:
				PORTB = 0b00000100;
				sprayTime = 6000;
				break;
			case 3:
				PORTB = 0b00001000;
				sprayTime = 9000;
				break;
			case 4:
				PORTB = 0b00010000;
				sprayTime = 12000;
				break;
			case 5:
				PORTB = 0b00100000;
				sprayTime = 15000;
				break;
			default:
				spraySetting = 0;	
				break;
		}
}