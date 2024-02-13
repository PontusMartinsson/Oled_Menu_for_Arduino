#include "Oled_menu.h"
#include "Arduino.h"
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C _u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE); // create the oled display object

Oled_menu::Oled_menu() {}

void Oled_menu::begin() {
  _u8g2.begin();
  _u8g2.setBitmapMode(1);
  _u8g2.setColorIndex(1);
  _u8g2.setPowerSave(0);

  Serial.begin(9600);
}

void Oled_menu::size(int size) {
  _size = size - 1;
}

void Oled_menu::enableScrollbar(bool enable) {

}

void Oled_menu::enableIcons(bool enable) {

}

void Oled_menu::enableValues(bool enable) {

}


void Oled_menu::labels(char labelArray[][_labelSize]) {
  int tempSize = _size + 1;

  // free memory if _labels is already allocated
  if (_labels != nullptr) {
    for (int i = 0; i < tempSize; i++) {
      delete[] _labels[i];
    }
    delete[] _labels;
  }

  // allocate memory for _labels
  _labels = new char*[tempSize];
  for (int i = 0; i < tempSize; i++) {
    _labels[i] = new char[_labelSize];
  }

  // copy data from labelArray to _labels
  for (int i = 0; i < tempSize; i++) {
    for (int j = 0; j < _labelSize; j++) {
      _labels[i][j] = labelArray[i][j];
    }
  }
}

void Oled_menu::icons(const unsigned char* iconArray[]) {
  _icons = iconArray;
}

void Oled_menu::drawItem(int item, int itemY, uint16_t font) {
  const int _iconY = itemY - 13;
  _u8g2.setFont(font);

  _u8g2.drawXBMP(_iconX, _iconY, 16, 16, _icons[item]); // draw icon
  _u8g2.drawStr(_labelX, itemY, _labels[item]); // draw label
}

void Oled_menu::draw() { 
  _previous = (_selected + _size) % (_size + 1); // set _prev to one more than _selected and wrap if beyond the bounds of the menu
  _next = (_selected + 1) % (_size + 1); // set _next to one less than _selected and wrap if beyond the bounds of the menu

  _u8g2.clearBuffer();

  _u8g2.drawRFrame(0, 22, _outlineWidth, 21, 5);
  drawItem(_previous, _previousY, _regularFont);
  drawItem(_selected, _selectedY, _boldFont);
  drawItem(_next, _nextY, _regularFont);

  // draw scrollbar
  if (_enableScrollbar) {
    _u8g2.drawBox(125, 64/(_size + 1) * _selected, 3, 64/_size + 1); // draw handle

    // draw dotted line
    for (int y = 0; y <= 64; y++) {
      if (!(y % 3)) {
        _u8g2.drawPixel(126, y);
      }
    }
  }

  _u8g2.sendBuffer();
}

void Oled_menu::up() {
  _selected = (_selected + _size) % (_size + 1); // increment _selected and wrap if beyond the bounds of the menu
  draw();
}

void Oled_menu::down() {
  _selected = (_selected + 1) % (_size + 1); // decrement _selected and wrap if beyond the bounds of the menu
  draw();
}

void Oled_menu::jump(int item) {
  _selected = item;
  draw();
}

int Oled_menu::getSelected() {
  return _selected;
}
