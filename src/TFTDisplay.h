/*
function: tftDisplay.h
Description of .h file: \
This file handles as much of the TFT printing and setup functions as possible within it's parameters. :)
*/

#if !defined _TFTDISPLAY_H
#define _TFTDISPLAY_H
//#include <Adafruit_mfGFX.h>//gfx library to handdle graphics for  tft lcd stuff
#include <Adafruit_ILI9341.h>//library handling adafruit ili tft display

//imports all libraries
//setting pin denominations for SPI interface on TFTLCD
#define TFT_DC D6
#define TFT_CS D5
#define TFT_MOSI D2
#define TFT_MISO D3
#define TFT_CLK D4
#define TFT_RST D7

class TFTDisplay{
    public:
        /*
        function: setupTFTDisplay()
        description: initializes and tests the tft display so we can verify it it's working properly.  
        parameters: none
        returns: none
        */
        void setupTFTDisplay(void);
        
        /*
        function: updateTimeDisplay()
        description: takes time data for the arduino, and prints it into the TFT display. 
        parameters: none
        returns: none
        */
        void updateTimeDisplay(void);
        
        /*
        function: printTFT()
        description: takes in a string, and some paramaters, and prints that text onto the TFT according to said paramters. 
        parameters: x axis(x, integer), y axis(y, integer), font size (fontSize, integer), String (str)
        returns: none
        */
        void printTFT(int x, int y, int fontSize, String Str);
        
        /*
        function: fillBlack()
        description: fills in the tft screen with black. 
        parameters: none
        returns: none
        */
        void fillBlack(void);
        
        /*
        function: printTFT()
        description: clears out a string. takes in a string, sets font to size 3, and prints out the texts. 
        parameters: String str. 
        returns: none
        */
        void printTFT(String str);
    
    private:
        // Creating instance of tft lcd object for manipulation.
        Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
    
};
#endif