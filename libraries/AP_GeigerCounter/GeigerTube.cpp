/* 
 * File:   GeigerTube.cpp
 * Author: crasher
 * 
 * Created on 7 juin 2013, 15:21
 */

#include "GeigerTube.h"

GeigerTube::GeigerTube(uint8_t pin)
{
    _pin = pin; 
}

uint16_t GeigerTube::read()
{
    return measures[lastpoint].count;
}

double GeigerTube::measure()
{
    return 0.0;
}

void GeigerTube::beat()
{
/*
    shift_reg[reg_index] = cpb;     // put the count in the correct bin
    reg_index = (reg_index+1) % NX; // increment register index
*/
}

void GeigerTube::notify()
{
    measures[lastpoint].count++;
}

