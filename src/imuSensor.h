#ifndef _IMUSENSOR_H
#define _IMUSENSOR_H

#include "Particle.h"
#include <Adafruit_LIS3DH.h>


class IMUSensor{
    public: 
    /*
    function: setupAccel()
    description: initializes accelerometer sensor on the i2c bus. 
    parameters: none
    returns: none
    */
    void setupAccel(void);
    
    /*
    function: readAccel()
    description: reads accelerometer data, and puts into a sensor read object
    parameters: none
    returns: none
    */
    void readAccel(void);
    
    /*
    function: readAccel()
    description: reads accelerometer data, and puts into a sensor read object
    parameters: none
    returns: none
    */
    int readAccelF(String Command);
    
    /*
    function: xAccel()
    description: returns x acceleration data.
    parameters: none
    returns: float(x.acceleration)
    */
    float xAccel(void);
    
    /*
    function: yAccel()
    description: returns y acceleration data.
    parameters: none
    returns: float(y.acceleration)
    */
    float yAccel(void);
    
    /*
    function: zAccel()
    description: returns z acceleration data.
    parameters: none
    returns: float(z.acceleration)
    */
    float zAccel(void);
    
    /*
    function: xAccelInt()
    description: returns x acceleration data.
    parameters: none
    returns: Int(x.acceleration)
    */
    int xAccelInt(String command);
    
    /*
    function: yAccelInt()
    description: returns y acceleration data.
    parameters: none
    returns: int(x.acceleration)
    */
    int yAccelInt(String command);
    
    /*
    function: zAccelInt()
    description: returns z acceleration data.
    parameters: none
    returns: int(x.acceleration)
    */
    int zAccelInt(String command);
    
    /*
    function: pushAccelData()
    description: pushes the accelerometer data to the particle cloud when requested. 
    parameters: none
    returns: float(x.acceleration)
    */
    void pushAccelData(const char *event, const char *data);
    
    private: 
        // Sensor "object" and event buffer for capturing data off IMU. 
        Adafruit_LIS3DH lis = Adafruit_LIS3DH();
        sensors_event_t eventBuff; 
};

#endif 