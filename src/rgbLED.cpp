#include "rgbLED.h"

/*
function: setupLEDs()
description: startup sequence for setting up the RGB LED strip on the front of the heart. 
parameters: none
returns: none
*/
void notificationLight::setupLEDs(void){
    this->rgb.setBrightness(BRIGHTNESS);
    this->rgb.begin();
    this->rgb.show(); // Initialize all pixels to 'off'
}

/*
function: setStrip(int red, int green, int blue)
description: sets the entire strip to a single RGB value
parameters: int red, int green, int blue 
returns: none
*/
void notificationLight::setStrip(uint8_t red, uint8_t green, uint8_t blue){
    for(int i = 0; i < PIXEL_COUNT; i++)
    {
        this->rgb.setPixelColor(i, red, green, blue);
    }
    this->rgb.show();
}

/*
function: updateTime()
description: sets the entire strip to the right time based off color values
parameters: none
returns: none
*/
void notificationLight::updateTime(void){
    for(uint8_t i = 0; i < 24; i++){
        this->rgb.setPixelColor(i, 100, 100, 100);
    }
    for(uint8_t i = 0; i < Time.hour(); i++){
        this->rgb.setPixelColor(i, 0,0,0);   
    }
    
    this->rgb.show();
}

/*
function: setLED(int l, int)
description: set's a specific LED to a specific color
parameters: uint16_t l(position), uint8_t r, uint8_t g, uint8_t b
returns: none
*/
void notificationLight::setLED(uint16_t l, uint8_t r, uint8_t g, uint8_t b){
    this->rgb.setPixelColor(l, r, g, b);
    this->rgb.show();
    
}

/*
function: sleepLEDs()
description: turns off the LED strip
parameters: none
returns: none
*/
void notificationLight::sleepLEDS(void){
    this->rgb.setBrightness(0);
    this->rgb.show();
}

/*
function: wakeLEDs()
description: set's the brightness and re-displays whatever content that was on the screen
parameters: none
returns: none
*/
void notificationLight::wakeLEDS(void){
    this->rgb.setBrightness(BRIGHTNESS);
    this->rgb.show();
}

/*
function: playWithLEDS()
description: fills in the LED's to random differnet colors 
parameters: none
returns: none
*/
void notificationLight::playWithLEDS(void)
{
    if (this->playPixelCursor % 4 == 0)
        this->playColorCursor = rand() % 3;
   
    switch(playColorCursor){
        case 0:
            this->setLED(playPixelCursor, 138, 43, 226);
            break;
        case 1:
            this->setLED(playPixelCursor, 100, 10, 10);
            break;
        case 2: 
            this->setLED(playPixelCursor, 100, 80, 100);
            break;
        default:
            break;
    }
    
    this->playPixelCursor++;
    
    if(this->playPixelCursor > 24)
        this->playPixelCursor = 0;
}