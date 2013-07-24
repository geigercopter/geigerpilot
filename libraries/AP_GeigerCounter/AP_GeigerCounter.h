/* 
 * File:   GC_GeigerCounter.h
 * Author: crasher
 *
 * Created on 7 juin 2013, 15:18
 */

#ifndef AP_GeigerCounter_h
#define	AP_GeigerCounter_h

#include "GeigerCounter.h"

//#include <AP_Common.h>

class AP_GeigerCounter: public GeigerCounter
{
    public:
        AP_GeigerCounter(GeigerTube * tubes, int size);
        uint16_t read(int channel = -1);
        double measure(int channel = -1);
        void beat();
};
#endif
