#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;
unsigned long counter = 0;
int interval = 6500;
int interval2 = 50;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;

SoftwareSerial BTserial(3, 4);  // Use pins D2 (RX) and D3 (TX) for SoftwareSerial on Arduino Nano

// Define the LCD settings
LiquidCrystal_I2C lcd(0x3F, 16, 2);  // Address 0x27 for a 16x2 display

void setup() {
  Serial.begin(9600);
  BTserial.begin(9600);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello & wlc to");
  // Display setup message
  lcd.setCursor(0, 1);
  lcd.print("Wireless stetho");
  BTserial.print("Wireless Stethoscope");
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long currentMillis2 = millis();

  if ((currentMillis2 - previousMillis2) >= interval2) { // Wait for interval2 ms before proceeding
    counter = 0;
    while ((currentMillis - previousMillis) < interval) { // Read the sensorvalue for (interval - interval2) ms
      sensorValue = analogRead(analogInPin);
      if (sensorValue > 130 && sensorValue < 250) {
        counter++;
      }
      currentMillis = millis();
    }
    previousMillis = currentMillis;  // End of reading time  // Multiples of interval
    previousMillis2 = currentMillis2;  // Start of reading time  // Multiples of (interval + interval2)

    // Print the counter value to Serial and Bluetooth
    Serial.print("BPM: ");
    Serial.println(counter);
    // Serial.print("Reading from: ");
    // Serial.println(previousMillis2 + interval2);
    // Serial.print("Reading till: ");
    // Serial.println(previousMillis);
    BTserial.print("BPM: ");
    BTserial.println(counter);
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("BPM: ");
    lcd.setCursor(0, 1);
    lcd.print("Getting data....");

    // Update the LCD display
    lcd.setCursor(5, 0);  // Set the cursor position to overwrite the BPM value
    lcd.print("          ");    // Clear previous BPM value
    lcd.setCursor(5, 0);  // Set the cursor back
    lcd.print(counter);   // Display the new BPM value
  }
}
