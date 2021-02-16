/*
*  BT module     Arduino mega
*   VCC             5V
*   GND             GND
*   TX              RX3 (digital pin 14)
*   RX              TX3 (digital pin 15)
*    
*   Use bluetooth terminal app for android, choose"Connect a device - Insecure"
*   select the HC-05 BT module
*   open the Arduino serial monitor, select 9600 baud and both NL and CR
*/
void setup() 
{
  Serial.begin(9600);   // open the serial port
  Serial3.begin(9600);  // open the bluetooth serial port, we use serial3 because we plug our module to TX3 and RX3 but
                        // we can use serial 1 or 2 however not 0 since it is used for the arduino serial monitor communication
}

void loop() 
{
  // send from serial to bluetooth
  if(Serial3.available()){
    Serial.println(Serial3.readString()); 
  }

  // send from bluetooth to serial
  if(Serial.available()){
    Serial3.println(Serial.readString()); 
  }
}
