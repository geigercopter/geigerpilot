/*
 *
 *
 */
#include <FastSerial.h>
#include "AP_GeigerCounter.h"

extern "C" {
  // AVR LibC Includes
  #include <avr/interrupt.h>
  #include <avr/io.h>
}

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WConstants.h"
#endif

AP_GeigerCounter::AP_GeigerCounter(InterruptDispatcher & dispatcher, uint8_t pins[GEIGER_COUNTER_PINS]):  _dispatcher(dispatcher)
{
    int i;
    for(i=0;i<GEIGER_COUNTER_PINS;i++)
    {
//        dispatcher.Register(pins[i], notify);
    }
    Serial.println("Instanciate AP_GeigerCounter");
    
    EIMSK &= ~(1 << INT0); // Disabling interrupts

    // prepare geiger counter pins for interruptions handling
    for(i=0;i<GEIGER_COUNTER_PINS;i++)
    {
        Serial.printf("Tube %d : %d\n", i, pins[i]);
        if (pins[i] == NOT_A_PIN) 
        {
            Serial.printf("Error pin %d is not a pin\n", pins[i]);
            return;
        }
        // activate internal pullup
        PORTB &= ~(1<<pins[i]);
        // set directions to INPUT
        DDRB &= ~(1<<pins[i]);
        // Enable interrupt for digital pins
        PCMSK0 |= (1 << pins[i]);
    }
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

uint16_t AP_GeigerCounter::read(int channel)
{
    return _tubes[channel].count;
}

double AP_GeigerCounter::measure(int channel)
{
    return 0.0;
}

void AP_GeigerCounter::beat()
{
/*
    shift_reg[reg_index] = cpb;     // put the count in the correct bin
    reg_index = (reg_index+1) % NX; // increment register index
*/
}

void AP_GeigerCounter::notify()
{
    int i=0;
    while(i<GEIGER_COUNTER_PINS)
    {
        if (PINB & _tubes[i].pin){
            _tubes[i].count++;
        }
        i++;
    }
}
