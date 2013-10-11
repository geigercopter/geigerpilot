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
    
    _pin = pin;
    _mode = FALL;
    count = 0;
    beatcount = 0;    

    // first point index will be 0
    lastpoint = GEIGER_TUBE_HISTORY_LEN - 1;

    for(int i=0;i<GEIGER_TUBE_HISTORY_LEN;i++)
    {
        measure = &measures[i];
        measure->count = 0;
        measure->timestamp = 0;
    }
}

uint16_t GeigerTube::read()
{
    return measures[lastpoint].count;
}

float GeigerTube::buildReport()
{
    report.total = 0;
    
    // beginning with oldest measure
    uint8_t point = (lastpoint + 1) % GEIGER_TUBE_HISTORY_LEN;

    uint8_t countdown = GEIGER_TUBE_HISTORY_LEN - 1;
    
    uint8_t bitshift = GEIGER_TUBE_AVERAGES_BITSHIFT - 1;
    
    report.averages[bitshift] = 0;
    
    while(point != lastpoint)
    {
        if(!((1 << bitshift) & countdown)) 
        {
            report.averages[--bitshift] = 0;
        }
        
        uint8_t measure_count = measures[point].count;
        
        report.total += measure_count;
        
        report.averages[bitshift] += measure_count;
        
        point = ++point % GEIGER_TUBE_HISTORY_LEN;
        
        countdown--;
    }
    
    report.uSv = (float)report.total / GEIGER_TUBE_CPM;
    return report.uSv;
}

// 1hz beat (for start)
void GeigerTube::beat()
{
    // only execute every GEIGER_TUBE_MEASURE_DELAY seconds
    // Simple EQUAL (=) sign is not an error but an assignation ! so leave it alone !
    if(beatcount = ++beatcount % GEIGER_TUBE_MEASURE_DELAY)
    {
        return;
    }

    Measure * measure = &measures[lastpoint = ++lastpoint % GEIGER_TUBE_HISTORY_LEN];
    
    // never insert code between theses 2 instructions in the following line
    measure->count = count; count = 0;
    measure->timestamp = millis();
    
    buildReport();
    
}

void GeigerTube::notify()
{
    count++;
}
