/*
  toggle_options.h

  Example sketch showcasing a simple options menu

  Author: Pontus Martinsson
  Created: 2024-02-16
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
#include "bitmaps.h"

#define optionNum 6 // number of options
#define upPin 2
#define downPin 3
#define selectPin 4

PotusOledMenu menu; // create instance of PotusOledMenu class

const char* labels[optionNum] = { "Labels", "Icons", "Outline", "Scrollbar", "Center", "Bold" }; // pointer array with labels
const unsigned char* icons[optionNum] = { label, icon, outline, scrollbar, center, bold }; // pointer array with bitmaps stored in bitmaps.h

bool options[optionNum] = { 1, 1, 1, 1, 1, 1 }; // array with option states, all true by default

void setup() {
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  pinMode(selectPin, INPUT);

  menu.begin();
  menu.config(optionNum, 1, 1, 1, 1, 1, 1);
  menu.labels(labels);
  menu.icons(icons);
  menu.draw();
}

// read buttons and apply changes accordingly
void loop() {
  if (digitalRead(upPin)) {
    menu.up();
    delay(100);
  }
  else if (digitalRead(downPin)) {
    menu.down();
    delay(100);
  }
  else if (digitalRead(selectPin)) {
    options[menu.getSelected()] = options[menu.getSelected()] ? 0 : 1; // toggle the selected option
    menu.config(optionNum, options[0], options[1], options[2], options[3], options[4], options[5]); // apply options
    menu.draw(); // refresh menu
  }
}
