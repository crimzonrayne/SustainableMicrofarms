/*
 * ATMega168_Growbox.c
 *
 * Created: 2/2/2014 11:32:35 PM
 *  Author: Crimzon
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

double sprayTime = 0;
double cycleTime = 60;

/*void SetupADC()
{
	ADMUX |= (1 << ADLAR);
	
	ADCSRA |= (1 << ADPS1);
	ADCSRA |= (1 << ADPS0);
	
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADSC);

}

int ReadTimer()
{
	return (cycleTime * ((ADCH)/256));
}
*/


uint16_t ReadADC(uint8_t __channel)
{
	ADMUX = (ADMUX & 0xf0) | __channel; // Channel selection
	ADCSRA |= _BV(ADSC);                // Start conversion
	while(!bit_is_set(ADCSRA,ADIF));    // Loop until conversion is complete
	ADCSRA |= _BV(ADIF);                // Clear ADIF by writing a 1 (this sets the value to 0)
	uint16_t temp = (ADC &= (0x0000001111111111));
	return(temp);
}

void adc_init()
{
	ADCSRA = _BV(ADEN) | _BV(ADPS1) | _BV(ADPS0); //Enable ADC and set 8 prescale
}


void delay_ms(double milliseconds)
{
	 do
	 {
		 _delay_ms(1);
		 milliseconds--;
	 } while(milliseconds);
}

int main(void)
{
	DDRB |= (1 << DDB0);
	
	adc_init();
	
	(PORTB |= (1 << PINB0));
    _delay_ms(1000);
    (PORTB &= ~(1 << PINB0));
    _delay_ms(2000);

	
    while(1)
    {
		sprayTime = cycleTime * ReadADC(0) * 2;
		(PORTB |= (1 << PINB0));
		delay_ms(sprayTime);
		(PORTB &= ~(1 << PINB0));
		delay_ms((cycleTime * 1000) - sprayTime);

		/*if (ReadADC(0) > 512)
		{
			(PORTB |= (1 << PINB0));
		} 
		else
		{
			(PORTB &= ~(1 << PINB0));
		}
		*/
    }
}