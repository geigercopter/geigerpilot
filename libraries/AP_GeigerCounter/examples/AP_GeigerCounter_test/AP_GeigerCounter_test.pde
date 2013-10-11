/*
 *  AP_Geigercounter_test
 */

#include "AP_GeigerCounter.h"
#include "InterruptDispatcher.h"

//#define USE_AP_VAR
#include <FastSerial.h>
/*
#include <AP_Common.h>
#include <AP_Math.h>
*/


//extern "C" void atexit( void ) { } 

////////////////////////////////////////////////////////////////////////////////
// Serial ports
////////////////////////////////////////////////////////////////////////////////
FastSerialPort0(Serial);        // FTDI/console

//GeigerTube tube1(PINB5);
//GeigerTube tube2(PINB6);
#define GEIGER_TUBES_COUNT 2

GeigerTube tubes[GEIGER_TUBES_COUNT] = {(PCINT5, RISING), (PCINT6, RISING)};

InterruptDispatcher_PCINT0_vect & dispatcher = InterruptDispatcher_PCINT0_vect::GetInstance();

AP_GeigerCounter geigerCounter(tubes, GEIGER_TUBES_COUNT);

void setup()
{
    Serial.begin(115200);
    Serial.println("GeigerCounter Test");
   
    for(int i=0; i< GEIGER_TUBES_COUNT; i++)
    {
        dispatcher.Register(&tubes[i]);
        Serial.printf("Registering tube %d\n", i);
    }
}

void loop()
{
    delay(1000);
    
    geigerCounter.beat();
    dispatcher.List();
    
   for(int i=0;i<GEIGER_TUBES_COUNT;i++) printreport(tubes[i]);
   
   Serial.println("###############################");
   Serial.printf("dispatcher counts : %d\n", InterruptDispatcher_PCINT0_vect::GetInstance().count);
   /*
   Serial.printf("dispatcher dbg1 : %d\n", InterruptDispatcher_PCINT0_vect::GetInstance().dbg1);
   Serial.printf("dispatcher dbg2 : %d\n", InterruptDispatcher_PCINT0_vect::GetInstance().dbg2);
   Serial.printf("dispatcher dbg3 : %d\n", InterruptDispatcher_PCINT0_vect::GetInstance().dbg3);
*/

    //Serial.printf("geigercounter reads : %d\n", geigerCounter.read());
    
    //for(int i=0;i<GEIGER_NUM_TUBES;i++) Serial.printf("tube[%d] reads : %d\n", i, tubes[i].read());

}

void printreport(GeigerTube & tube)
{
    Serial.println("###############################");
    Serial.printf("GEIGER_TUBE_CPM: %d\n", GEIGER_TUBE_CPM);
    Serial.printf("tube counts : %d\n", tube.count);

    for(int i=0;i<GEIGER_TUBE_AVERAGES_BITSHIFT;i++) Serial.printf("tube average[%d] : %d\n", i, tube.report.averages[i]);

    Serial.printf("tube total : %d\n", tube.report.total);

    Serial.printf("tube uSv : %f\n", tube.report.uSv);
}
