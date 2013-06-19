/*
 *  AP_RangeFinder_test
 *  Code by DIYDrones.com
 */

#include <FastSerial.h>
#include <AP_Common.h>
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

AP_GeigerCounter geigerCounter(A11,A12);       // use AN0 analog pin for APM2 on left


void setup()
{
    Serial.begin(115200);
    Serial.println("GeigerCounter Test");
    Serial.print("Sonar Type: ");
    Serial.println(SONAR_TYPE);

    isr_registry.init();
    timer_scheduler.init(&isr_registry);

    // initialise communication method (analog read or i2c)
#if SONAR_TYPE == AP_RANGEFINDER_MAXSONARI2CXL
    I2c.begin();
    I2c.timeOut(5);
    I2c.setSpeed(true); // initially set a fast I2c speed, and drop it on first failures
#else
# ifdef USE_ADC_ADS7844
    adc.Init(&timer_scheduler);   // APM ADC initialization
    aRF.calculate_scaler(SONAR_TYPE,3.3);   // setup scaling for sonar
# else
    // initialise the analog port reader
    AP_AnalogSource_Arduino::init_timer(&timer_scheduler);
    aRF.calculate_scaler(SONAR_TYPE,5.0);   // setup scaling for sonar
# endif
#endif
}

void loop()
{
    Serial.print("dist:");
    Serial.print(aRF.read());
    Serial.print("\traw:");
    Serial.print(aRF.raw_value);
    Serial.println();

#if SONAR_TYPE == AP_RANGEFINDER_MAXSONARI2CXL
    if( !aRF.healthy ) {
        Serial.println("not healthy!");
    }
    aRF.take_reading();
#endif
    delay(100);
}
