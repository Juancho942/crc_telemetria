#include <Arduino.h>
#include <sensor.h>
#include <Adafruit_LiquidCrystal.h>
#include "Wire.h"

sensor Sensor0(A0, 2000, " °C");
sensor Sensor1(A1, 2000, " °C");
sensor sensor2(A2, 2000, " cm");

// initialize the library with the numbers of the interface pins
Adafruit_LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{   Serial.begin(9600);
    // set up the LCD's number of rows and columns:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("hello, world!");
}

void loop()
{ 
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(1, 1);
    // print the number of seconds since reset:
    lcd.print(Sensor0.lecturaSensor());
    delay(1000);
}