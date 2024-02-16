/*
  scrolling_text.ino

  Example sketch showcasing auto scrolling text

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

/* 
DISCLAIMER: This is both a horrible way to achieve this and a horrible way to 
use this library. This was made purely to showcase how automatic scrolling and 
only showing certain elements could be used.
*/

#include "PotusOledMenu.h"

PotusOledMenu menu;

char* text[] = {
  "",
  "",
  "'My wife",
  "constantly",
  "reminds me of",
  "my drinking...",
  "But drinking",
  "is a job...",
  "for drunkman.'",
  "-Jouko aka. Pekka",
  ""
}; 

void setup() {
  menu.begin();
  menu.setSize(11);
  menu.enableLabels(true);
  menu.enableCenter(true);
  menu.labels(text);
  menu.draw();
}

void loop() {
  delay(2000);
  menu.down();
}
