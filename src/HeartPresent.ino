#include "ClockControl.h"
#include "HMI.h"
#include "imuSensor.h"
#include "ledRelay.h"
#include "TFTDisplay.h"
#include "cardReader.h"
#include "wifiHandler.h"
#include "rgbLED.h"
#include "alarmRelay.h"
#include "globalVariables.h"

//SYSTEM_THREAD(ENABLED);// allows RTOS to do it's thing, and for all the functions of the RGB strip to be handled!!!!!
//SYSTEM_MODE(MANUAL);//allows me to manage when the particle should be listening to requests or not!!!

// GLOBAL VARIABLES BEGIN //

// Relay controlling the beeper built into the system.
alarmRelay alarm;

// Neopixel Notification Light.
notificationLight notifLight;

// Lamp Light, allows us to have lamp features.
LEDRelay lampLight;

// Display for publishing notifications onto heart.
TFTDisplay tftDisplay;

// Allows us to read RFID cards so only authorized users may use the machine.
rfidReader cardReader;
// Keeps track of what's locked and what's not
LockStatus lockStatus;

NotificationSettings notifications;

// Allows us to detect motion interacting with the heart.
IMUSensor motionSensor;

// HMI variables live here!
HMIScreen hmiScreen;

// Allows us to keep sleep mode information saved.
SleepMode sleepMode;

// For whatever reason the HMI needs the serial device to be defined like this(not preferable, if I rewrite the firwmware to the HMI, I'll do it differently)
USARTSerial &nexSerial = Serial1; //chooses the right serial device

// Counters for dealing with timing operations in the main loop
Counters counter;

// Handler for controlling the clock.
ClockControl clock_control;
UDP Udp;

// GLOBAL VARIABLES END //

// TIMERS HANDLERS BEGIN //

Timer ms_100_task_handler(100, ms_100_task);
Timer ms_300_task_handler(200, ms_300_task);
Timer ms_1000_task_handler(1000, ms_1000_task);
Timer s_10_task_handler(10000, s_10_task);
Timer s_30_task_handler(30000, s_30_task);
Timer s_60_task_handler(60000, s_30_task);

// TIMERS HANDLERS END //

// GLOBAL VARIABLES END //

// TIMERS FUNCTIONS BEGIN //

void ms_100_task(void)
{
    if (sleepMode.sleep_mode_enabled == false && lockStatus.system_locked == false)
        notifLight.playWithLEDS();

    // Checking if UDP messages arrived, parse out and chk commands.
    if (Udp.parsePacket() > 0)
    {
        uint8_t msg[4];
        for (uint8_t i = 0; i < 4; i++)
            msg[i] = Udp.read();

        if (msg[0] == 20 && msg[1] == 20 && msg[2] == 30 && msg[3] == 90)
        {
            lock();
        }
        if (msg[0] == 20 && msg[1] == 20 && msg[2] == 30 && msg[3] == 91)
        {
            unlock();
        }
        if (msg[0] == 50 && msg[1] == 50 && msg[2] == 30 && msg[3] == 92)
        {
            lampLight.toggle();
        }
        if (msg[0] == 50 && msg[1] == 50 && msg[2] == 30 && msg[3] == 91)
        {
            lampLight.setLED(true);
        }
        if (msg[0] == 50 && msg[1] == 50 && msg[2] == 30 && msg[3] == 90)
        {
            lampLight.setLED(false);
        }
        if (msg[0] == 12 && msg[1] == 12 && msg[2] == 12 && msg[3] == 12)
        {
            alarm.beepOnce(300);
        }
    }
}

void ms_300_task(void)
{
    // Allows us to change the lock status. if we get a match, we can lock and unlock the system.
    if (cardReader.readCardID())
    {
        lockStatus.system_locked = !lockStatus.system_locked;

        // Once the system lock, we need to update the status' and disable the sensors and peripherals
        if (lockStatus.system_locked)
            lock();
        // Vice versa for the unlocking the system.
        else
            unlock();
    }
}

void lock(void)
{
    // Disable the lights and turn off un needed peripherals
    lampLight.setLED(false);
    notifLight.setStrip(240, 0, 0);
    hmiScreen.lock();
    lockStatus.system_locked = true;
}

void unlock(void)
{
    // Turn back on the notification lights!
    notifLight.wakeLEDS();
    hmiScreen.wake();
    hmiScreen.home();
    lockStatus.system_locked = false;
}

void ms_1000_task(void)
{
}

void s_10_task(void)
{
    tftDisplay.updateTimeDisplay();
}

void s_30_task(void)
{
    if (lockStatus.system_locked)
    {
        tftDisplay.updateTimeDisplay();
    }
}

void s_60_task(void){
    
}

// TIMERS FUNCTIONS END //

