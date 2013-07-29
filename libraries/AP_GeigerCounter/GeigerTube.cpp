/* 
 * File:   GeigerTube.cpp
 * Author: crasher
 * 
 * Created on 7 juin 2013, 15:21
 */

#include "GeigerTube.h"

GeigerTube::GeigerTube(uint8_t pin)
{
    Measure * measure;
    
    for(int i=0;i<GEIGER_TUBE_HISTORY_LEN;i++)
    {
        measure = &measures[i];
        measure->count = 0;
        measure->timestamp = 0;
    }
    _pin = pin;
    beatcount = 0;    
    lastpoint = 0;
}

uint16_t GeigerTube::read()
{
    return measures[lastpoint].count;
}

double GeigerTube::measure()
{
    int16_t total;
    total = 0;
    
    for(int i=0;i<GEIGER_TUBE_HISTORY_LEN;i++)
    {
        total += measures[i].count;
    }
    return total / GEIGER_TUBE_CPM;
}

// 1hz beat (for start)
void GeigerTube::beat()
{
    // only execute every GEIGER_TUBE_MEASURE_DELAY seconds
    if(!(beatcount++ % GEIGER_TUBE_MEASURE_DELAY))
    {
        return;
    }
    beatcount = 0;
    
    Measure * measure = &measures[lastpoint];
    measure->count = count;
    count = 0;
    lastpoint = lastpoint++ % GEIGER_TUBE_HISTORY_LEN;
}

void GeigerTube::notify()
{
    measures[lastpoint].count++;
}
