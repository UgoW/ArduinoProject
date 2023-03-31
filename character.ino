byte leftBlock[8] = {
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
  B00011
};

byte midBlock[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte rightBlock[8] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100
};

byte upHead[8] = {
  B01100,
  B01100,
  B00000,
  B11110,
  B01101,
  B11111,
  B10000,
  B00000
};

byte upNoHead[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte headOnly[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B01100,
  B01100,
  B00000
};

byte walk1[8] = {
  B01100,
  B01100,
  B00000,
  B01110,
  B11100,
  B01100,
  B11010,
  B10011
};

byte walk2[8] = {
  B01100,
  B01100,
  B00000,
  B01100,
  B01100,
  B01100,
  B01100,
  B01110
};

#include <LiquidCrystal.h>
LiquidCrystal lcd(15, 14, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  lcd.createChar(byte(0), walk1);
  lcd.createChar(byte(1), walk2);
}


void loop() {
  lcd.setCursor(0,0);
  
  lcd.write(byte(1));
  delay(300);

  lcd.setCursor(0,0);
  lcd.write(byte(0));
  delay(300);
}
