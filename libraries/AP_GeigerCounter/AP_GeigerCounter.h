/* 
 * File:   GC_GeigerCounter.h
 * Author: crasher
 *
 * Created on 7 juin 2013, 15:18
 */

#ifndef AP_GeigerCounter_h
#define	AP_GeigerCounter_h

#include "INotifiable.h"
#include "InterruptDispatcher.h"
#include "GeigerCounter.h"

//#include <AP_Common.h>

#define GEIGER_COUNTER_PINS 2
#define GEIGER_COUNTER_HISTORY_LEN 12
#define GEIGER_COUNTER_CPM 175

class AP_GeigerCounter: public GeigerCounter, public INotifiable
{
    
    public:
        AP_GeigerCounter(InterruptDispatcher & dispatcher, uint8_t pins[GEIGER_COUNTER_PINS]);

        uint16_t read(int channel = -1);
        double measure(int channel = -1);
        void beat();
        void notify();

    protected:
        struct MeasurePoint {
            uint32_t timestamp;
            uint8_t count;
        };
        struct Tube {
            uint16_t pin;
            uint8_t count;
            uint8_t lastpoint;
            MeasurePoint point[GEIGER_COUNTER_HISTORY_LEN];
        };
        volatile Tube _tubes[GEIGER_COUNTER_PINS];
        InterruptDispatcher & _dispatcher;
};
#endif
