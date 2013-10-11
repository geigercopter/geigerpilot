#include "InterruptDispatcher_PCINT0_vect.h"

void InterruptDispatcher_PCINT0_vect::dispatcher(void)
{
    //InterruptDispatcher_PCINT0_vect::GetInstance().dispatch(PINB);
    InterruptDispatcher_PCINT0_vect::GetInstance().dispatch();
}

/*
ISR(PCINT0_vect)
{
    InterruptDispatcher_PCINT0_vect::GetInstance().dispatch();
}
*/