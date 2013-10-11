/* 
 * File:   InterruptDispatcher.cpp
 * Author: crasher
 * 
 * Created on 28 juin 2013, 15:21
 */

#include "InterruptDispatcher.h"

InterruptDispatcher::InterruptDispatcher()
{
    _states = 0xFF;
}

void InterruptDispatcher::Register(IrqNotifiable * notifiable)
{
    int pin = notifiable->_pin;
    IrqNotifiable * tmpNotifiable;
Serial.printf("registering pin %d on PORTx : %d\n", notifiable->_pin, *_port);
    
    // set direction to INPUT
    *_ddr &= ~(1<<pin);
    // activate internal pullup
    *_port |= (1<<pin);
Serial.printf("PORTx changed to :%d\n", *_port);
    
    // Enable interrupt for digital pin
    *_pcmsk |= (1 << pin);

    // now adds irq to notifiables list
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

        // force as last notifiable
        notifiable->next = 0;
    }
}

void InterruptDispatcher::List()
{
    IrqNotifiable * notifiable = _notifiables;
    while(notifiable)
    {
Serial.printf("notifiable pin#%d\n", notifiable->_pin);
        notifiable = notifiable->next;
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

volatile void InterruptDispatcher::dispatch()
{
    count++;
    IrqNotifiable * notifiable = _notifiables;

    while(notifiable)
    {
        notifiable->notify();
        notifiable = notifiable->next;
    }
}

/**
 * 
 * @param states of pins are passed as parameter to prevent PINx state changes
 *          during treatment
 */
volatile void InterruptDispatcher::dispatch(uint8_t states)
{
    //uint8_t port = *_port;
    //count++;
if((_states == 0xFF) && (_states != states)) dbg1 = _states ^ states;    
//if(_states != states) dbg1 = _states ^ states;    
    uint8_t changes = _states ^ states;

    _states = states;

dbg2 = _states;
dbg3 = changes;
    /*
    IrqNotifiable * notifiable = _notifiables;

    while(notifiable)
    {
        uint8_t pin = notifiable->_pin;
        if(changes & (1 << pin))
        {
            if (notifiable->_mode & ((states | (1 << pin)) ? 2 : 1))
            {
//dbg1 = notifiable->_mode;
//dbg2 = pinchanges;
//dbg3 += (2 & ((pinchanges & (1 << pin)) ? 2 : 1));
                notifiable->notify();
            }
        }

        notifiable = notifiable->next;
    }
    */
}
