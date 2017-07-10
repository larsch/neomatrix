/*
 * Neomatrix - Copyright (C) 2017 Lars Christensen
 * MIT Licensed
 *
 * Arduino/ESP8266 Sketch
 */

#include "neomatrix.hpp"
#include "wifi.hpp"
#include "WiFiServer.h"
#include "WiFiClient.h"
#include "counter.hpp"

WiFiServer server(1080);
WiFiClient client;

static Counter<1, 2> tick;
static uint32_t last = 0;

void setup()
{
  Serial.begin(115200);
  wifi_init();
  neomatrix_init();
  server.begin();
}

void loop()
{
  wifi_run();
  neomatrix_run();

  if (client) {
    uint32_t now = tick();
    if (now != last)
      client.println(analogRead(A0));
    last = now;
  } else {
    client = server.available();
  }
}
