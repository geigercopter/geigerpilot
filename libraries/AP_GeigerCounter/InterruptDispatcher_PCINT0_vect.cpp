#include "InterruptDispatcher_PCINT0_vect.h"

// not implemented for AVR, MCU would never "exit", so atexit can be dummy 
// see 
extern "C" void atexit( void ) { } 

InterruptDispatcher_PCINT0_vect & InterruptDispatcher_PCINT0_vect::GetInstance()
{
    static InterruptDispatcher_PCINT0_vect _singleton; // singleton instance
    return _singleton;
}

void InterruptDispatcher_PCINT0_vect::dispatcher(void)
{

}

int8_t InterruptDispatcher_PCINT0_vect::Register(uint8_t pin, void * func)
{
    return 0;
}

int8_t InterruptDispatcher_PCINT0_vect::UnRegister(uint8_t pin)
{
    return 0;
}
