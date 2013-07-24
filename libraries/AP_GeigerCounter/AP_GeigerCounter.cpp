/*
 *
 *
 */

//#include <FastSerial.h>
#include "AP_GeigerCounter.h"

/*
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
*/
AP_GeigerCounter::AP_GeigerCounter(GeigerTube * tubes, int size)
{
    //Serial.println("Instanciate AP_GeigerCounter");
}

uint16_t AP_GeigerCounter::read(int channel)
{
    return _tubes->read();
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


