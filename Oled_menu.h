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
    //set the number of menu items
    void size(int size);
    //insert 2D array containing your labels
    void labels(char labelArray[][_labelSize]); 
    //insert pointer to 16x16px icon bitmaps
    void icons(const unsigned char* iconArray[]);
    //draw the menu
    void draw();
    //scroll upwards
    void up();
    //scroll downwards
    void down();
    //jump to specific item, first item is 0
    void jump(int item);
    //returns the currently selected item
    int getSelected();
    
  private:
    static const unsigned char _selectionOutline[] PROGMEM;
    const uint16_t _regularFont = u8g2_font_7x13_mf;
    const uint16_t _boldFont = u8g2_font_7x13B_mf;
    const int _previousY = 15;
    const int _selectedY = 37;
    const int _nextY = 59;
    const int _labelX = 25;
    const int _iconX = 4;

    void drawItem(int item, int itemY, uint16_t font);

    int _size;
    bool _enableIcons = false;
    int _selected = 0;//öl
    int _previous;
    int _next;
    char** _labels;
    const unsigned char** _icons;
};

#endif