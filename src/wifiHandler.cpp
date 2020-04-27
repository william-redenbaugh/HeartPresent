#include "wifiHandler.h"

/*
function: isWifiWorking()
description: returns boolean state if Wifi is working or not
parameters: none
returns: bool(state of wifi)
*/
bool isWifiWorking(void){

    if(Particle.connected())
        return true;
    else
        return false;    

}
/*
function: toggleWifiParticle()
description: toggles the Wifi on or off on the particle device. 
parameters: none
returns: none
*/
void toggleWifiParticle(void){
    if(Particle.connected())
        WiFi.off();
    else{
        WiFi.on();
        Particle.connect();
    }
}
/*
function: enableListeningMode()
description: enables listening mode on the particle photon
parameters: none
returns: none
*/
void enableListeningMode(void){
    WiFi.disconnect();
    WiFi.listen();
}