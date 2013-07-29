/*
 *  AP_Geigercounter_test
 */
//#define USE_AP_VAR

#include <FastSerial.h>
#include <AP_Common.h>
#include <AP_Math.h>
/*
#include <AP_GeigerCounter/GeigerTube.h>
#include <AP_GeigerCounter/InterruptDispatcher.h>
*/
#include "AP_GeigerCounter.h"
#include "InterruptDispatcher.h"

extern "C" void atexit( void ) { } 

//GeigerTube tube1(PINB5);
//GeigerTube tube2(PINB6);
#define GEIGER_NUM_TUBES 2

GeigerTube tubes[GEIGER_NUM_TUBES] = {(PCINT5), (PCINT6)};

InterruptDispatcher_PCINT0_vect & dispatcher = InterruptDispatcher_PCINT0_vect::GetInstance();

AP_GeigerCounter geigerCounter(tubes, GEIGER_NUM_TUBES);

void setup()
{
    for(int i=0; i< GEIGER_NUM_TUBES; i++)
    {
        dispatcher.Register(&tubes[0]);
    }
    //Serial.begin(115200);
    //Serial.println("GeigerCounter Test");
//    geigerCounter.init();
}

void loop()
{
    delay(1000);
    geigerCounter.beat();
            
    //Serial.print("count A :");
    //Serial.print(geigerCounter.read());

    //Serial.print("\tcount B :");
    //Serial.print(geigerCounter.read());

    //Serial.println();
    //delay(1000);
}