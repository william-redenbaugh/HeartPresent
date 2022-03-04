# HeartPresent

A Particle.io project that contains the code for my girlfriend's heart present I made a couple years ago. The code was recently updated, with new features added. 

## Libraries Used: 
-Neopixel(for controlling the status lights)
-Adafruit_LIS3DH(drivers for the accelerometer/gyro inside the heart, currently not used for anything)
-Adafruit_ILI9341(drivers for the secondary display on the heart)
-ITEADLIB_Nextion(drivers for interfacing with the hmi/main display on the heart, I plan on writing my own since their drivers kinda suck)
-MFRC522(drivers for the rfid module on board)

## Current Functions: 
### Used as a lamp
I can currently remote control the bright LED lamp strip, and we use it as a normal lap 
### Authentication
RFID module allows us to lock down the heart at any time 
### Pictures
Cute pictures in the HMI allow the heart to double as a picture frame 
### Clock
Tells the time 
### Remote Control of "Clock Present" 
It sends basic UDP messages to another present I made for my girlfriend since that present doesn't have cloud integration. This allows both presents to react to cloud stimuli 
### Cute light animations
LED ring animations different colors. 
###
