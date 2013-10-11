/* 
 * File:   INotifiable.h
 * Author: crasher
 *
 * Created on 30 juin 2013, 19:12
 */

#ifndef IRQNOTIFIABLE_H
#define	IRQNOTIFIABLE_H

extern "C" {
  // AVR LibC Includes
  #include <inttypes.h>
}

class IrqNotifiable
{
public:
    uint8_t _pin;
    enum Mode { RAISE = 1, FALL = 2, BOTH = 3 };
    IrqNotifiable::Mode _mode;
    IrqNotifiable * next; 
    virtual void notify();

};

#endif	/* IRQNOTIFIABLE_H */
