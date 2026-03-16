#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int pirPin = 7;
int ledPin = 8;

unsigned long startTime = 0;
unsigned long totalTime = 0;

void setup()
{
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Energy System");
  lcd.setCursor(0,1);
  lcd.print("Starting...");
  
  delay(2000);
  lcd.clear();
}

void loop()
{
  int motion = digitalRead(pirPin);

  if(motion == HIGH)
  {
    digitalWrite(ledPin, HIGH);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Motion Detect");
    lcd.setCursor(0,1);
    lcd.print("Light ON");

    startTime = millis();
  }

  else
  {
    digitalWrite(ledPin, LOW);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("No Motion");
    lcd.setCursor(0,1);
    lcd.print("Light OFF");

    totalTime = totalTime + (millis() - startTime);
  }

  float hours = totalTime / 3600000.0;
  float energy = hours * 10; 

  lcd.setCursor(0,0);
  lcd.print("Energy:");
  lcd.print(energy);
  lcd.print("Wh");

  lcd.setCursor(0,1);
  lcd.print("Time:");
  lcd.print(hours);
  lcd.print("h");

  delay(1000);
}
