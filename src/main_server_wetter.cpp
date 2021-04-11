#include <Arduino.h>
#include <DNSServer.h>
#include <ESPUI.h>

#if defined(ESP32)
#include <WiFi.h>
#include <HTTPClient.h>
#else
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif
#include <string.h>

#include <ArduinoJson.h>
#include "setup/setup.h"
#include "main_server.h"

wetter_dat main_server::wetter_data;

String main_server::wetter_klassifizierung(int id)
{
    Serial.print("die ID ist:");
    Serial.println(id);
    switch (id)
    {
    case 200:
        return String("Gewitter mit leichtem Regen");
        break;
    case 201:
        return String("Gewitter mit  Regen");
        break;
    case 202:
        return String("Gewitter mit starkem leichtem Regen");
        break;
    case 210:
        return String("Gewitter");
        break;
    case 211:
        return String("leichtes Gewitter");
        break;
    case 212:
        return String("Starkes Gewitter");
        break;
    case 221:
        return String("Aufziehendes Gewwitter");
        break;
    case 230:
        return String("Gewitter mit leichtem Nieselregen");
        break;
    case 231:
        return String("Gewitter mit Nieselregen");
        break;
    case 232:
        return String("Gewitter mit Starkem Nieselregen");
        break;
    case 300:
        return String("Niesel");
        break;
    case 301:
        return String("Niesel");
        break;
    case 302:
        return String("Niesel");
        break;
    case 500:
        return String("Leichter Regen");
        break;
    case 501:
        return String("moderater Regen");
        break;
    case 502:
        return String("Starker Regen");
        break;
    case 503:
        return String("sehr Starker Regen");
        break;
    case 504:
        return String("extremer Regen");
        break;
    case 511:
        return String("Hagel");
        break;
    case 520:
        return String("Duschregen");
        break;
    case 521:
        return String("Starker Duschregen");
        break;
    case 522:
        return String("sehr Starker Duschregen");
        break;
    case 531:
        return String("aufziehender Duschregen");
        break;
    case 701:
        return String("Nebel");
        break;
    case 711:
        return String("Rauch");
        break;
    case 721:
        return String("Dunst");
        break;
    case 731:
        return String("Sand");
        break;
    case 741:
        return String("starker Nebel");
        break;
    case 751:
        return String("Sand");
        break;
    case 761:
        return String("Staub");
        break;
    case 762:
        return String("Vulkanische Asche");
        break;
    case 771:
        return String("Sturm");
        break;
    case 781:
        return String("Tornado");
        break;
    }
    if (id > 303 && id < 333)
    {
        return String("Nieselregen");
    }
    if (id > 599 && id < 623)
    {
        return String("Schnee");
    }
    if (id == 800)
    {
        return String("Klarer Himmel");
    }
    if (id > 800 && id < 805)
    {
        return String("Wolkig");
    }
    return String("Ich weiß es nicht so genau, schau bitte deine API einstellungen nocheinmal an.");
};

wetter_dat main_server::abfrage_wetter(const char *breitengrad, const char *laengengrad, const char *appid)
{
    wetter_dat wetter_data_help;
    if (WiFi.status() == WL_CONNECTED)
    { //Check WiFi connection status

        HTTPClient http; //Declare an object of class HTTPClient

        char *adresse = new char[strlen("http://api.openweathermap.org/data/2.5/onecall?lat=") + strlen(breitengrad) + strlen("&lon=") + strlen(laengengrad) + strlen("&exclude=minutely,hourly,alerts&appid=") + strlen(appid)];
        strcpy(adresse, "http://api.openweathermap.org/data/2.5/onecall?lat=");
        strcat(adresse, breitengrad);
        strcat(adresse, "&lon=");
        strcat(adresse, laengengrad);
        strcat(adresse, "&exclude=minutely,hourly,alerts&appid=");
        strcat(adresse, appid);
        Serial.println(adresse);
        http.begin(adresse);       //Specify request destination
        int httpCode = http.GET(); //Send the request
        String payload = http.getString();
        Serial.print("Response Code:"); //200 is OK
        Serial.println(httpCode);
        Serial.println("Start");
        Serial.print("Returned data from Server:");
        //Serial.println(payload);
        if (httpCode == 200)
        {
            const size_t capacity = 6144;
            DynamicJsonBuffer jsonBuffer(capacity);
            JsonObject &root = jsonBuffer.parseObject(payload);
            if (!root.success())
            {
                Serial.println(F("Parsing failed!"));
                wetter_data_help.aktuell.id = 999;
                wetter_data_help.voraus[0].id = 999;
                wetter_data_help.voraus[1].id = 999;
                return wetter_data_help;
            }
            //Serial.println(root["daily"][0]["dt"].as<long>());
            wetter_data_help.aktuell.datum = root["current"]["dt"].as<long>();
            wetter_data_help.aktuell.id = root["current"]["weather"][0]["id"].as<int>();
            for (int i = 0; i < 2; i++)
            {
                wetter_data_help.voraus[i].datum = root["daily"][i]["dt"].as<long>();
                wetter_data_help.voraus[i].id = root["daily"][i]["weather"][0]["id"].as<int>();
            };
        }
        else
        {
            wetter_data_help.aktuell.id = 999;
            wetter_data_help.voraus[0].id = 999;
            wetter_data_help.voraus[1].id = 999;
        }
        http.end(); //Close connection
    }
    Serial.print("aktueller timestamp: ");
    Serial.println(wetter_data_help.aktuell.datum);
    Serial.print("aktuelle wetter id: ");
    Serial.println(wetter_data_help.aktuell.id);
    Serial.print("voraussage timestamp: ");
    Serial.println(wetter_data_help.voraus[0].datum);
    Serial.print("vorraussage wetter id: ");
    Serial.println(wetter_data_help.voraus[0].id);
    Serial.print("voraussage timestamp: ");
    Serial.println(wetter_data_help.voraus[1].datum);
    Serial.print("vorraussage wetter id: ");
    Serial.println(wetter_data_help.voraus[1].id);
    long heute_21_uhr = wetter_data_help.voraus[0].datum + 32400;
    wetter_data_help.timestamp_heute_21 = heute_21_uhr;
    wetter_data_help.h_bis_21 = (heute_21_uhr - wetter_data_help.aktuell.datum) / 3600;
    heute_21_uhr = (heute_21_uhr - wetter_data_help.aktuell.datum) % 3600;
    wetter_data_help.min_bis_21 = heute_21_uhr / 60;
    heute_21_uhr = heute_21_uhr % 60;
    wetter_data_help.sek_bis_21 = heute_21_uhr;
    Serial.print("zeit bis 21 uhr winterzeit bzw 22 sommerzeit: ");
    Serial.print(wetter_data_help.h_bis_21);
    Serial.print(":");
    Serial.print(wetter_data_help.min_bis_21);
    Serial.print(":");
    Serial.println(wetter_data_help.sek_bis_21);
    load_flaggs.reload_wetter = false;
    return wetter_data_help;
};