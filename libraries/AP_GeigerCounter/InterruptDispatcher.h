/* 
 * File:   InterruptDispatcher.h
 * Author: crasher
 *
 * Created on 28 juin 2013, 15:21
 */

#include <AP_Common.h>

#ifndef InterruptDispatcher_h
#define	InterruptDispatcher_h

#ifndef STRINGIFY
#define STRINGIFY(name) #name
#endif

#ifndef CLASS_IRQ
#define CLASS_IRQ(name, vector) \
    static void name(void) asm(STRINGIFY(vector)) \
    __attribute__ ((signal, __INTR_ATTRS))
#endif

#ifndef IRQ_DISPATCHER_MAX_PINS
#define IRQ_DISPATCHER_MAX_PINS 2
#endif

class InterruptDispatcher
{
public:
    virtual int8_t Register(uint8_t pin, void * func) = 0;
    virtual int8_t UnRegister(uint8_t pin) = 0;
    InterruptDispatcher() {};
    ~InterruptDispatcher() {};
};

#include "InterruptDispatcher_PCINT0_vect.h"
#endif	/* InterruptDispatcher_h */