void setup()
{
    // Setting up all the electronics in the device.
    peripherals_setup();

    threads_setup();

    lock();
    initCloudRequests();
}

void loop()
{

    // just keeping where we are for determining how long we need to wait later.
    counter.ms_per_tick = millis();

    // No uploading of any kind when the system is locked.
    if (!lockStatus.system_locked)
    {
        hmiScreen.run();
    }

    // Process that need to be run continuously, doesn't matter if system is locked or not.
    Particle.process();

    // Once we get through everything, we delay as much time is needed, or we don't delay at all and keep going
    // if need be!
    counter.current_ms = millis();
    counter.loop_tick++;
    if (counter.loop_tick == 1200)
    {
        if (!counter.stagger_push)
        {
            // Update the clock twice a minute.
            tftDisplay.updateTimeDisplay();
        }
        else
        {
            counter.stagger_push = false;
        }
        counter.loop_tick = 0;
    }
    if (counter.loop_tick == 600)
    {
        if (!counter.stagger_push)
        {
            // Update the clock twice a minute.
            tftDisplay.updateTimeDisplay();
        }
        else
        {
            counter.stagger_push = false;
        }
    }

    if ((counter.ms_per_tick + 50) > counter.current_ms)
    {
        unsigned long wait_time = 50 - (counter.current_ms - counter.ms_per_tick);
        delay(wait_time);
    }
}

void peripherals_setup(void)
{
    Time.zone(-7);
    hmi_setup();

    // Setting up the alarm relay.
    alarm.setupRelay(DAC);
    // alarm.beepOnce(400);
    hmiScreen.setProgressBar(15);

    // Setting up the notification ring in the middle of the heart.
    notifLight.setupLEDs();
    notifLight.setStrip(100, 100, 100);
    hmiScreen.setProgressBar(30);

    // Setting up the lamp features of the heart.
    lampLight.setupLEDStrip();
    lampLight.setLED(1);
    delay(500);
    lampLight.setLED(0);
    hmiScreen.setProgressBar(45);

    // Setting up the TFT side/notification display.
    tftDisplay.setupTFTDisplay();
    tftDisplay.printTFT(20, 20, 2, "Setting up...");
    hmiScreen.setProgressBar(70);

    // Setting up the rfid card reader
    cardReader.setupCardReader();
    hmiScreen.setProgressBar(85);

    // Setting up the 6DOF IMU sensor.
    motionSensor.setupAccel();
    hmiScreen.setProgressBar(90);

    // Since we don't have access to the inside of the Heart, we will disable the internal status LED.
    RGB.control(true);
    RGB.color(0, 0, 0);
    RGB.brightness(0);
    RGB.control(false);

    tftDisplay.updateTimeDisplay();
    hmiScreen.setProgressBar(100);
    hmiScreen.home();

    Udp.begin(4250);
    clock_control.setup(&Udp);
}

// Since the HMI is the most difficult and complex to setup, we will next it
// in it's own function
void hmi_setup(void)
{
    hmiScreen.setup();
    hmiScreen.sleepMode.attachPop(sleepModeCallback, &hmiScreen.sleepMode);            //sleepmode
    hmiScreen.getTextKeyboard.attachPop(keyBoardCallback, &hmiScreen.getTextKeyboard); //sleepmode
    hmiScreen.toggleLEDStrip.attachPush(toggleLEDCallback, &hmiScreen.toggleLEDStrip); //toggle led
    hmiScreen.toggleWifi.attachPop(toggleWifiCallback, &hmiScreen.toggleWifi);         //turn on/off wifi
    hmiScreen.wakeUpButton.attachPush(wakeUpCallback, &hmiScreen.wakeUpButton);
    hmiScreen.QuickMessage.attachPop(quickMessageJump, &hmiScreen.QuickMessage);
    hmiScreen.QuickMessage6.attachPop(quickMessage6Function, &hmiScreen.QuickMessage6);
    hmiScreen.QuickMessage5.attachPop(quickMessage5Function, &hmiScreen.QuickMessage5);
    hmiScreen.QuickMessage4.attachPop(quickMessage4Function, &hmiScreen.QuickMessage4);
    hmiScreen.QuickMessage3.attachPop(quickMessage3Function, &hmiScreen.QuickMessage3);
    hmiScreen.QuickMessage2.attachPop(quickMessage2Function, &hmiScreen.QuickMessage2);
    hmiScreen.QuickMessage1.attachPop(quickMessage1Function, &hmiScreen.QuickMessage1);
}

/*
function: sleepModeCallBack()
description: runs when the HMI detects a press on the sleep mode button. 
parameters: none
returns: none
*/
void sleepModeCallback(void *ptr)
{
    sleepMode.sleep_mode_enabled = true;
    hmiScreen.sleep();
    notifLight.setStrip(0, 0, 0);
    lampLight.setLED(false);
    clock_control.sleep();
}

