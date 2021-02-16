
#include <Wire.h>                                 // Library for I2C protocol
#include "Adafruit_VL53L0X.h"                     // Library for the ToF (Time of Flight) sensor
Adafruit_VL53L0X    tof = Adafruit_VL53L0X();     // Declaring an object to use the Tof sensor library

void setup() {
  Serial.begin(115200);                           // Open serial port, set data rate at 115200 bits/sec
  if (!tof.begin()){                              // Check if the Time of Flight sensor is present
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
}

void loop() {
Serial.print("Distance (mm): "); 
VL53L0X_RangingMeasurementData_t measure;
Serial.println(measure.RangeMilliMeter);          // Convert the distance in mm
delay(1000);
}
