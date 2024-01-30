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
    void icons(const unsigned char* iconArray[]);
    void labels(char labelArray[][_labelSize]);
    void draw();
    void up();
    void down();
  private:
    const uint16_t _regularFont = u8g2_font_7x13_mf;
    const uint16_t _boldFont = u8g2_font_7x13B_mf;
    int _size;
    bool _enableIcons;
    int _selected = 0;//öl
    int _previous;
    int _next;
    unsigned char* _temp[1];
    char _labels[][11];
};

#endif