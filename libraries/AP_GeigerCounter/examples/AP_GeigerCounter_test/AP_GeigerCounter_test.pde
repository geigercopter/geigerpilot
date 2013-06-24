/*
 *  AP_Geigercounter_test
 */

/*
#include <FastSerial.h>
#include <AP_Common.h>
//#include "../../AP_GeigerCounter.h"
*/
#include "AP_GeigerCounter.h"

// includes
/*
#include <AP_Math.h>
#include <Filter.h>
#include <I2C.h>                // Arduino I2C lib
#include <AP_RangeFinder.h>     // Range finder library
#include <Arduino_Mega_ISR_Registry.h>
#include <AP_PeriodicProcess.h>
#include <AP_ADC.h>                             // ArduPilot Mega Analog to Digital Converter Library
#include <AP_AnalogSource.h>
#include <ModeFilter.h>                 // mode filter
#include <AP_Buffer.h>
*/

AP_GeigerCounter geigerCounter(A11,A12);
//AP_GeigerCounter geigerCounter(A1,A2);

void setup()
{
    Serial.begin(115200);
    Serial.println("GeigerCounter Test");
    geigerCounter.init();
}

void loop()
{
    Serial.print("count A :");
    Serial.print(geigerCounter.read());

    Serial.print("\tcount B :");
    Serial.print(geigerCounter.read());

    Serial.println();
    delay(1000);
}
