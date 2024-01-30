#include "Arduino.h"
#include "Oled_menu.h"
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);
Oled_menu::Oled_menu() {}

void Oled_menu::begin() {
  u8g2.begin();
  u8g2.setBitmapMode(1);
  u8g2.setColorIndex(1);
  u8g2.setPowerSave(0);

  // Serial.begin(9600);
}

void Oled_menu::config(int size, bool enableIcons) {
  _size = size;
  _enableIcons = enableIcons;
}

void Oled_menu::icons(const unsigned char* iconArray[1]) {
  memcpy(_temp, iconArray, 1);

  const unsigned char _icons[1] PROGMEM = {_temp};
  
  u8g2.clearBuffer();
  u8g2.drawXBMP(30, 30, 16, 16, _icons);
  u8g2.setFont(_regularFont);
  u8g2.drawStr(10, 22, "SUG DASE");
  u8g2.sendBuffer();
}

void Oled_menu::labels(char labelArray[][_labelSize]) {
  memcpy(_labels, labelArray, _labelSize);
}
