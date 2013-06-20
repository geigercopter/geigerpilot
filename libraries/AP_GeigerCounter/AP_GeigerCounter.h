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
    AP_GeigerCounter(int16_t tube1, int16_t tube2);
    void init();
    int read();
  public:
private:      
    // geigertube click pins
    int16_t _tube1 = 0; 
    int16_t _tube2 = 0; // 
};
#endif
