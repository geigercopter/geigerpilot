/* 
 * File:   GC_GeigerCounter.h
 * Author: crasher
 *
 * Created on 7 juin 2013, 15:18
 */

#ifndef AP_GeigerCounter_h
#define	AP_GeigerCounter_h

#include "GeigerCounter.h"

class AP_GeigerCounter : public GeigerCounter
{
public:
    AP_GeigerCounter(GeigerTube tubes[], uint8_t size);
    uint16_t read();
    double measure();
    void beat();
private:
    GeigerTube * _tubes;
    uint8_t _nbtubes;
};
#endif
