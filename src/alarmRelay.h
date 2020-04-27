#include "Particle.h"
#if !defined _ALARMRELAY_H
#define _ALARMRELAY_H

/*
class: alarmRelay
description: class that handles controlling the alarm relay
*/
class alarmRelay{
    public:
        /*
        function: setupRelay()
        description: initializes a relay object with a specific pin value
        parameters: none
        returns: none
        */
        void setupRelay(int p);
        
        /*
        function: beepOnce()
        description: beeps once within a given delay interval, with a 50 percent duty cycle
        parameters: none
        returns: none
        */
        void beepOnce(int d);
        
        /*
        function: beepTwice()
        description: beeps twice within a given delay interval, with a 50 percent duty cycle
        parameters: none
        returns: none
        */
        void beepTwice(int d);
        
        /*
        function: beepThrice()
        description: beeps three times within a given delay interval, with a 50 percent duty cycle
        parameters: none
        returns: none
        */
        void beepThrice(int d);
        
        /*
        function: beepQuad()
        description: beeps 4 times within a given delay interval, with a 50 percent duty cycle
        parameters: none
        returns: none
        */
        void beepQuad(int d);
        
        /*
        function: beep()
        description: beeps a defined amount of times with a specificed delay speed with a 50 percent duty cycle. 
        parameters: none
        returns: none
        */
        void beep(int d, int t);
        
        /*
        function: setAlarm(bool b)
        description: sets beeper status. 
        parameters: alarm state 
        returns: none
        */
        void setAlarm(bool b);
    
    private:
    
        // GPIO Pin
        int pin; 
        
        // Current State of Relay
        bool armed;
    
};
#endif