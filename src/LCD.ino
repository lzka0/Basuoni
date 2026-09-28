#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

void Welcome()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("BASUONI");
lcd.setCursor(0,1);
lcd.print("Welcome");
}


void Manual()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("BASUONI");
lcd.setCursor(0,1);
lcd.print("Mode : Manual");
}



void Automatic()
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("BASUONI");
lcd.setCursor(0,1);
lcd.print("Mode : Automatic");
}


void Calibration() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BASUONI");
  lcd.setCursor(0, 1);
  lcd.print("Mode : Calibration");
}