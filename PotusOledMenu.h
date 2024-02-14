#ifndef PotusOledMenu_h
#define PotusOledMenu_h

#include "Arduino.h"
#include <U8g2lib.h>

#define _labelSize 18

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
    void config(int size, bool labels, bool outline, bool scrollbar, bool icons, bool center, bool bold);

    // Specify all labels
    void labels(char labelArray[][_labelSize]); 
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
