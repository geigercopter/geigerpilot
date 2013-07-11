/* 
 * File:   GeigerCounter.h
 * Author: crasher
 *
 * Created on 7 juin 2013, 15:21
 */

extern "C" {
  // AVR LibC Includes
  #include <inttypes.h>
}

#ifndef GeigerCounter_h
#define	GeigerCounter_h

class GeigerCounter
{
public:
    virtual uint16_t read(int channel) = 0;
    virtual double measure(int channel) = 0;
    virtual void beat() = 0;
    virtual /*inline*/ void notify() = 0;
    //virtual ~GeigerCounter() = 0;
    GeigerCounter() {};
    ~GeigerCounter() {};
};

#endif	/* GeigerCounter_h */