#ifndef _HMI_H 
#define _HMI_H

#include "Particle.h"
#include "Nextion.h"
/*
class: HMIScreen
description: Allows me to deal with interactions with the Human machine interace.

*/
struct HMIScreen{
    
    // HMI INTERACTION VARIABLES BEGIN // 
    bool notifOff = false; //boolean to know if notifications are on or off. 
    bool picOff = false; //boolean to know if pictures scrowling is on or off...
   
    NexButton sleepMode = NexButton(0,3, "sL");//initializes the sleep mode button NexButton(pageNumber, ID number, ID name)
    NexButton toggleLEDStrip = NexButton(00, 05, "tL");//toggleLED button
    NexButton toggleWifi = NexButton(1, 1, "toggleWifi");
    NexButton wakeUpButton = NexButton(3,1, "wakeUpButton");
    
    //stuff for 
    NexProgressBar loadingBar = NexProgressBar(4, 2, "j0");
    NexText loadingBarTextBox = NexText(4,3, "textBox");
    
    //stuff from the home screen scrolling text nav!
    NexText homeText = NexText(0,6, "g0");
    NexButton functionHome= NexButton(0,2, "nP");
    
    //text data for sendText, page 17
    NexText hmiText = NexText(17, 1, "t0");
    
    //qr data for sendText, page 14
    NexText qrTag = NexText(14, 1, "qrTag");
    
    //Stuff for Quick Messages
    NexButton QuickMessage1 = NexButton(23,1,"b0");
    NexButton QuickMessage2 = NexButton(23,3,"b1");
    NexButton QuickMessage3 = NexButton(23,4,"b2");
    NexButton QuickMessage4 = NexButton(23,5,"b3");
    NexButton QuickMessage5 = NexButton(23,6,"b4");
    NexButton QuickMessage6 = NexButton(23,7,"b5");

    //stuff for the keyboard commands!!!
    NexButton getTextKeyboard = NexButton(22, 38, "b37");
    NexText keyboardText = NexText(22, 2, "tb0");
    NexText terminalText = NexText(22, 40, "t0");
    char keyBuffer[192] = {0};
    
    //function nav pages
    NexButton Function1 = NexButton(1,5, "b2");
    NexButton Function2 = NexButton(1,6, "b3");
    NexButton Function3 = NexButton(1,12, "b9");
    NexButton Function4 = NexButton(1,13, "b10");
    NexButton QuickMessage = NexButton(1,11,"b8");
    
    //these function variables are designed to be multi use, so we can re program their labels and their function. Just trying to make it easier to add in new functionality later on!
    //functions for FunctionPage1, page 11. 
    NexButton function11 = NexButton(11, 1, "function11");
    NexButton function12 = NexButton(11, 2, "function12");
    NexButton function13 = NexButton(11, 3, "function13");
    NexButton function14 = NexButton(11, 4, "function14");
    NexButton function15 = NexButton(11, 5, "function15");
    NexButton function16 = NexButton(11, 6, "function16");
    NexButton function17 = NexButton(11, 7, "function17");
    NexButton function18 = NexButton(11, 8, "function18");
    
    //functions for FunctionPage2, page 12
    NexButton function21 = NexButton(12, 1, "function21");
    NexButton function22 = NexButton(12, 2, "function22");
    NexButton function23 = NexButton(12, 3, "function23");
    NexButton function24 = NexButton(12, 4, "function24");
    NexButton function25 = NexButton(12, 5, "function25");
    NexButton function26 = NexButton(12, 6, "function26");
    NexSlider slider27 = NexSlider(12, 7, "function 27");
    NexSlider slider28 = NexSlider(12, 8, "function 27");    
    NexSlider slider29 = NexSlider(12, 9, "function 27");
    
    //functions for gauges, page 15
    NexGauge guage151  = NexGauge(15, 1, "z0");
    NexText guage151text = NexText(15, 4, "he");
    NexGauge guage152  = NexGauge(15, 3, "z1");
    NexText guage152text = NexText(15, 5, "he");
    NexGauge guage153  = NexGauge(15, 2, "z2");
    NexText guage153text = NexText(15, 6, "he");
    
    NexNumber number154 = NexNumber(15,7,"n0");
    NexText number154text = NexText(15, 8, "he");
    NexNumber number155 = NexNumber(15,9,"n1");
    NexText number155text = NexText(15, 10, "he");
    NexNumber number156 = NexNumber(15,11,"n2");
    NexText number156text = NexText(15, 12, "he");
    
    //functions for guages2, page 16
    NexNumber number161 = NexNumber(16,11,"n0");
    NexText number116text = NexText(16, 12, "he");
    NexNumber number162 = NexNumber(16,13,"n0");
    NexText number162text = NexText(16, 14, "he");
    NexNumber number163 = NexNumber(16,15,"n0");
    NexText number163text = NexText(16, 16, "he");
    NexNumber number164 = NexNumber(16,17,"n0");
    NexText number164text = NexText(16, 18, "he");
    NexNumber number165 = NexNumber(16,19,"n0");
    NexText number165text = NexText(16, 20, "he");
    NexNumber number166 = NexNumber(16,21,"n0");
    NexText number166text = NexText(16, 22, "he");
    NexNumber number167 = NexNumber(16,1,"n0");
    NexText number167text = NexText(16, 2, "he");
    NexNumber number168 = NexNumber(16,3,"n0");
    NexText number168text = NexText(16, 4, "he");
    NexNumber number169 = NexNumber(16,5,"n0");
    NexText number169text = NexText(16, 6, "he");
    
    NexTouch *nex_listen_list[14] = {
        &QuickMessage1,
        &QuickMessage2,
        &QuickMessage3,
        &QuickMessage4,
        &QuickMessage5,
        &QuickMessage6,
        &QuickMessage,
        &functionHome,
        &sleepMode,
        &toggleLEDStrip,
        &toggleWifi,
        &wakeUpButton,
        &getTextKeyboard,
        NULL
    };
    
    // HMI INTERACTION VARIABLES END// 
    
    // HMI HELPER FUNCTIONS BEGIN //
    
    /*
    function: setup()
    description: set's up whatever possible with the HMI
    parameters: none
    returns: none
    */
    void setup(void);
    
    /*
    function: homeHMI()
    description: brings the HMI home!
    parameters: none
    returns: none
    */
    void home(void);
    
    /*
    function: wake()
    description: wakes up the HMI!
    parameters: none
    returns: none
    */
    void wake(void);
    
    /*
    function: sleep()
    description: sleeps the HMI!
    parameters: none
    returns: none
    */
    void sleep(void);
    
    /*
    function: setProgressBar(int x)
    description: allows us to have a progress bar mode. 
    parameters: int x(percentage of the progress bar complete)
    returns: none
    */
    void setProgressBar(int x);
    
    /*
    function: pushHomeText()
    description: changes home HMI text!
    parameters: String str(data for the setText)
    returns: none
    */
    void pushHomeText(String str);
    
    /*
    function: pushQRText()
    description: changes the qr code! so you can read it with a smartphone or something :)
    parameters: String str(data for the setText)
    returns: none
    */
    void changeQRText(String str);
    
    /*
    function: lock()
    description: set's hmi to lock screen
    parameters: none
    returns: none
    */
    void lock(void);
    
    /*
    function: run()
    description: used to search and wait for callbacks from the HMI
    parameters: none
    returns: none
    */
    void run(void);
    // HMI HELPER FUNCTIONS END //
};

#endif 