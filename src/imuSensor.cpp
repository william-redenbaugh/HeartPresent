#include "imuSensor.h"

/*
function: setupAccel()
description: initializes accelerometer sensor on the i2c bus. 
parameters: none
returns: none
*/
void IMUSensor::setupAccel(void){
    if (! this->lis.begin(0x18))
        System.reset();
        // If the accelerometer doesn't sync, then the system resets!
    
    // Sets default listening modes.     
    this->lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
    delay(20);
}

/*
function: readAccel()
description: reads accelerometer data, and puts into a sensor read object
parameters: none
returns: none
*/
void IMUSensor::readAccel(void){
    this->lis.read();     
    this->lis.getEvent(&eventBuff);
}

/*
function: readAccel()
description: reads accelerometer data, and puts into a sensor read object
parameters: none
returns: none
*/
int IMUSensor::readAccelF(String Command){
    this->lis.read();     
    this->lis.getEvent(&this->eventBuff);
    return 1; 
}

/*
function: xAccel()
description: returns x acceleration data.
parameters: none
returns: float(x.acceleration)
*/
float IMUSensor::xAccel(void){
    return this->eventBuff.acceleration.x;
}

/*
function: yAccel()
description: returns y acceleration data.
parameters: none
returns: float(y.acceleration)
*/
float IMUSensor::yAccel(void){
    return this->eventBuff.acceleration.y;
}

/*
function: zAccel()
description: returns z acceleration data.
parameters: none
returns: float(z.acceleration)
*/
float IMUSensor::zAccel(void){
    return this->eventBuff.acceleration.z;
}

/*
function: xAccelInt()
description: returns x acceleration data.
parameters: none
returns: Int(x.acceleration)
*/
int IMUSensor::xAccelInt(String command){
    this->lis.read();     
    this->lis.getEvent(&this->eventBuff);
    return int(this->eventBuff.acceleration.x * 1000);
}

/*
function: yAccelInt()
description: returns y acceleration data.
parameters: none
returns: int(x.acceleration)
*/
int IMUSensor::yAccelInt(String command){
    this->lis.read();     
    this->lis.getEvent(&this->eventBuff);
    return int(this->eventBuff.acceleration.y * 1000);
}

/*
function: zAccelInt()
description: returns z acceleration data.
parameters: none
returns: int(x.acceleration)
*/
int IMUSensor::zAccelInt(String command){
    this->lis.read();     
    this->lis.getEvent(&this->eventBuff);
    return int(this->eventBuff.acceleration.z * 1000);
}

/*
function: pushAccelData()
description: pushes the accelerometer data to the particle cloud when requested. 
parameters: none
returns: float(x.acceleration)
*/
void IMUSensor::pushAccelData(const char *event, const char *data){
    this->readAccel();
    String str = String(this->xAccel()) + " " + String(this->yAccel()) + " " + String(this->zAccel());
    delay(40);
    Particle.publish("Accel Data", str);
}