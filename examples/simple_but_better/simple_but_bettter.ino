#include <PotusOledMenu.h>
#include "bitmaps.h"

#define upPin 2
#define downPin 3

PotusOledMenu menu; // create instance of PotusOledMenu class

char labels[][18] = { "Heart", "Play", "People", "Clock", "Arrow", "House" }; // array with labels, second dimension has to be 18
unsigned char* icons[] = { heart, play, people, clock, arrow, house }; // pointer array with bitmaps stored in bitmaps.h

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

void loop() {
  // read buttons and scroll menu accordingly
  if (digitalRead(upPin)) {
    menu.up();
    delay(100);
  }
  else if (digitalRead(downPin)) {
    menu.down();
    delay(100);
  }
}
