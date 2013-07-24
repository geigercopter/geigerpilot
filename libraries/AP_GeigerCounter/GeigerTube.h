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

#define GEIGER_TUBE_HISTORY_LEN 12
#define GEIGER_TUBE_CPM 175

#include "IrqNotifiable.h"

class GeigerTube : public IrqNotifiable
{
public:
    GeigerTube(uint8_t pin);
    uint16_t read();
    double measure();
    void beat();
    /*inline*/ void notify();
protected:
        struct Measure {
            uint32_t timestamp;
            uint8_t count;
        };
        uint8_t count;
        uint8_t lastpoint;
        Measure measures[GEIGER_TUBE_HISTORY_LEN];
        
};

#endif	/* GeigerTube_h */