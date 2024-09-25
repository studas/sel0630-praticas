#include <Wire.h>

const byte I2C_ADDRESS = 0x09;

void setup() {
  Wire.begin(I2C_ADDRESS);
  Wire.onRequest(requestEvent); // Register a callback for when data is requested
  Serial.begin(9600); // Optional: For debugging
  Serial.println("Arduino I2C Slave Initialized for Potentiometer Reading");
}

void loop(){

}

void requestEvent() {
  int potValue = analogRead(A0); 
  
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);
  
  // Convert the integer to two bytes (MSB first)
  byte highByte = (potValue >> 8) & 0xFF;
  byte lowByte = potValue & 0xFF;
  
  Wire.write(highByte);
  Wire.write(lowByte);
}