/*
function: toggleLEDCallback()
description: toggles LED when the LED is set to toggle. 
parameters: none
returns: none
*/
void toggleLEDCallback(void *ptr)
{
    lampLight.toggle();
}

/*
function: toggleWifiCallback(void *ptr)
description: toggles Wifi on or off!
parameters: none 
returns: none
*/
void toggleWifiCallback(void *ptr)
{
    toggleWifiParticle();
}

/*
function: wakeUpCallback(void *ptr)
description: wakes up particle! 
parameters: none 
returns: none
*/
void wakeUpCallback(void *ptr)
{
    sleepMode.sleep_mode_enabled = false;
    hmiScreen.home();
    hmiScreen.wake();
    clock_control.wake();
}

/*
function: wakeUpCallback(void *ptr)
description: wakes up particle! 
parameters: none 
returns: none
*/
void keyBoardCallback(void *ptr)
{
    hmiScreen.keyboardText.getText(hmiScreen.keyBuffer, sizeof(hmiScreen.keyBuffer));
    String buffer = hmiScreen.keyBuffer;
    if (buffer.equals("exit"))
    {
        hmiScreen.terminalText.setText("Exiting");
        delay(100);
        hmiScreen.terminalText.setText("Exiting.");
        delay(100);
        hmiScreen.terminalText.setText("Exiting..");
        delay(100);
        hmiScreen.terminalText.setText("Exiting...");
        delay(100);
        hmiScreen.terminalText.setText("Exiting....");
        delay(100);
        hmiScreen.home();
    }

    if (buffer.equals("reset"))
    {
        hmiScreen.terminalText.setText("Resetting Device");
        delay(100);
        hmiScreen.terminalText.setText("Resetting Device.");
        delay(100);
        hmiScreen.terminalText.setText("Resetting Device..");
        delay(100);
        hmiScreen.terminalText.setText("Resetting Device...");
        delay(100);
        hmiScreen.terminalText.setText("Resetting Device....");
        delay(100);
        hmiScreen.terminalText.setText("Resetting Device.....");
        delay(100);
        System.reset();
    }

    if (buffer.equals("wifilisten"))
    {
        hmiScreen.terminalText.setText("Setting Wifi to listening mode...");
        enableListeningMode();
        delay(700);
        hmiScreen.terminalText.setText("WiFi has been set to listening mode!!");
    }

    if (buffer.equals("beep"))
    {
        hmiScreen.terminalText.setText("beeping...");
        //
        hmiScreen.terminalText.setText("Completed Beeping");
    }

    hmiScreen.keyboardText.setText("");
}

/*
function: quickMessageJump(void *ptr)
description: jumps to the quick message page! and sets the message names(designed to be customizable!) 
parameters: none 
returns: none
*/
void quickMessageJump(void *ptr)
{
}

/*
function: quickMessage6Function(void *ptr)
description: jumps back to the home page
parameters: none 
returns: none
*/
void quickMessage6Function(void *ptr)
{
    hmiScreen.home();
}

/*
function: quickMessage5Function(void *ptr)
description: publishes a paritcle event with a given message!
parameters: none 
returns: none
*/
void quickMessage5Function(void *ptr)
{
    Particle.publish("QuickMessage", "What are you doing?");
}

void quickMessage4Function(void *ptr)
{
    Particle.publish("QuickMessage", "I miss you :(");
}

void quickMessage3Function(void *ptr)
{
    Particle.publish("QuickMessage", "Are you in your dorm?");
}

void quickMessage2Function(void *ptr)
{
    Particle.publish("QuickMessage", "How are you doing?");
}

void quickMessage1Function(void *ptr)
{
    Particle.publish("QuickMessage", "Hey Babe");
}

// Starts up all the threads for the system!
void threads_setup(void)
{
    ms_100_task_handler.start();
    ms_300_task_handler.start();
    //ms_1000_task_handler.start();
    //s_10_task_handler.start();
    //s_30_task_handler.start();
    //s_60_task_handler.start();
}

/*
function: initCloudRequests()
description: initializes all the cloud requests. so you can send and recieve data on the particle.io console. 
parameters: none
returns: none
*/
void initCloudRequests(void)
{
    Particle.subscribe("push", push, MY_DEVICES);
    //Particle.subscribe("quiet", pushQuiet,MY_DEVICES);
    Particle.subscribe("loud", pushLoud, MY_DEVICES);
    //Particle.subscribe("toggleLED", particleToggleLED, MY_DEVICES);//allows the led Strip to be toggled remotely.
    //Particle.subscribe("printTFT", particlePrintTFT);//particle function to print data to the TFT display
    //Particle.subscribe("commandHMI", particleCommandHMI, MY_DEVICES);//particle functioin to command the nextion display.
    //Particle.subscribe("updateQR", particleUpdateQR, MY_DEVICES);
    Particle.subscribe("command", particleCommands, MY_DEVICES);
    //Particle.subscribe("toggleSleepMode", particleToggleSleepMode, MY_DEVICES);//particle function to toggle sleep mode.
    //Particle.subscribe("hook-response/get_weather", getWeatherData, MY_DEVICES);
}

