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

#include "IrqNotifiable.h"

class InterruptDispatcher
{
public:
    void Register(IrqNotifiable * notifiable);
    void UnRegister(IrqNotifiable * notifiable); 

protected:
    void dispatch();
    //uint8_t _pins;
    
    IrqNotifiable * _notifiables; // list of notifiables

    //uint8_t _mask;

    static volatile uint8_t * _test;
    
    volatile uint8_t * _port;
    volatile uint8_t * _ddr;
    volatile uint8_t * _pcmsk;
};

#include "InterruptDispatcher_PCINT0_vect.h"

#endif	/* InterruptDispatcher_h */
