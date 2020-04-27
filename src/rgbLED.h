#if !defined _RGBLED_H
#define _RGBLED_H
#include "neopixel.h"

#define PIXEL_PIN A0
#define PIXEL_COUNT 24
#define PIXEL_TYPE WS2812B
#define BRIGHTNESS 40 // 0 - 255

/*
class: notificationLight
description: class that handles controlling the rgb notifcation circle. 
*/
class notificationLight{
    public: 
 
        /*
        function: setupLEDs()
        description: startup sequence for setting up the RGB LED strip on the front of the heart. 
        parameters: none
        returns: none
        */
        void setupLEDs(void);
        
        /*
        function: setStrip(int red, int green, int blue)
        description: sets the entire strip to a single RGB value
        parameters: int red, int green, int blue 
        returns: none
        */
        void setStrip(uint8_t red, uint8_t green, uint8_t blue);
        
        /*
        function: updateTime()
        description: sets the entire strip to the right time based off color values
        parameters: none
        returns: none
        */
        void updateTime(void);
        
        /*
        function: setLED(int l, int)
        description: set's a specific LED to a specific color
        parameters: uint16_t l(position), uint8_t r, uint8_t g, uint8_t b
        returns: none
        */
        void setLED(uint16_t l, uint8_t r, uint8_t g, uint8_t b);
        
        /*
        function: sleepLEDs()
        description: turns off the LED strip
        parameters: none
        returns: none
        */
        void sleepLEDS(void);
        
        /*
        function: wakeLEDs()
        description: set's the brightness and re-displays whatever content that was on the screen
        parameters: none
        returns: none
        */
        void wakeLEDS(void);
        
        /*
        function: playWithLEDS()
        description: fills in the LED's to random differnet colors 
        parameters: none
        returns: none
        */
        void playWithLEDS(void);
 
    private: 
        Adafruit_NeoPixel rgb = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
        uint16_t playPixelCursor = 0;
        uint16_t playColorCursor = 0;

};
    
#endif