#include "ClockControl.h"

/*
function: void setup(UDP *Udp)
description:  Sets up the udp interface. 
parameters: none
returns:  none
*/
void ClockControl::setup(UDP *Udp){
    this->Udp = Udp; 
}

/*
function: wake(void)
description:  sends the wake command to the clock
parameters: none
returns:  none
*/
void ClockControl::wake(void){
    Udp->sendPacket(this->wake_buff, sizeof(this->wake_buff), this->remoteIP, this->port);
}

/*
function: sleep(void)
description:  sends the sleep command to clock
parameters: none
returns:  none
*/
void ClockControl::sleep(void){
    Udp->sendPacket(this->sleep_buff, sizeof(this->wake_buff), this->remoteIP, this->port);
}


/*
function: send_msg(String str)
description:  sends a message to be displayed on the heart. 
parameters: String str(message to be sent)
returns:  none
*/

void ClockControl::send_msg(String str){
    
    uint8_t msg[4 + str.length()];
    msg[0] = 40; 
    msg[1] = 40; 
    msg[2] = 50; 
    msg[3] = 60; 
    
    for(uint16_t i = 0; i < str.length(); i++){
        msg[4 + i] = str[i];
    }
    
    Udp->sendPacket(msg, sizeof(msg), this->remoteIP, this->port);
}