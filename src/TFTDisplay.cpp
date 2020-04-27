#include "TFTDisplay.h"

/*
function: setupTFTDisplay()
description: initializes and tests the tft display so we can verify it it's working properly.  
parameters: none
returns: none
*/
void TFTDisplay::setupTFTDisplay(void){
    // Sets up TFT display.
    this->tft.begin();
    // Clears the display. 
    this->tft.fillScreen(ILI9341_BLACK);
    
    // Filling the display with a bunch of different characters.
    this->tft.setRotation(1);
    
    yield();
    this->tft.fillScreen(ILI9341_RED);
    yield();
    this->tft.fillScreen(ILI9341_GREEN);
    yield();
    this->tft.fillScreen(ILI9341_BLUE);
    yield();
    this->tft.fillScreen(ILI9341_BLACK);
    yield();
}

/*
function: updateTimeDisplay()
description: takes time data for the arduino, and prints it into the TFT display. 
parameters: none
returns: none
*/
void TFTDisplay::updateTimeDisplay(void){
    //fill in screen, then update the Time display. 
    this->tft.fillScreen(ILI9341_BLACK);
    this->tft.setCursor(105,40);
    this->tft.setTextSize(4);//sets to normal text size
    this->tft.print(Time.hour());
    this->tft.print(":");
    
    if(Time.minute() < 10){
        this->tft.print("0");
        this->tft.print(Time.minute());
        this->tft.setTextSize(3);//sets to normal text size
    }
    else{
        this->tft.print(Time.minute());
        this->tft.setTextSize(3);//sets to normal text size
    }
    
    this->tft.setCursor(85,100);
    this->tft.print(Time.month());//prints month 
    this->tft.print("/");
    this->tft.print(Time.day());
    this->tft.print(":");
    this->tft.print(Time.year());
    
    if (Time.month() > 10){
        this->tft.setCursor(25, 140);
        this->tft.print("Merry Christmas");
        this->tft.setCursor(40, 170);
        this->tft.print("Thanksgivings");
    }
    
    if (Time.month() == 2 && Time.day() == 14){
        this->tft.setCursor(25, 140);
        this->tft.print("Happy Valentines");
        this->tft.setCursor(40, 170);
        this->tft.print("I love you :)");
    }
} 

/*
function: printTFT()
description: takes in a string, and some paramaters, and prints that text onto the TFT according to said paramters. 
parameters: x axis(x, integer), y axis(y, integer), font size (fontSize, integer), String (str)
returns: none
*/
void TFTDisplay::printTFT(int x, int y, int fontSize, String Str)
{
    this->tft.setCursor(x,y);// set the cursor. 
    this->tft.setTextSize(fontSize);//set the fontsie
    this->tft.print(Str);//print text!
}

/*
function: printTFT()
description: clears out a string. takes in a string, sets font to size 3, and prints out the texts. 
parameters: String str. 
returns: none
*/
void TFTDisplay::printTFT(String str){
    tft.fillScreen(ILI9341_BLACK);//blacks out the whole display
    tft.setCursor(0, 0);//resets cursor
    tft.setTextSize(3);//sets to normal text size
    tft.print(str);
}

 /*
function: fillBlack()
description: fills in the tft screen with black. 
parameters: none
returns: none
*/
void TFTDisplay::fillBlack(void){
    tft.fillScreen(ILI9341_BLACK);
}