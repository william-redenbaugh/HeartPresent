#ifndef _CLOCKCONTROL_H
#define _CLOCKCONTROL_H

#include "Particle.h"

class ClockControl{
    public: 
        /*
        function: void setup(UDP *Udp)
        description:  Sets up the udp interface. 
        parameters: none
        returns:  none
        */
        void setup(UDP *Udp);
        
        /*
        function: wake(void)
        description:  sends the wake command to the clock
        parameters: none
        returns:  none
        */
        void wake(void);
        
        /*
        function: sleep(void)
        description:  sends the sleep command to clock
        parameters: none
        returns:  none
        */
        void sleep(void);
        
        /*
        function: send_msg(String str)
        description:  sends a message to be displayed on the heart. 
        parameters: String str(message to be sent)
        returns:  none
        */
        void send_msg(String str);
        
    private:
    // Reference to the main UDP handler 
    UDP *Udp;
    // local ip address that connects to the clock
    IPAddress remoteIP = IPAddress(192, 168, 1, 24);
    
    // Port to connect to the clock
    int port = 4210; 
    
    // Command Bytearrays that signal the clock to sleep or wake up. 
    uint8_t sleep_buff[5] = {40, 40, 50, 65, 0};
    uint8_t wake_buff[5] = {40, 40, 50, 65, 1};
};

#endif