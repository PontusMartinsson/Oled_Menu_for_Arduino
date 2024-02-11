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

  Serial.begin(9600);
}

void Oled_menu::config(int size, bool enableIcons) {
  _size = size;
  _enableIcons = enableIcons;
}

// void Oled_menu::icons(const unsigned char* iconArray[1]) {
//   memcpy(_temp, iconArray, 1);

//   const unsigned char _icons[1] PROGMEM = {_temp};

//   u8g2.clearBuffer();
//   u8g2.drawXBMP(30, 30, 16, 16, _icons);
//   u8g2.setFont(_regularFont);
//   u8g2.drawStr(10, 22, "SUG DASE");
//   u8g2.sendBuffer();
// }

// void Oled_menu::labels(char labelArray[][_labelSize]) {
//   for(int i = 0; i <= sizeof(labelArray); i++) {
//     for(int j = 0; j < _labelSize; j++) {
//       _labels[i][j] = labelArray[i][j];
//     }
//   }
// }

void Oled_menu::labels(char labelArray[][_labelSize]) {
  _size = (sizeof(labelArray) + 1);

  // free memory if _labels is already allocated
  if (_labels != nullptr) {
    for (int i = 0; i < _size; i++) {
      delete[] _labels[i];
    }
    delete[] _labels;
  }

  // allocate memory for _labels
  _labels = new char*[_size];
  for (int i = 0; i < _size; i++) {
    _labels[i] = new char[_labelSize];
  }

  // copy data from labelArray to _labels
  for (int i = 0; i < _size; i++) {
    for (int j = 0; j < _labelSize; j++) {
      _labels[i][j] = labelArray[i][j];
    }
  }

  Serial.println(_size);
}

void Oled_menu::drawItem(int item, int itemY, uint16_t font) {
  const int _iconY = itemY - 13;
  u8g2.setFont(font);

  u8g2.drawStr(_labelX, itemY, _labels[2]);
}

void Oled_menu::draw() {
  u8g2.clearBuffer();
  drawItem(_previous, _previousY, _regularFont);
  drawItem(_selected, _selectedY, _boldFont);
  drawItem(_next, _nextY, _regularFont);
  u8g2.sendBuffer();
}

void Oled_menu::up() {

}