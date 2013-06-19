#include "AP_GeigerCounter.h"

extern "C" {
  // AVR LibC Includes
  #include <inttypes.h>
  #include <avr/interrupt.h>
}

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WConstants.h"
#endif

ISR(PCINT0_vect)
{
    if (PINB & B00011000) { 
        click_count++; // We got 1 on Echo pin, remeber current counter value
    }
}

AP_GeigerCounter::AP_GeigerCounter(int16_t tube1, int16_t tube2) :
    _tube1(tube1),
    _tube2(tube2)
{
    	if ((_tube1 == NOT_A_PIN) || (_tube2 == NOT_A_PIN)) return;
        
        pinMode(_tube1, INPUT);
        pinMode(_tube2, INPUT);
        
	/*
        PORTB&=B11001111; // B4 -d10 - sonar Echo
	DDRB &=B11001111;
        */
        
}
void AP_GeigerCounter::init()
{

}

int AP_GeigerCounter::read()
{
    return 0;
}
