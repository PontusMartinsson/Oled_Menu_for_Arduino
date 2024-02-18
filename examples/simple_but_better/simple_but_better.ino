/*
  simple_but_better.ino

  Example sketch showcasing a simple menu made in a more efficient way

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
#include "bitmaps.h"

#define upPin 2
#define downPin 3

PotusOledMenu menu; // create instance of PotusOledMenu class

char* labels[] = { "Heart", "Play", "People", "Clock", "Arrow", "House" }; // pointer array with labels
unsigned char* icons[] = { heart, play, people, clock, arrow, house }; // pointer array with bitmaps stored in bitmaps.h

bool buttonPressed = false;

void setup() {
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  
  menu.begin();
  // these do not have to be in setup(), but it is often convenient
  menu.config(6, true, true, true, true, false, true); // configure options
  menu.labels(labels); // set labels
  menu.icons(icons); // set icons
  menu.draw(); // display menu
}

// read buttons and scroll menu accordingly
void loop() {
  bool upPressed = digitalRead(upPin);
  bool downPressed = digitalRead(downPin);

  if (upPressed && !(buttonPressed)) { // up
    buttonPressed = true;
    menu.up();
  }
  else if (downPressed && !(buttonPressed)) { // down
    buttonPressed = true;
    menu.down();
  }
  else if (buttonPressed && !upPressed && !downPressed) { // reset buttonPressed when no button is pressed
    buttonPressed = false;
  }
}
