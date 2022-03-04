#include "alarmRelay.h"

/*
function: setupRelay()
description: initializes a relay object with a specific pin value
parameters: none
returns: none
*/
void alarmRelay::setupRelay(int p){
    this->pin = p; 
    this->armed = true; 
    pinMode(pin, OUTPUT);
}

/*
function: beepOnce()
description: beeps once within a given delay interval, with a 50 percent duty cycle
parameters: none
returns: none
*/
void alarmRelay::beepOnce(int d){
    if(this->armed){
        digitalWrite(pin, HIGH);
        delay(d);
        digitalWrite(pin, LOW);
    }
}

/*
function: beepTwice()
description: beeps twice within a given delay interval, with a 50 percent duty cycle
parameters: none
returns: none
*/
void alarmRelay::beepTwice(int d){
    if(this->armed){
        digitalWrite(pin, HIGH);
        delay(d);
        digitalWrite(pin, LOW);
        delay(d);
        digitalWrite(pin, HIGH);
        delay(d);
        digitalWrite(pin, LOW);
    }
}

/*
function: beepThrice()
description: beeps three times within a given delay interval, with a 50 percent duty cycle
parameters: none
returns: none
*/
void alarmRelay::beepThrice(int d){
    if(this->armed){
        digitalWrite(pin, HIGH);
        delay(d);
        digitalWrite(pin, LOW);
        delay(d);
        digitalWrite(pin, HIGH);
        delay(d);
        digitalWrite(pin, LOW);
        delay(d);
        digitalWrite(pin, HIGH);
        delay(d);
        digitalWrite(pin, LOW);
    }
}

/*
function: beepQuad()
description: beeps 4 times within a given delay interval, with a 50 percent duty cycle
parameters: none
returns: none
*/
void alarmRelay::beepQuad(int d){
    if(this->armed){
        digitalWrite(pin, HIGH);
        delay(d);
        digitalWrite(pin, LOW);
        delay(d);
        digitalWrite(pin, HIGH);
        delay(d);
        digitalWrite(pin, LOW);
        delay(d);
        digitalWrite(pin, HIGH);
        delay(d);
        digitalWrite(pin, LOW);
        delay(d);
        digitalWrite(pin, HIGH);
        delay(d); 
        digitalWrite(pin, LOW);
    }
}

/*
function: beep()
description: beeps a defined amount of times with a specificed delay speed with a 50 percent duty cycle. 
parameters: none
returns: none
*/
void alarmRelay::beep(int d, int t){
    for(int i = 0; i < t; i++){
        digitalWrite(pin, HIGH);
        delay(d);
        digitalWrite(pin, LOW);
        delay(d); 
    }
}

/*
function: setAlarm(bool b)
description: sets beeper status. 
parameters: alarm state 
returns: none
*/
void alarmRelay::setAlarm(bool b){
    this->armed = b;
}