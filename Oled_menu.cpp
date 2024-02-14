#include "Oled_menu.h"
#include "Arduino.h"
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C _u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

Oled_menu::Oled_menu() {}

void Oled_menu::begin() {
  _u8g2.begin();
  _u8g2.setBitmapMode(1);
  _u8g2.setColorIndex(1);
  _u8g2.setPowerSave(0);

  Serial.begin(9600);
}

void Oled_menu::setSize(int size) {
  _size = size - 1;
}

void Oled_menu::enableLabels(bool enable) {
  _enableLabels = enable;
}

void Oled_menu::enableOutline(bool enable) {
  _enableOutline = enable;
}

void Oled_menu::enableScrollbar(bool enable) {
  _enableScrollbar = enable;
  _outlineWidth = enable ? 120 : 128;
  _labelXMax = enable ? 115 : 123;
}

void Oled_menu::enableIcons(bool enable) {
  _enableIcons = enable;
  _labelXMin = enable ? 25 : 6;
}

void Oled_menu::enableCenter(bool enable) {
  _enableCenter = enable;
}

void Oled_menu::enableBold(bool enable) {
  _enableBold = enable;
}

void Oled_menu::config(int size, bool labels, bool outline, bool scrollbar, bool icons, bool center, bool bold) {
  setSize(size);
  enableLabels(labels);
  enableOutline(outline);
  enableScrollbar(scrollbar);
  enableIcons(icons);
  enableCenter(center);
  enableBold(bold);
}
void Oled_menu::labels(char labelArray[][_labelSize]) {
  int arraySize = 0;

  // calculate first dimension of labelArray
  while (labelArray[arraySize][0] != '\0') {
    arraySize++;
  }

  // free memory if _labels is already allocated
  if (_labels != nullptr) {
    for (int i = 0; i < arraySize; i++) {
      delete[] _labels[i];
    }
    delete[] _labels;
  }

  // allocate memory for _labels
  _labels = new char*[arraySize];
  for (int i = 0; i < arraySize; i++) {
    _labels[i] = new char[_labelSize];
  }

  // copy data from labelArray to _labels
  for (int i = 0; i < arraySize; i++) {
    for (int j = 0; j < _labelSize; j++) {
      _labels[i][j] = labelArray[i][j];
    }
  }
}

void Oled_menu::setLabel(int item, const char* label) {
  strncpy(_labels[item], label, _labelSize - 1);
}

void Oled_menu::icons(const unsigned char* iconArray[]) {
  _icons = iconArray;
}

void Oled_menu::setIcon(int item, const unsigned char* icon) {
  _icons[item] = icon;
}

void Oled_menu::drawItem(int item, int itemY) {
  const int _iconY = itemY - 13;
  _u8g2.setFont((_enableBold && item == _selected) ? _boldFont : _regularFont); // set the correct font

  // calculate starting x coordinate for the label
  int labelX;
  if (_enableCenter) { labelX = (_labelXMax - _labelXMin) / 2 + _labelXMin - _u8g2.getStrWidth(_labels[item]) / 2; } 
  else { labelX = _labelXMin; }

  if (_enableIcons) { _u8g2.drawXBMP(_iconX, _iconY, 16, 16, _icons[item]); } // draw icon
  if (_enableLabels) { _u8g2.drawStr(labelX, itemY, _labels[item]); } // draw label
}

void Oled_menu::draw() { 
  _previous = (_selected + _size) % (_size + 1); // set _prev to one more than _selected and wrap if beyond the bounds of the menu
  _next = (_selected + 1) % (_size + 1); // set _next to one less than _selected and wrap if beyond the bounds of the menu

  _u8g2.clearBuffer();

  if (_enableOutline) { _u8g2.drawRFrame(0, 22, _outlineWidth, 21, 5); } // draw selection outline

  drawItem(_previous, _previousY);
  drawItem(_selected, _selectedY);
  drawItem(_next, _nextY);

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
