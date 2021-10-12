/*
 * filename: ezil.ino
 */
#include <Arduino_JSON.h>
#include "heltec.h"
#include "define.h"

String ezilGetStatus(String wallet)
{
  String url_prefix = "https://stats.ezil.me/current_stats/";
  String url = url_prefix + wallet + "/reported";
  return httpGETRequest(url.c_str());
}

EzilHashrate ezilJsonToRates(JSONVar data)
{
  EzilHashrate rate;
  rate.current_hashrate = int(data["eth"]["current_hashrate"]);
  rate.average_hashrate = int(data["eth"]["average_hashrate"]);
  rate.last_share_timestamp = int(data["eth"]["last_share_timestamp"]);
  rate.last_share_coin = unquote(JSON.stringify(data["eth"]["last_share_coin"]));
  rate.wallet = unquote(JSON.stringify(data["eth"]["wallet"]));
  rate.reported_hashrate = int(data["eth"]["reported_hashrate"]);
  return rate;
}

void display_hashrate_ezil(EzilHashrate rates)
{
  char hashrate_string[32];
  
  time_t t = time(NULL);
  struct tm *now = localtime(&t);
  Heltec.display->clear();
  Heltec.display->display();

  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, tm2string(now));
  Heltec.display->drawString(0, 20, "\n\nReported @ Ezil\n\n");
  Heltec.display->drawString(90, 32, "MH/s\n");
  
  Heltec.display->setFont(ArialMT_Plain_24);
  sprintf(hashrate_string, "%.2f", rates.reported_hashrate / 1.0e6);
  Heltec.display->drawString(0, 32, hashrate_string);

  Heltec.display->display();
}

void do_ezil()
{
  int count = 0;
  EzilHashrate rates;
  do
  {
    JSONVar ezilObject = JSON.parse(ezilGetStatus(EZIL_WALLET));
    Serial.println(ezilObject);
    if (JSON.typeof(ezilObject) == "undefined")
    {
      Serial.println("Parsing input failed!");
      return;
    }
    rates = ezilJsonToRates(ezilObject);
    if (rates.current_hashrate > 0.0)
    {
      break;
    }
    sleep(100);
    count++;
  } while (count < 3);
  display_hashrate_ezil(rates);
}
