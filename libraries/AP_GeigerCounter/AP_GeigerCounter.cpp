/*
 *
 *
 */
#include <FastSerial.h>
#include "AP_GeigerCounter.h"


extern "C" {
  // AVR LibC Includes
  #include <inttypes.h>
  #include <avr/interrupt.h>
  #include <avr/io.h>
}

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WConstants.h"
#endif

volatile uint16_t tube_count_1=0;
volatile uint16_t tube_count_2=0;

ISR(PCINT0_vect)
{
    tube_count_1++;
    tube_count_2++;

    Serial.println("Interrupt");    
    if (PINB & B00011000) {
       tube_count_1++;
       tube_count_2++;
       // click_count++; // We got 1 on Echo pin, remeber current counter value
    }
}

/**
 * 
 * @param tube1
 * @param tube2
 */
AP_GeigerCounter::AP_GeigerCounter(int16_t tube1, int16_t tube2) :
    _tube1(tube1),
    _tube2(tube2)
{
    Serial.printf("Tube 1 : %d\n", _tube1);
    Serial.printf("Tube 2 : %d\n", _tube2);
    
    Serial.println("Instanciate");
    if ((_tube1 == NOT_A_PIN) || (_tube2 == NOT_A_PIN)) 
    {
        Serial.println("Error : not a pin");
        return;
    }
    /*
    pinMode(_tube1, INPUT);
    pinMode(_tube2, INPUT);
    digitalWrite(_tube1, HIGH);   // Configure internal pull-up resistor
    digitalWrite(_tube2, HIGH);   // Configure internal pull-up resistor

    PORTB&=B11001111;
    DDRB &=B11001111;
     */
    
    // prepare geiger counter pins for interruptions handling
    
    // activate internal pullup active
    PORTB |= (1<<PB5) | (1<<PB6);

    // set directions to INPUT
    DDRB |= (1<<DDB5) | (1<<DDB6);

    EIMSK &= ~(1 << INT0); // Disabling interrupts

    // Enable interrupt for : B5 - D11 and B6 - D12
    PCMSK0 |= (1 << PCINT5) | (1 << PCINT6);
    
    PCICR |= (1 << PCIE0); // PCINT0 Interrupt enabled for PORTB
    
    /*
    ISCX1     ISCX0    used for interrupt x
     0          0      low
     0          1      change
     1          0      falling slope
     1          1      rising slope
    */
    // Define interrupt on rising edge 
    EICRA |= (1 << ISC00) | (1 << ISC01);
    
    // I dont really catch the difference between EICRA and MCUCR, but EICRA worked  
    //MCUCR = (1<<ISC01) | (1<<ISC00);
        
    EIFR |= (1 << INTF0); // Clear Interrupt flag
    EIMSK |= (1 << INT0);// Re-enable interrupts
}

void AP_GeigerCounter::init()
{
    Serial.println("Initialise");
}

uint16_t AP_GeigerCounter::read(int channel)
{
    	Serial.println("-rd-");
        switch(channel)
        {
            case 1:
                return tube_count_1;
                break;
            case 2:
                return tube_count_2;
                break;
            default:
                return tube_count_1 + tube_count_2;
        }
}
