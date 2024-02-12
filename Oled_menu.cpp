#include "Oled_menu.h"
#include "Arduino.h"
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C _u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

Oled_menu::Oled_menu() {}

void Oled_menu::begin(int size, bool enableIcons) {
  _size = size - 1;
  _enableIcons = enableIcons;
  
  _u8g2.begin();
  _u8g2.setBitmapMode(1);
  _u8g2.setColorIndex(1);
  _u8g2.setPowerSave(0);

  Serial.begin(9600);
}

void Oled_menu::icons(const unsigned char* iconArray) {
  _icons = iconArray;
}

void Oled_menu::labels(char labelArray[][_labelSize]) {
  // int tempSize = _size + 1;

  // Serial.println(_size);

  // free memory if _labels is already allocated
  if (_labels != nullptr) {
    for (int i = 0; i <= _size; i++) {
      delete[] _labels[i];
    }
    delete[] _labels;
  }

  // allocate memory for _labels
  _labels = new char*[_size + 1];
  for (int i = 0; i <= _size; i++) {
    _labels[i] = new char[_labelSize];
  }

  // copy data from labelArray to _labels
  for (int i = 0; i <= _size; i++) {
    for (int j = 0; j < _labelSize; j++) {
      _labels[i][j] = labelArray[i][j];
    }
  }
  Serial.println(_labels[0]);
  Serial.println(_labels[1]);
  Serial.println(_labels[2]);
  Serial.println(_labels[3]);
  Serial.println(_labels[4]);
}

void Oled_menu::drawItem(int item, int itemY, uint16_t font) {
  const int _iconY = itemY - 13;
  _u8g2.setFont(font);


  // _u8g2.drawXBMP(0, itemY, 128, 21, _icons[0]);
  _u8g2.drawStr(_labelX, itemY, _labels[item]);
}

void Oled_menu::draw() { 
  _previous = _selected - 1;
  _next = _selected + 1;
  
  if (_previous < 0) {
    _previous = _size;
  } 
  else if (_previous > _size) {
    _previous = 0;
  }

  if (_next < 0) {
    _next = _size;
  } 
  else if (_next > _size) {
    _next = 0;
  }

  _u8g2.clearBuffer();
  _u8g2.drawXBMP(0, 22, 128, 21, _icons[0]);

  drawItem(_previous, _previousY, _regularFont);
  drawItem(_selected, _selectedY, _boldFont);
  drawItem(_next, _nextY, _regularFont);

  _u8g2.sendBuffer();
}

void Oled_menu::up() {
  _selected--;
  
  if (_selected < 0) {
    _selected = _size;
  } 

  draw();
}

void Oled_menu::down() {
  _selected++;

  if (_selected > _size) {
    _selected = 0;
  }

  draw();
}
