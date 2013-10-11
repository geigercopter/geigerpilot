/* 
 * File:   GeigerTube.h
 * Author: crasher
 *
 * Created on 7 juin 2013, 15:21
 */
/*
extern "C" {
  // AVR LibC Includes
  #include <inttypes.h>
}
*/
#ifndef GeigerTube_h
#define	GeigerTube_h

  // size of measure array
#define GEIGER_TUBE_HISTORY_LEN 16
  // averages bit ranks
#define GEIGER_TUBE_AVERAGES_BITSHIFT 4

 // delay between 2 measurements (in seconds)
#define GEIGER_TUBE_MEASURE_DELAY 4

#define GEIGER_TUBE_BASE_CPM 186
/*
 * this is a HACK. As for now : 
 * - we cant detect Tube pin IRQ direction, so x2 for FALL and RAISE signals
 * - x2 as we cant identify pin who triggered IRQ, so the signal is dispatched
 *      to each GeigerTube objects declared (2 in this case)
 * 
 * here we have 2 tubes x2 for raise + fall = 4
 * 
 * This is hardware signal issue and should be temporary as we'll resolve
 * the issue widen . 
 * 
 */
#define GEIGER_TUBE_CPM_MULTIPLIER 4
#define GEIGER_TUBE_CPM GEIGER_TUBE_BASE_CPM * GEIGER_TUBE_CPM_MULTIPLIER

#include <FastSerial.h>
#include "IrqNotifiable.h"

class GeigerTube : public IrqNotifiable
{
public:
    GeigerTube(uint8_t pin);
    uint16_t read();
    float buildReport();
    void beat();
    void notify();
    
    volatile uint8_t count;

    struct Report {
        uint16_t total;
        uint16_t averages[GEIGER_TUBE_AVERAGES_BITSHIFT];
        float uSv;
    };
    Report report;
protected:

    struct Measure {
        uint32_t timestamp;
        uint8_t count;
    };

    Measure measures[GEIGER_TUBE_HISTORY_LEN];
    uint8_t beatcount;
    uint8_t lastpoint;
};

#endif	/* GeigerTube_h */