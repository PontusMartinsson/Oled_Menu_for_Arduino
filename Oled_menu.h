#ifndef Oled_menu_h
#define Oled_menu_h

#include "Arduino.h"
#include <U8g2lib.h>

#define _labelSize 18

class Oled_menu {
  public:
    Oled_menu();
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
    // Enable/disable bold text on selected item
    void enableBold(bool enable);
    // Configure all options
    void config(int size, bool labels, bool outline, bool scrollbar, bool icons, bool bold);

    // Specify all labels
    void labels(char labelArray[][_labelSize]); 
    // Specify label, requires labels() to have been set
    void setLabel(char label, int item);
    // Specify all icons
    void icons(const unsigned char* iconArray[]);
    // Specify icon, requires icons() to have been set
    void setIcon(const unsigned char* icon, int item);

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
    void drawItem(int item, int itemY);

    const uint16_t _regularFont = u8g2_font_7x13_mf;
    const uint16_t _boldFont = u8g2_font_7x13B_mf;

    const int _previousY = 15;
    const int _selectedY = 37;
    const int _nextY = 59;
    const int _iconX = 4;

    int _labelX = 6;
    int _outlineWidth = 120;

    int _size;
    bool _enableLabels = false;
    bool _enableOutline = true;
    bool _enableScrollbar = true;
    bool _enableIcons = false;
    bool _enableBold = true;

    int _selected = 0;//öl
    int _previous;
    int _next;

    char** _labels;
    const unsigned char** _icons;
};

#endif