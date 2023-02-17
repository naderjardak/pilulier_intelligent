#define BOARD_TYPE      "AVR Mega2560"
#define EspSerial Serial3
#include "ESP_AT_Lib.h"

#define SSID        "TOPNET_9C38_N"
#define PASSWORD    "nader09882301"

#define ESP_AT_BAUD       115200

ESP8266 wifi(&EspSerial);

void setup(void)
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStart ConnectWiFi on " + String(BOARD_TYPE));

  // initialize serial for ESP module
  EspSerial.begin(ESP_AT_BAUD);

  Serial.print("FW Version: ");
  Serial.println(wifi.getVersion().c_str());


  if (wifi.setOprToStation()) 
  {
    Serial.println("Set STA Mode OK");
  } 
  else 
  {
    Serial.println("Set STA Mode failed");
  }

  if (wifi.joinAP(SSID, PASSWORD)) 
  {
    Serial.println("Connect to WiFi OK");
    Serial.print("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
  } 
  else 
  {
    Serial.println("Connect to WiFi failed");
  }

  Serial.println("Done");
}

void loop(void)
{
}
