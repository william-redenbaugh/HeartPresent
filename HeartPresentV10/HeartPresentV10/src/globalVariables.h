#ifndef _GLOBALVARIABLES_H
#define _GLOBALVARIABLES_H

/*
Used for dealing with Counting and timer intervals. 
*/
struct Counters{
    volatile uint16_t loop_tick = 0;     
    volatile unsigned long ms_per_tick = 0; 
    volatile unsigned long current_ms = 0; 
    
    // Used so that when a push notification shows us, we push off updating the clock and other stuff
    // to the next interval. 
    volatile bool stagger_push = false; 
};

/*
Used for dealing with sleep mode. Any variables involving SleepMode will be found here 
*/ 
struct SleepMode{
    volatile bool sleep_mode_enabled = false; 
};

/*
Handling Locking Variables
*/
struct LockStatus{
    //volatile bool system_locked = true; 
    volatile bool system_locked = false; 
};

/*
Handling varibles dealing with notifications.
*/
struct NotificationSettings{
    volatile bool enabled = true; 
};

/*
Handling variables involving scrowling through pictures. 
*/
struct PictureSettings{
    volatile bool enabled = false; 
    volatile uint16_t pictures = false; 
};

#endif 