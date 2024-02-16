/*
  simple.ino

  Example sketch showcasing a simple menu in an easy way

  Author: Pontus Martinsson
  Created: 2024-02-15
  Last modified: 2024-02-16

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

#include <PotusOledMenu.h>

#define upPin 2
#define downPin 3

PotusOledMenu menu; // create instance of PotusOledMenu class

char* labels[] = { "Heart", "Play", "People", "Clock", "Arrow", "House" }; // pointer array with labels

// 16x16px .xbm bitmaps generated using convertio.co
const unsigned char heart [] PROGMEM = {
  0x00, 0x00, 0x3C, 0x1E, 0x42, 0x21, 0x81, 0x40, 0x01, 0x40, 0x01, 0x40, 
  0x01, 0x40, 0x01, 0x40, 0x02, 0x20, 0x04, 0x10, 0x08, 0x08, 0x10, 0x04, 
  0x20, 0x02, 0x40, 0x01, 0x80, 0x00, 0x00, 0x00, };

const unsigned char play [] PROGMEM = {
  0x00, 0x00, 0x06, 0x00, 0x1A, 0x00, 0x62, 0x00, 0x82, 0x01, 0x02, 0x06, 
  0x02, 0x18, 0x02, 0x60, 0x02, 0x80, 0x02, 0x60, 0x02, 0x18, 0x02, 0x06, 
  0x82, 0x01, 0x62, 0x00, 0x1A, 0x00, 0x06, 0x00, };

const unsigned char people [] PROGMEM = {
  0x00, 0x00, 0x38, 0x0E, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x38, 0x0E, 
  0x00, 0x00, 0x7C, 0x1F, 0x82, 0x20, 0x82, 0x20, 0x01, 0x41, 0x01, 0x41, 
  0x01, 0x41, 0x01, 0x41, 0x01, 0x41, 0x01, 0x41, };

const unsigned char clock [] PROGMEM = {
  0xE0, 0x07, 0x18, 0x18, 0x84, 0x20, 0x82, 0x40, 0x82, 0x40, 0x81, 0x80, 
  0x81, 0x80, 0x81, 0x80, 0x81, 0x87, 0x01, 0x80, 0x01, 0x80, 0x02, 0x40, 
  0x02, 0x40, 0x04, 0x20, 0x18, 0x18, 0xE0, 0x07, };

const unsigned char arrow [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x70, 0x00, 0x58, 0x00, 
  0xCC, 0x7F, 0x06, 0x40, 0xCC, 0x7F, 0x58, 0x00, 0x70, 0x00, 0x60, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

const unsigned char house [] PROGMEM = {
  0x00, 0x00, 0x80, 0x01, 0xC0, 0x03, 0xE0, 0x07, 0xF0, 0x0F, 0xF8, 0x1F, 
  0xFC, 0x3F, 0xFE, 0x7F, 0xFF, 0xFF, 0xF8, 0x1F, 0x38, 0x1C, 0x38, 0x1C, 
  0x38, 0x1C, 0x38, 0x1C, 0xF8, 0x1F, 0xF8, 0x1F, };

unsigned char* icons[] = { heart, play, people, clock, arrow, house }; // pointer array with bitmaps

void setup() {
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  
  menu.begin();

  // configure options
  // these do not have to be in setup(), but it is often convenient
  // all options are false by default
  menu.setSize(6); // this is the only required option
  menu.enableLabels(true);
  menu.enableIcons(true);
  menu.enableOutline(true);
  menu.enableScrollbar(true);
  menu.enableCenter(false); // entirely redundant since all options are false by default
  menu.enableBold(true);

  // these do not have to be in setup(), but it is often convenient
  menu.labels(labels); // set labels
  menu.icons(icons); // set icons
  menu.draw(); // display menu
}

void loop() {
  // read buttons and scroll menu accordingly
  if (digitalRead(upPin) == HIGH) {
    menu.up();
    delay(100);
  }
  else if (digitalRead(downPin) == HIGH) {
    menu.down();
    delay(100);
  }
}
