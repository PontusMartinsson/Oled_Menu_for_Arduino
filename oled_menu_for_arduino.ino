#include "Oled_menu.h"

Oled_menu pall;

char balls[][11] = { "gg", "hanoos", "the zaza" };

void setup() {
  pall.begin();
  pall.labels(balls);
  pall.config(25, true);
}

void loop() {
  pall.up();
  pall.draw();
  delay(2000);
}