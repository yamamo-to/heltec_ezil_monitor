#include <Arduino.h>
#include <Arduino_JSON.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "heltec.h"
#include "define.h"
#include "ezil.h"

int update_cycle_in_minutes = 10;  /* min */
unsigned long lastTime = 0;
unsigned long timerDelay = 60000;


void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  pinMode(25, OUTPUT);
  digitalWrite(25,LOW);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Initialize...");

  setupWifi(MY_SSID, MY_SSID_PASS);
  setupTime();
}

void loop()
{

  if ((lastTime == 0) || ((millis() - lastTime) > timerDelay))
  {
    time_t t;
    struct tm *now;

    t = time(NULL);
    now = localtime(&t);

    if (now->tm_min % update_cycle_in_minutes == 0)
    {
      if (WiFi.status() == WL_CONNECTED)
      {
        do_ezil();
      }
      else
      {
        Serial.println("WiFi Disconnected");
      }
    }
    lastTime = millis();
  }
}
