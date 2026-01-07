#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Setup LCD address (typically 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int entrySensor = 2;
const int exitSensor = 3;
const int totalSlots = 4;
int availableSlots = totalSlots;

Servo gate;

const int gatePin = 9;

void setup() {
  pinMode(entrySensor, INPUT);
  pinMode(exitSensor, INPUT);
  
  gate.attach(gatePin);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Welcome");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Arduino Project");
  delay(2000);
  lcd.clear();
  lcd.print("Smart Parking");
  delay(2000);
  lcd.clear();

  updateLCD();
}

void loop() {
  if (digitalRead(entrySensor) == LOW && availableSlots > 0) {
    openGate();
    lcd.clear();
    lcd.print("Vehicle Entered");
    delay(1000);
    availableSlots--;
    updateLCD();
    waitUntilClear(entrySensor);
  }

  if (digitalRead(exitSensor) == LOW && availableSlots < totalSlots) {
    openGate();
    lcd.clear();
    lcd.print("Vehicle Exited");
    delay(1000);
    availableSlots++;
    updateLCD();
    waitUntilClear(exitSensor);
  }
}

void openGate() {
  gate.write(90); // Open position
  delay(2000);
  gate.write(0); // Close position
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Available Slots:");
  lcd.setCursor(0, 1);
  lcd.print(availableSlots);
  delay(2000);
}

void waitUntilClear(int sensorPin) {
  // Wait until object is no longer detected
  while (digitalRead(sensorPin) == LOW) {
    delay(100);
  }
}