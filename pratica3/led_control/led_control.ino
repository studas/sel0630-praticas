#include <Wire.h>

const int LED_PIN = 13; // Built-in LED on most Arduino boards
const byte I2C_ADDRESS = 0x09; // Slave address (can be any valid 7-bit address)

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Initialize LED to OFF

  Wire.begin(I2C_ADDRESS); // Initialize I2C as slave
  Wire.onReceive(receiveEvent); // Register event
  Serial.begin(9600); // Optionqal: For debugging
  Serial.println("Arduino I2C Slave Initialized");
}

void loop() {
  // Nothing needed here; actions are handled in receiveEvent
}

void receiveEvent(int howMany) {
  if (Wire.available()) {
    byte command = Wire.read();
    Serial.print("Received command: ");
    Serial.println(command);

    if (command == '1') {
      digitalWrite(LED_PIN, HIGH); // Turn LED ON
      Serial.println("LED turned ON");
    }
    else if (command == '0') {
      digitalWrite(LED_PIN, LOW); // Turn LED OFF
      Serial.println("LED turned OFF");
    }
    else {
      Serial.println("Unknown command");
    }
  }
}