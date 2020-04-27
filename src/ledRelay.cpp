#include "ledRelay.h"

/*
function: ledStripStatusString()
description: returns the boolean of the led strip as a string
parameters: none
returns: String(ledStripStatus)
*/
String LEDRelay::ledStripStatusString(void){
   if(this->ledStripStatus)
    return "LED Strip: True";
   else
    return "LED Strip: False";
}

/*
function: setupLEDStrip()
description: sets the pin definitions and tests the LED strip relay
parameters: none
returns: none
*/
void LEDRelay::setupLEDStrip(void){
    pinMode(WKP, OUTPUT);//setups WKP pin as an output, rather than a wakeup pin
    this->ledStripStatus = false; //ledStripStatus is disabled. 
    digitalWrite(WKP, HIGH);
    delay(500);
    digitalWrite(WKP, LOW);
}

/*
function: toggle()
description: toggles the LED. 
parameters: none
returns: none
*/
void LEDRelay::toggle(void){
    this->ledStripStatus =! this->ledStripStatus; 
    digitalWrite(WKP, this->ledStripStatus);
}
/*
function: setLED(bool LED)
description: turns on or off LED
parameters: none
returns: none
*/
void LEDRelay::setLED(bool LED){
    this->ledStripStatus = LED;
    digitalWrite(WKP, LED);
}