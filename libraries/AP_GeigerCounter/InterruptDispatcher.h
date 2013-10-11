/* 
 * File:   InterruptDispatcher.h
 * Author: crasher
 *
 * Created on 28 juin 2013, 15:21
 */

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

// not implemented for AVR, MCU would never "exit", so atexit can be dummy 
// see http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=535303#535303
// and http://www.embeddedrelated.com/usenet/embedded/show/88449-1.php
// perhaps this declaration should find a better declaration on a more general (common) header
// but I decided to left it in this place as it resolves a linking error
//extern "C" void atexit( void ) { } 

#include <FastSerial.h> // uncomment for debug

#include "IrqNotifiable.h"

class InterruptDispatcher
{
public:
    void Register(IrqNotifiable * notifiable);
    void UnRegister(IrqNotifiable * notifiable); 
    void List();
    volatile void dispatch();
    volatile void dispatch(uint8_t states);
    volatile int count;
    volatile int dbg1; 
    volatile int dbg2;
    volatile int dbg3;
protected:
    IrqNotifiable * _notifiables; // list of notifiables

    volatile uint8_t * _port;
    volatile uint8_t * _ddr;
    volatile uint8_t * _pcmsk;
    // used to keep last PORT values
    volatile uint8_t _states;
    InterruptDispatcher();
};

#include "InterruptDispatcher_PCINT0_vect.h"

#endif	/* InterruptDispatcher_h */
