#include <SoftwareSerial.h>

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;
unsigned long counter = 0;
int interval = 3000;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;  // Added declaration for previousMillis2

SoftwareSerial BTserial(3, 4); // RX | TX

void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long currentMillis2 = millis();

  if ((currentMillis2 - previousMillis2) >= interval)
  {
    while ((currentMillis - previousMillis) < interval)
    {
      sensorValue = analogRead(analogInPin);
      if (sensorValue > 130 && sensorValue < 250)
      {
        counter++;
      }
      currentMillis = millis();  // Updated currentMillis inside the loop
    }
    previousMillis = currentMillis;
    previousMillis2 = currentMillis2;
    Serial.println(counter);
    BTserial.write(counter);
  }
}
