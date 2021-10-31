/*
 * Fat_Lurch - 2021-10-29
 * 
 * Updated - 2021-10-30: Added handling to control characters so they are not displayed
 * 
 * This is a very simple sketch that will display a single line of text (only) on a standard 16x2 LCD I2C display
 * 
 * Based on the original example from johnrickman: https://github.com/johnrickman/LiquidCrystal_I2C/blob/master/examples/SerialDisplay/SerialDisplay.pde
 * 
 * To send data to the display in the Arduino IDE, press ctrl+shift+m then set "No Line Ending" and ensure the data rate is 9600
 * 
 * Then just type into the command line at the top and hit enter. The text should appear on the display
 * 
 */

#include <LiquidCrystal_I2C.h> //LiquidCrystal I2C by Frank de Brabander - https://www.arduino.cc/reference/en/libraries/liquidcrystal-i2c/

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 (default) for a 16 chars and 2 line display

char charBuf;

void setup()
{
  lcd.init();               // initialize the LCD
  lcd.backlight();          //Turn on LCD backlight
  Serial.begin(9600);
}

void loop()
{
  // when characters arrive over the serial port...
  if (Serial.available()) 
  {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) 
    {
      // Read the character to a buffer
      charBuf = char(Serial.read());
      
      // Skip control characters like \r and \n (aka CR and LF)
      if (!isControl(charBuf)) 
      {
        lcd.write(charBuf);
      }
    }
  }
}
