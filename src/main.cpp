#include <DNSServer.h>
#include <Arduino.h>
#include <ESPUI.h>

#if defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#include <ESP8266WiFi.h>
#endif
#include "setup/setup.h"
#include "main_server.h"
#include "save_load.h"
#include <string.h>

server_setup server_setup;
main_server main_server;

char versions_nr[40] = "debug 1.2 ENG";

IPAddress apIP(192, 168, 178, 1);
const byte DNS_PORT = 80;
DNSServer dnsServer;

void setup()
{
  strcpy(server_setup.setup_data_1.versions_nr, versions_nr);
  delay(1000);
  save_load save_load;
  Serial.begin(115200);
  save_load.init_eeprom();
  save_load.Load_1(server_setup.setup_data_2.setup_zust, server_setup.setup_data_1.ssid, server_setup.setup_data_1.password, server_setup.setup_data_1.hostname, server_setup.setup_data_1.anzahl_beete, server_setup.setup_data_1.bew_typ, server_setup.setup_data_1.login);
  save_load.Load_2(server_setup.setup_data_2);
  if (server_setup.setup_data_2.setup_zust != 99 && server_setup.setup_data_2.setup_zust != 2)
  {
    strcpy(server_setup.setup_data_1.hostname, "Einrichtung");
  }
  ESPUI.jsonInitialDocumentSize = 30000;
  //dev
  /*
  server_setup.setup_data_2.setup_zust = 99;
  server_setup.setup_data_1.login = 0;
  server_setup.setup_data_1.anzahl_beete = 2;
  strcpy(server_setup.setup_data_2.beet_name[0], String("beet 1 test lol").c_str());
  strcpy(server_setup.setup_data_2.beet_name[1], String("beet 2 test lol").c_str());
*/
  //Dev

#if defined(ESP32)
  WiFi.setHostname(server_setup.setup_data_1.hostname);
#else
  WiFi.hostname(server_setup.setup_data_1.hostname);
#endif

  WiFi.begin(server_setup.setup_data_1.ssid, server_setup.setup_data_1.password);
  Serial.print("\n\nTry to connect to existing network");
  uint8_t timeout = 20;
  // Wait for connection, 5s timeout
  do
  {
    delay(500);
    Serial.print(".");
    timeout--;
  } while (timeout && WiFi.status() != WL_CONNECTED);
  if (WiFi.status() != WL_CONNECTED)
  {
    if (server_setup.setup_data_2.setup_zust != 1)
    {
      //server_setup.setup_data_2.setup_zust = 1;
      server_setup.setup_data_2.end_setup = true;
    }
    Serial.print("\n\nCreating hotspot");
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP("bewässerungsanlage");
    timeout = 5;
    do
    {
      delay(500);
      Serial.print(".");
      timeout--;
    } while (timeout);
  };
  dnsServer.start(DNS_PORT, "*", apIP);
  Serial.println("\n\nWiFi parameters:");
  Serial.print("IP address: ");
  Serial.println(WiFi.getMode() == WIFI_AP ? WiFi.softAPIP() : WiFi.localIP());

  if (!MDNS.begin(server_setup.setup_data_1.hostname))
  {
    Serial.println("Error starting mDNS");
    return;
  }

  if (server_setup.setup_data_2.setup_zust != 2 && server_setup.setup_data_2.setup_zust != 99)
  {
    server_setup.init_1();
  };
  if (server_setup.setup_data_2.setup_zust == 2)
  {
    server_setup.init_2(server_setup.setup_data_1.ssid, server_setup.setup_data_1.password, server_setup.setup_data_1.hostname, server_setup.setup_data_1.anzahl_beete, server_setup.setup_data_1.bew_typ, server_setup.setup_data_1.login);
  };
  if (server_setup.setup_data_2.setup_zust == 99)
  {
    main_server.init_server(server_setup.setup_data_1, server_setup.setup_data_2);
  }
  Serial.println("\n\n setup_zustand");
  Serial.println(server_setup.setup_data_2.setup_zust);
};

void loop()
{
  dnsServer.processNextRequest();
  if (server_setup.setup_data_2.setup_zust != 2 && server_setup.setup_data_2.setup_zust != 99)
  {
    if (server_setup.setup_data_1.end_setup)
    {
      save_load save_load;
      save_load.Save_1(server_setup.setup_data_1.ssid, server_setup.setup_data_1.password, server_setup.setup_data_1.hostname, server_setup.setup_data_1.anzahl_beete, server_setup.setup_data_1.bew_typ, server_setup.setup_data_1.login);
      ESP.restart();
    }
  };
  if (server_setup.setup_data_2.setup_zust == 2 || server_setup.setup_data_2.setup_zust == 99)
  {
    if (server_setup.setup_data_2.end_setup)
    {
      save_load save_load;
      save_load.Save_2(server_setup.setup_data_2);
      ESP.restart();
    }
  };
  if (server_setup.setup_data_2.setup_zust == 99)
  {
    if (main_server.handle_server(server_setup.setup_data_1, server_setup.setup_data_2) == false)
    {
      save_load save_load;
      save_load.Save_1(server_setup.setup_data_1.ssid, server_setup.setup_data_1.password, server_setup.setup_data_1.hostname, server_setup.setup_data_1.anzahl_beete, server_setup.setup_data_1.bew_typ, server_setup.setup_data_1.login);
      save_load.Save_2(server_setup.setup_data_2);
      ESP.restart();
    };
  }
}
