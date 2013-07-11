/* 
 * File:   InterruptDispatcher_PCINT0_vect.h
 * Author: crasher
 *
 * Created on 30 juin 2013, 18:55
 */
#include "InterruptDispatcher.h"

extern "C" {
  // AVR LibC Includes
  #include <inttypes.h>
  #include <avr/interrupt.h>
  #include <avr/io.h>
}

#ifndef INTERRUPTDISPATCHER_PCINT0_VECT_H
#define	INTERRUPTDISPATCHER_PCINT0_VECT_H

#ifndef IRQ_DISPATCHER_MAX_PINS
#define IRQ_DISPATCHER_MAX_PINS 2
#endif

class InterruptDispatcher_PCINT0_vect : public InterruptDispatcher
{

public:
    //static void Init();
    static InterruptDispatcher_PCINT0_vect & GetInstance();
    int8_t Register(uint8_t pin, void * func);
    int8_t UnRegister(uint8_t pin);

    InterruptDispatcher_PCINT0_vect() {};
    ~InterruptDispatcher_PCINT0_vect() {};
    
private:
    CLASS_IRQ(dispatcher, PCINT0_vect);
};
#endif	/* INTERRUPTDISPATCHER_PCINT0_VECT_H */
