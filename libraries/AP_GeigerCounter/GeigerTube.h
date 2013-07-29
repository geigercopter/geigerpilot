/* 
 * File:   GeigerTube.h
 * Author: crasher
 *
 * Created on 7 juin 2013, 15:21
 */
/*
extern "C" {
  // AVR LibC Includes
  #include <inttypes.h>
}
*/
#ifndef GeigerTube_h
#define	GeigerTube_h

#define GEIGER_TUBE_HISTORY_LEN 15  // size of measure array
#define GEIGER_TUBE_MEASURE_DELAY 4 // delay between 2 measurements (in seconds)
#define GEIGER_TUBE_CPM 175

#include "IrqNotifiable.h"

class GeigerTube : public IrqNotifiable
{
public:
    GeigerTube(uint8_t pin);
    uint16_t read();
    double measure();
    void beat();
    
    void notify();
protected:
        struct Measure {
            uint32_t timestamp;
            uint8_t count;
        };
        
        Measure measures[GEIGER_TUBE_HISTORY_LEN];
        uint8_t count;
        uint8_t beatcount;
        uint8_t lastpoint;
};

#endif	/* GeigerTube_h */