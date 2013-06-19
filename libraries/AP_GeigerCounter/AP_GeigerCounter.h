/* 
 * File:   GC_GeigerCounter.h
 * Author: crasher
 *
 * Created on 7 juin 2013, 15:18
 */

#ifndef GC_GEIGERCOUNTER_H
#define	GC_GEIGERCOUNTER_H

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
    int16_t _tube1; 
    int16_t _tube2; // 
};
#endif
