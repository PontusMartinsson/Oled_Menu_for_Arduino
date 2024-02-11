#ifndef Oled_menu_h
#define Oled_menu_h

#include "Arduino.h"
#include <U8g2lib.h>

#define _labelSize 11
#define _iconSize 32

class Oled_menu {
  public:
    Oled_menu();
    void begin();
    void config(int size, bool enableIcons); 
    // void icons(const unsigned char* iconArray[]);
    // insert 2D array containing your labels
    void labels(char labelArray[][_labelSize]); 
    //Draw the menu
    void draw();
    //Scroll upwards
    void up();
    //Scroll downwards
    void down();
  private:
    const uint16_t _regularFont = u8g2_font_7x13_mf;
    const uint16_t _boldFont = u8g2_font_7x13B_mf;
    const int _previousY = 15;
    const int _selectedY = 37;
    const int _nextY = 59;
    const int _labelX = 25;
    const int _iconX = 4;

    void drawItem(int item, int itemY, uint16_t font);

    int _size;
    bool _enableIcons;
    int _selected = 0;//öl
    int _previous;
    int _next;
    // unsigned char* _temp[1];
    // char _labels[15][11];
    char** _labels;
};

#endif