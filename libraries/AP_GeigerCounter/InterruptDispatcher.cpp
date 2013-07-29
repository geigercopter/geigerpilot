/* 
 * File:   InterruptDispatcher.cpp
 * Author: crasher
 * 
 * Created on 28 juin 2013, 15:21
 */

#include "InterruptDispatcher.h"

void InterruptDispatcher::Register(IrqNotifiable * notifiable)
{
    int pin = notifiable->_pin;
    IrqNotifiable * tmpNotifiable;
    
    // activate internal pullup
    *_port &= ~(1<<pin);

    // set direction to INPUT
    *_ddr &= ~(1<<pin);

    // Enable interrupt for digital pin
    *_pcmsk |= (1 << pin);

    if((_notifiables == 0)||(notifiable == 0))
    {
       _notifiables = notifiable;
    }
    else
    {
        tmpNotifiable = _notifiables;
        // find the last or 
        do
        {
            //no way to register the same object twice !
            if((tmpNotifiable == notifiable))
            {
                return;
            }
            
            // if last element, add new notifiable on list
            if(tmpNotifiable->next == 0)
            {
                tmpNotifiable->next = notifiable;
                break;
            }
            tmpNotifiable = tmpNotifiable->next;
        }
        while(true);

        // force notifiable as last
        notifiable->next = 0;
    }
}

void InterruptDispatcher::UnRegister(IrqNotifiable * notifiable)
{   
    IrqNotifiable * current = _notifiables;
    IrqNotifiable * last = 0;
    
    if((_notifiables == 0)||(notifiable == 0))
    {
        return;
    }
    
    while(current)
    {
        // remove notifiable from list
        if(current == notifiable)
        {
            last->next = current->next;
            break;
        }
        last = current;
        current = current->next;
    }
}

void InterruptDispatcher::dispatch()
{
    IrqNotifiable * notifiable = this->_notifiables;   
    
    uint8_t mask = *_port;
    
    while(notifiable)
    {
        if(notifiable->_pin & mask)
        {
            notifiable->notify();
        }
        notifiable = notifiable->next;
    }
}
