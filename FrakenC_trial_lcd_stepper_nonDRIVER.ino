//declare variables and etc for liquid display
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x3F
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

LiquidCrystal_I2C lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

//declare variables for the motor pins
int motorPin1 = 8;    // Blue   - 28BYJ48 pin 1
int motorPin2 = 9;    // Pink   - 28BYJ48 pin 2
int motorPin3 = 10;    // Yellow - 28BYJ48 pin 3
int motorPin4 = 11;    // Orange - 28BYJ48 pin 4
// Red    - 28BYJ48 pin 5 (VCC)
int lcdCount = 0;

int motorSpeed = 1200;  //variable to set stepper speed
int count = 0;          // count of steps made
int countsperrev = 512; // number of steps per full revolution
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

//button information BUTTON LOCATION
int buttonState = 0;
int trigger = 0;
const int buttonPin = 2;

//////////////////////////////////////////////////////////////////////////////
void setup() {
  //declare the motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(9600);

  //declare lcd
  lcd.begin (20, 4, LCD_5x8DOTS);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);

  //declare button
  pinMode(buttonPin, INPUT);
}

//////////////////////////////////////////////////////////////////////////////
void loop() {
  /*
    if(count < countsperrev )
      clockwise();
    else if (count == countsperrev * 2)
      count = 0;
    else
  */
  //Setting LCD information
  lcd.setBacklight(HIGH);
  lcd.home ();

  //Setting button information
  buttonState = digitalRead(buttonPin);
  Serial.print("Button state: ");
  Serial.println(buttonState);
  if (buttonState == HIGH) {
    trigger++;
    Serial.println("Countdown starting...:");
  }
  if (trigger == 0) {
    lcd.print("Waiting for button  press...");
  }


  //Countdown:
  if (lcdCount == 0 && trigger >= 1) {
    lcd.clear();
    Serial.println(trigger);
    for (int i = 0; i <= 10; i++) {
      if (i >= 0 && i <= 5) {
        lcd.print(10 - i);
        delay(1000);
        lcd.clear();
      }
      else if (i >= 6 && i < 10) {
        lcd.print(10 - i);
        lcd.print(" Motor start");
        anticlockwise();
        delay(100);
        Serial.println(i);
        anticlockwise();
        delay(100);
        Serial.println(i);
        anticlockwise();
        delay(100);
        Serial.println(i);
        anticlockwise();
        delay(100);
        Serial.println(i);
        anticlockwise();
        delay(100);
        Serial.println(i);
        anticlockwise();
        delay(100);
        Serial.println(i);
        anticlockwise();
        delay(100);
        Serial.println(i);
        anticlockwise();
        delay(100);
        Serial.println(i);
        anticlockwise();
        delay(100);
        Serial.println(i);
        anticlockwise();
        delay(100);
        Serial.println(i);
        anticlockwise();
        delay(100);
        Serial.println(i);
        anticlockwise();
        lcd.clear();
      }

    }

    lcd.clear();
    lcd.print("Loop Complete       Launching...");
    lcdCount++;
    for (int i = 0; i < 1000000; i++) {
      anticlockwise();
    }
  }


}

//////////////////////////////////////////////////////////////////////////////
//set pins to ULN2003 high in sequence from 1 to 4
//delay "motorSpeed" between each pin setting (to determine speed)

void anticlockwise()
{
  for (int i = 0; i < 8; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void clockwise()
{
  for (int i = 7; i >= 0; i--)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void setOutput(int out)
{
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}