/*
function: particleCommands()
description: allows you to send some commands to the particle cloud!!!!
parameters: none
returns: none
*/

void particleCommands(const char *event, const char *data)
{
    String buffer = data;
    if (buffer.equals("notifoff"))
    {
        notifications.enabled = false;
    }
    if (buffer.equals("notifon"))
    {
        notifications.enabled = true;
    }
    if (buffer.equals("picoff"))
    {
    }
    if (buffer.equals("picon"))
    {
    }
    if (buffer.equals("beep"))
    {
        alarm.beepOnce(200);
    }
    if (buffer.equals("toggleLED"))
    {
        lampLight.toggle();
    }
    if (buffer.equals("reboot"))
    {
        System.reset();
    }
    if (buffer.equals("sleep"))
    {
        sleepMode.sleep_mode_enabled = true;
        hmiScreen.sleep();
        notifLight.setStrip(0, 0, 0);
        lampLight.setLED(false);
        clock_control.sleep();
    }
    if (buffer.equals("wake"))
    {
        sleepMode.sleep_mode_enabled = false;
        hmiScreen.home();
        hmiScreen.wake();
        clock_control.wake();
    }
    if (buffer.equals("lock"))
    {
        lock();
    }
    if (buffer.equals("unlock"))
    {
        unlock();
    }
}

//put a comment here ASAP
String tryExtractString(String str, const char *start, const char *end)
{
    if (str == NULL)
    {
        return "";
    }

    int idx = str.indexOf(start);
    if (idx < 0)
    {
        return "";
    }

    int endIdx = str.indexOf(end);
    if (endIdx < 0)
    {
        return "";
    }

    return str.substring(idx + strlen(start), endIdx);
}

/*
function: particleToggleSleepMode()
description: toggles sleepMode in accordance to the particle cloud. 
parameters: none
returns: none
*/
void particleToggleSleepMode(const char *event, const char *data)
{
}

/*
function: particleToggleLED()
description: toggles LEDs in accordance to the particle cloud. 
parameters: none
returns: none
*/
void particleToggleLED(const char *event, const char *data)
{
}

/*
function: particlePrintTFT()
description: prints out texts to the TFT on accordance to the cloud. 
parameters: none
returns: none
*/
void particlePrintTFT(const char *event, const char *data)
{
}

/*
function: particleUpdateQR()
description: updates the QR code in accordance to the cloud pull function
parameters: none
returns: none
*/
void particleUpdateQR(const char *event, const char *data)
{
}

/*
function: pushNotification()
description: pushes a notification by printing to the tft led, and blinking the rgb leds :)
parameters:  *event, *data const char 
returns: none
*/
void push(const char *event, const char *data)
{
    if (!lockStatus.system_locked && !sleepMode.sleep_mode_enabled)
    {
        String buffer = data;
        tftDisplay.printTFT(buffer);
        hmiScreen.home();
        hmiScreen.homeText.setText(buffer);
        counter.stagger_push = true;
        alarm.beepOnce(300);
        clock_control.send_msg(buffer);
    }
    else if (lockStatus.system_locked & sleepMode.sleep_mode_enabled)
    {
        tftDisplay.printTFT("Message Receieved");
    }
}

/*
function: pushQuiet()
description: pushes a notification by printing to the tft led, and blinking the rgb leds :) But doens't beep the epper!
parameters:  *event, *data const char 
returns: none
*/
void pushQuiet(const char *event, const char *data)
{
}

/*
function: pushLoud()
description: pushes a notification by printing to the tft led, and blinking the rgb leds :) But beeps for 3 times as long :)))
parameters:  *event, *data const char 
returns: none
*/

void pushLoud(const char *event, const char *data)
{
}

/*
function: getWeatherData()
description: prints out weather data from another server. 
parameters: none
returns: none
*/
void getWeatherData(const char *event, const char *data)
{
}

/*
function: toggleLockDownMode()
description: toggles the LockDown boolean, so we can lock down the machine(or not!)
parameters: none
returns: none
*/
void toggleLockDownMode(const char *event, const char *data)
{
}

/*
function: sysReset()
description: cloud reqeusts the particle to reset, 
parameters: none
returns: none
*/
void sysReset(const char *event, const char *data)
{
    System.reset();
}