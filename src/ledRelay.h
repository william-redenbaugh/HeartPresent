#ifndef _LEDRELAY_H
#define _LEDRELAY_H

#include "Particle.h"

class LEDRelay{

    public: 
        /*
        function: ledStripStatusString()
        description: returns the boolean of the led strip as a string
        parameters: none
        returns: String(ledStripStatus)
        */
        String ledStripStatusString(void);
        
        /*
        function: setupLEDStrip()
        description: sets the pin definitions and tests the LED strip relay
        parameters: none
        returns: none
        */
        void setupLEDStrip(void);
        
        /*
        function: LEDtoggle()
        description: toggles the LED. 
        parameters: none
        returns: none
        */
        void toggle(void);
        
        /*
        function: setLED(bool LED)
        description: turns on or off LED
        parameters: none
        returns: none
        */
        void setLED(bool LED);
        
    private: 
        bool ledStripStatus = false; 
};

#endif 