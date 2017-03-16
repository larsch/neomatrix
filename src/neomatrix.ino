/*
 * Neomatrix - Copyright (C) 2017 Lars Christensen
 * MIT Licensed
 *
 * Arduino/ESP8266 Sketch
 */

#include "neomatrix.hpp"
#include "wifi.hpp"

void setup()
{
  Serial.begin(115200);
  wifi_init();
  neomatrix_init();
}

void loop()
{
  wifi_run();
  neomatrix_run();
}
