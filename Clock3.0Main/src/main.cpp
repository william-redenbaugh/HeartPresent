#include <Arduino.h>

// OS RUNTIME // 
#include "OS/OSThreadKernel.h"
#include "OS/OSSignalKernel.h"
#include "OS/OSMutexKernel.h"

// LCD runtime thread. 
#include "lcd_display_runtime.hpp"

// BLE sense callback module
#include "ble_sense_coms.hpp"

// LED strip runtime thread
#include "led_strip_runtime.hpp"

// Dotmatrix runtime thread
#include "dotmatrix_runtime.hpp"

void setup() {
  os_init(); 

}

void loop() {
  os_thread_delay_s(1); 
}