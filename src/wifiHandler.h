#ifndef _WIFI_HANDLER_H
#define _WIFI_HANDLER_H

#include "Particle.h"

/*
function: isWifiWorking()
description: returns boolean state if Wifi is working or not
parameters: none
returns: bool(state of wifi)
*/
bool isWifiWorking(void);

/*
function: toggleWifiParticle()
description: toggles the Wifi on or off on the particle device. 
parameters: none
returns: none
*/
void toggleWifiParticle(void);

/*
function: enableListeningMode()
description: enables listening mode on the particle photon
parameters: none
returns: none
*/
void enableListeningMode(void);

#endif