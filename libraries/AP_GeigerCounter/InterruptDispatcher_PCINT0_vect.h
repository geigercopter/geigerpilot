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

class InterruptDispatcher_PCINT0_vect : public InterruptDispatcher
{
public:
    static InterruptDispatcher_PCINT0_vect & GetInstance(void){
        static InterruptDispatcher_PCINT0_vect _singleton; // singleton instance
        return _singleton;
    };

private:
    InterruptDispatcher_PCINT0_vect() {
        _port = &PORTB;
        _ddr = &DDRB;
        _pcmsk = &PCMSK0;

        //Enable IRQ on PCINT0
        PCICR |= (1 << PCIE0);
    };
    CLASS_IRQ(dispatcher, PCINT0_vect);
};
#endif	/* INTERRUPTDISPATCHER_PCINT0_VECT_H */
