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
AP_GeigerCounter::AP_GeigerCounter(GeigerTube * tubes, uint8_t nbtubes)
    : _tubes(tubes), _nbtubes(nbtubes)
{

    //Serial.println("Instanciate AP_GeigerCounter");
}

uint16_t AP_GeigerCounter::read()
{
    uint16_t total = 0;

    for(int i = 0; i < _nbtubes; i++)
    {
        total += _tubes[i]->read();
    }
    return total;
}

double AP_GeigerCounter::measure()
{
    double measure = 0;

    for(int i = 0; i < _nbtubes; i++)
    {
        measure += _tubes[i]->measure();
    }
    return measure / _nbtubes;
}

void AP_GeigerCounter::beat()
{
    for(int i = 0; i < _nbtubes; i++)
    {
        _tubes[i]->beat();
    }
}


