/* 
 * File:   InterruptDispatcher.cpp
 * Author: crasher
 * 
 * Created on 28 juin 2013, 15:21
 */

#include "InterruptDispatcher.h"

int8_t InterruptDispatcher::Register(IrqNotifiable * notifiable)
{
    int pin = notifiable->_pin;
    IrqNotifiable * tmpNotifiable;
    
    // activate internal pullup
    *_port &= ~(1<<pin);

    // set direction to INPUT
    *_ddr &= ~(1<<pin);

    // Enable interrupt for digital pin
    *_pcmsk |= (1 << pin);

    if(_notifiables == 0)
    {
       _notifiables = notifiable;
    }
    else
    {
        tmpNotifiable = _notifiables;
        
        // find the last or 
        do
        {
            //no way to register twice
            if((tmpNotifiable == notifiable))
            {
                break;
            }
        }
        while(tmpNotifiable->next)
        if(tmpNotifiable->next)
        {
    }
    
    lastNotifiable-> = 
    /*
    // prepare geiger counter pins for interruptions handling
        
    // activate internal pullup
    PORTB &= ~(1<<pin);

    // set directions to INPUT
    DDRB &= ~(1<<pin);

    // Enable interrupt for digital pins
    PCMSK0 |= (1 << pin);
    
    // PCINT0 Interrupt enabled for PORTB
    PCICR |= (1 << PCIE0); 
    
    /*
    ISCX1     ISCX0    used for interrupt x
     0          0      low
     0          1      change
     1          0      falling slope
     1          1      rising slope
    */
    /*
    // Define interrupt on rising edge 
    EICRA |= (1 << ISC00) | (1 << ISC01);
    // I dont really catch the difference between EICRA and MCUCR, but EICRA worked  
    //MCUCR = (1<<ISC01) | (1<<ISC00);
        
    EIFR |= (1 << INTF0); // Clear Interrupt flag
    EIMSK |= (1 << INT0);// Re-enable interrupts
    
    _notifiables[pin] = notifiable;
    return _pins |= pin;
     */
}

int8_t InterruptDispatcher::UnRegister(IrqNotifiable * notifiable)
{
    _notifiables = 0;
    return _pins;// &= ~pin;
}

void InterruptDispatcher::dispatch(unsigned char mask)
{
    IrqNotifiable * notifiable = this->_notifiables;
    int8_t pin = 0;

    if(!(mask & _pins)) return;
    
    while(notifiable)
    {
        if(notifiable->_pin & mask)
        {
            notifiable->notify();
        }
        pin++;
        
        notifiable = notifiable->next;
    }
}
