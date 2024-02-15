/*
  PotusOledMenu.h

  C++ Arduino wrapper for the PotusOledMenu struct and c functions for the PotusOledMenu library

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

#ifndef PotusOledMenu_h
#define PotusOledMenu_h

#include "Arduino.h"
#include <U8g2lib.h>

class PotusOledMenu {
  public:
    PotusOledMenu();
    void begin();

    // Set the number of menu items
    void setSize(int size);
    // Enable/disable labels
    void enableLabels(bool enable);
    // Enable/disable selection outline
    void enableOutline(bool enable);
    // Enable/disable scrollbar
    void enableScrollbar(bool enable);
    // Enable/disable icons
    void enableIcons(bool enable);
    // Enable/disable values
    void enableValues(bool enable);
    // Enable/disable label centering
    void enableCenter(bool enable);
    // Enable/disable bold text on selected item
    void enableBold(bool enable);
    // Configure all options
    void config(int size, bool labels, bool icons, bool outline, bool scrollbar, bool center, bool bold);

    // Specify all labels
    void labels(char labelArray[][18]); 
    // Specify label, requires labels() to have been set
    void setLabel(int item, const char* label);
    // Specify all icons
    void icons(const unsigned char* iconArray[]);
    // Specify icon, requires icons() to have been set
    void setIcon(int item, const unsigned char* icon);

    // Draw the menu
    void draw();
    // Scroll upwards
    void up();
    // Scroll downwards
    void down();
    // Jump to specific item, first item is 0
    void jump(int item);
    // Returns the currently selected item
    int getSelected();

  private:
    void drawItem(byte item, byte itemY);

    byte _labelXMin = 6;
    byte _labelXMax = 115;
    byte _outlineWidth = 120;

    byte _size;
    bool _enableLabels = false;
    bool _enableOutline = false;
    bool _enableScrollbar = false;
    bool _enableIcons = false;
    bool _enableCenter = false;
    bool _enableBold = false;

    byte _selected = 0;//öl

    char** _labels;
    unsigned char** _icons;
};

#endif
