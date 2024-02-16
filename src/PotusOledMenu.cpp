/*
  PotusOledMenu.cpp

  Arduino specific functions

  Author: Pontus Martinsson
  Created: 2024-01-30
  Last modified: 2024-02-15

  For more information, visit: https://github.com/Pontana22/PotusOledMenu

  License: MIT License

  Copyright (c) 2024 Pontus Martinsson

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "PotusOledMenu.h"
#include "Arduino.h"
#include <U8g2lib.h>

#define _labelSize 18

U8G2_SSD1306_128X64_NONAME_F_SW_I2C _u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

PotusOledMenu::PotusOledMenu() {}

void PotusOledMenu::begin() {
  _u8g2.begin();
  _u8g2.setBitmapMode(1);
  _u8g2.setColorIndex(1);
  _u8g2.setPowerSave(0);
}

void PotusOledMenu::setSize(int size) {
  _size = size - 1;
}

void PotusOledMenu::enableLabels(bool enable) {
  _enableLabels = enable;
}

void PotusOledMenu::enableIcons(bool enable) {
  _enableIcons = enable;
  _labelXMin = enable ? 25 : 6;
}

void PotusOledMenu::enableOutline(bool enable) {
  _enableOutline = enable;
}

void PotusOledMenu::enableScrollbar(bool enable) {
  _enableScrollbar = enable;
  _outlineWidth = enable ? 120 : 128;
  _labelXMax = enable ? 115 : 123;
}

void PotusOledMenu::enableCenter(bool enable) {
  _enableCenter = enable;
}

void PotusOledMenu::enableBold(bool enable) {
  _enableBold = enable;
}

void PotusOledMenu::config(int size, bool labels, bool icons, bool outline, bool scrollbar, bool center, bool bold) {
  setSize(size);
  enableLabels(labels);
  enableIcons(icons);
  enableOutline(outline);
  enableScrollbar(scrollbar);
  enableCenter(center);
  enableBold(bold);
}

void PotusOledMenu::labels(char* labelArray[]) {
  int arraySize = 0;

  // calculate first dimension of labelArray
  while (labelArray[arraySize] != nullptr) {
    arraySize++;
  }

  // free memory if _labels is already allocated
  if (_labels != nullptr) {
    for (int i = 0; i < arraySize; i++) {
      delete[] _labels[i];
    }
    delete[] _labels;
  }

  _labels = new char*[arraySize]; // allocate memory for _labels
  for (int i = 0; i < arraySize; i++) {
    int labelSize = strlen(labelArray[i]) + 1; // setermine the size of the current string
    _labels[i] = new char[labelSize]; // allocate memory for the current label
    strcpy(_labels[i], labelArray[i]); // copy the string
  }
}

void PotusOledMenu::setLabel(int item, const char* label) {
  strncpy(_labels[item], label, _labelSize - 1);
}

void PotusOledMenu::icons(const unsigned char* iconArray[]) {
  _icons = iconArray;
}

void PotusOledMenu::setIcon(int item, const unsigned char* icon) {
  _icons[item] = icon;
}

void PotusOledMenu::drawItem(byte item, byte itemY) {
  const byte _iconX = 4;
  const byte _iconY = itemY - 13;
  _u8g2.setFont((_enableBold && item == _selected) ? u8g2_font_7x13B_mf : u8g2_font_7x13_mf); // set the correct font

  // calculate starting x coordinate for the label
  int labelX;
  if (_enableCenter) { labelX = (_labelXMax - _labelXMin) / 2 + _labelXMin - _u8g2.getStrWidth(_labels[item]) / 2; } 
  else { labelX = _labelXMin; }

  if (_enableIcons) { _u8g2.drawXBMP(_iconX, _iconY, 16, 16, _icons[item]); } // draw icon
  if (_enableLabels) { _u8g2.drawStr(labelX, itemY, _labels[item]); } // draw label
}

void PotusOledMenu::draw() { 
  const byte _previousY = 15;
  const byte _selectedY = 37;
  const byte _nextY = 59;

  byte _previous = (_selected + _size) % (_size + 1); // set _prev to one more than _selected and wrap if beyond the bounds of the menu
  byte _next = (_selected + 1) % (_size + 1); // set _next to one less than _selected and wrap if beyond the bounds of the menu

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

void PotusOledMenu::up() {
  _selected = (_selected + _size) % (_size + 1); // increment _selected and wrap if beyond the bounds of the menu
  draw();
}

void PotusOledMenu::down() {
  _selected = (_selected + 1) % (_size + 1); // decrement _selected and wrap if beyond the bounds of the menu
  draw();
}

void PotusOledMenu::jump(int item) {
  _selected = item;
  draw();
}

int PotusOledMenu::getSelected() {
  return _selected;
}
