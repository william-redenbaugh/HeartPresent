#include "HMI.h"

/*
function: setup()
description: set's up whatever possible with the HMI
parameters: none
returns: none
*/
void HMIScreen::setup(void){
    nexInit();//sets up the HMI initialization sequence
    setBaudrate(115200);//sets to the fastest baud rate supported by the HMI
    
    sendCommand("sleep=0");
    delay(100);
    sendCommand("dim=60");
    delay(100);
    sendCommand("page 4");
    delay(100);
    sendCommand("page 4");
        
}

/*
function: homeHMI()
description: brings the HMI home!
parameters: none
returns: none
*/
void HMIScreen::home(void){
    sendCommand("page 0");
}

/*
function: wake()
description: wakes up the HMI!
parameters: none
returns: none
*/
void HMIScreen::wake(void){
    sendCommand("sleep = 0");
    sendCommand("dim = 50");
}

/*
function: sleep()
description: sleeps the HMI!
parameters: none
returns: none
*/
void HMIScreen::sleep(void){
    sendCommand("sleep = 1");
    sendCommand("dim = 0");
}

/*
function: setProgressBar(int x)
description: allows us to have a progress bar mode. 
parameters: int x(percentage of the progress bar complete)
returns: none
*/
void HMIScreen::setProgressBar(int x){
    loadingBar.setValue(x);
}

/*
function: pushHomeText()
description: changes home HMI text!
parameters: String str(data for the setText)
returns: none
*/
void HMIScreen::pushHomeText(String str){
    String data = "g0.txt=" + '"' + str + '"';
    sendCommand(str);
}

/*
function: pushQRText()
description: changes the qr code! so you can read it with a smartphone or something :)
parameters: String str(data for the setText)
returns: none
*/
void HMIScreen::changeQRText(String str){
    String data = "qr0.txt=" + '"' + str + '"';
    sendCommand(str);
}

/*
function: lock()
description: set's hmi to lock screen
parameters: none
returns: none
*/
void HMIScreen::lock(void){
    sendCommand("page 13");
    sendCommand("dim=20");
}

/*
function: run()
description: used to search and wait for callbacks from the HMI
parameters: none
returns: none
*/
void HMIScreen::run(void){
    nexLoop(this->nex_listen_list);//listens out for events attached to the HMI interface. 
}