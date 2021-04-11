#include <DNSServer.h>
#include <ESPUI.h>

#if defined(ESP32)
#include <WiFi.h>
#include <AsyncTCP.h>
#include <HTTPClient.h>
#else
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESP8266HTTPClient.h>
#endif
#include <string.h>
#include "setup/setup.h"
#include "main_server.h"
#include "save_load.h"

uint32_t main_server::timer_zwischenspeicher_sensoren = 0;
uint32_t main_server::timer_zwischenspeicher_refresh = 0;

String main_server::httpGETRequest(const char *serverName)
{
    WiFiClient client;
    HTTPClient http;

    // Your IP address with path or Domain name with URL path
    http.begin(client, serverName);

    // Send HTTP POST request
    int httpResponseCode = http.GET();
    String payload = "Offline";

    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        payload = "111";
    }
    // Free resources
    http.end();
    Serial.println(payload);
    //Serial.print("payload in int");
    //Serial.println(help);
    delay(1);
    return payload;
}

bool main_server::refresh_timer_sensoren()
{
    //zehn min = 600000
    if (millis() - timer_zwischenspeicher_sensoren > 60000 * 60)
    {
        timer_zwischenspeicher_sensoren = millis();
        return true;
    }
    return false;
}

bool main_server::refresh_timer()
{
    //zehn min = 600000
    if (millis() - timer_zwischenspeicher_refresh > 600000)
    {
        timer_zwischenspeicher_refresh = millis();
        return true;
    }
    return false;
}

void main_server::abfrage_sensoren()
{

    for (int i = 0; i < update_data_1.anzahl_beete; i++)
    {
        Serial.println(i);
        char *adresse = new char[strlen("http://") + strlen(update_data_2.IP_sensor[i]) + strlen("/abfrage")];
        strcpy(adresse, "http://");
        strcat(adresse, update_data_2.IP_sensor[i]);
        strcat(adresse, "/abfrage");
        for (int a = 23; a > 0; a--)
        {
            data_beete[i].beet_feuchte[a] = data_beete[i].beet_feuchte[a - 1];
        }
        data_beete[i].beet_feuchte[0] = httpGETRequest(adresse).toInt();
        Serial.print("Sensor ");
        Serial.print(i);
        Serial.print(" : ");
        Serial.println(data_beete[i].beet_feuchte[0]);
    }
}

void main_server::reset_var_check()
{
    if (wetter_data.aktuell.datum > wetter_data.voraus[0].datum - 21600 && wetter_data.aktuell.datum < wetter_data.voraus[0].datum - 20400)
    {
        //wenn es um 6 UTC+1 ist, resette die bewässerungs variablen
        for (int i = 0; i < update_data_1.anzahl_beete; i++)
        {
            data_beete[i].bew_beendet = false;
        }
    }
};

void main_server::abfrage_ventil()
{
    for (int i = 0; i < update_data_1.anzahl_beete; i++)
    {
        String(update_data_2.ventil_nr[i]);
        char *adresse = new char[strlen("http://") + strlen(update_data_2.IP_ventil[i]) + strlen("/abfrage_relay?relay_nr=") + strlen("00")];
        strcpy(adresse, "http://");
        strcat(adresse, update_data_2.IP_ventil[i]);
        strcat(adresse, "/abfrage_relay?relay_nr=");
        char cstr[8];
        itoa(update_data_2.ventil_nr[i], cstr, 10);
        strcat(adresse, cstr);
        Serial.print("adresse:");
        Serial.println(adresse);
        data_beete[i].ventil_zustand = httpGETRequest(adresse);
        if (data_beete[i].ventil_zustand == "111")
        {
            data_beete[i].ventil_zustand = "nicht erreichbar";
        };
    }
}

void main_server::set_ventil(int i, char zeit[])
{
    char nr[2];
    itoa(update_data_2.ventil_nr[i], nr, 10);
    char *adresse = new char[strlen("http://") + strlen(update_data_2.IP_ventil[i]) + strlen("/set_relay?relay_nr=") + strlen(nr) + strlen("&bew_zeit=") + strlen(zeit)];
    strcpy(adresse, "http://");
    strcat(adresse, update_data_2.IP_ventil[i]);
    strcat(adresse, "/set_relay?relay_nr=");
    strcat(adresse, nr);
    strcat(adresse, "&bew_zeit=");
    strcat(adresse, zeit);
    Serial.print("call adresse: ");
    Serial.println(adresse);
    httpGETRequest(adresse);
    data_beete[i].bew_beendet = true;
};

void main_server::stop_ventil(int i)
{
    char nr[2];
    itoa(update_data_2.ventil_nr[i], nr, 10);
    char *adresse = new char[strlen("http://") + strlen(update_data_2.IP_ventil[i]) + strlen("/set_relay?relay_nr=") + strlen(nr) + strlen("&schalten=1")];
    strcpy(adresse, "http://");
    strcat(adresse, update_data_2.IP_ventil[i]);
    strcat(adresse, "/set_relay?relay_nr=");
    strcat(adresse, nr);
    strcat(adresse, "&schalten=1");
    httpGETRequest(adresse);
};

void main_server::berechnung_bewaesserung()
{
    for (int i = 0; i < update_data_1.anzahl_beete; i++)
    {

        //falls bewesserung aktiviert ist.
        if (data_beete[i].bew_beendet == false)
        {
            if (data_beete[i].bew_geplant)
            {
                if (data_beete[i].beet_feuchte[0] < data_einst.min_feuchte)
                {
                    switch (data_einst.min_regen_id)
                    {
                    //leicht
                    case 0:
                        //aktuell
                        //regen
                        if (wetter_data.aktuell.id > 500 && wetter_data.aktuell.id < 532)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.aktuell.id > 200 && wetter_data.aktuell.id < 233)
                        { //Gewitter
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.aktuell.id > 600 && wetter_data.aktuell.id < 623)
                        { //schnee
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.voraus[1].id > 500 && wetter_data.voraus[1].id < 532)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.voraus[1].id > 200 && wetter_data.voraus[1].id < 233)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.voraus[1].id > 600 && wetter_data.voraus[1].id < 623)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else
                        {
                            Serial.println("auto_bew gespeichert");
                            data_beete[i].auto_bew = true;
                        }
                        break;
                    //moderat
                    case 1:
                        if (wetter_data.aktuell.id > 501 && wetter_data.aktuell.id < 532)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.aktuell.id > 201 && wetter_data.aktuell.id < 233)
                        { //Gewitter
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.aktuell.id > 601 && wetter_data.aktuell.id < 623)
                        { //schnee
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.voraus[1].id > 501 && wetter_data.voraus[1].id < 532)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.voraus[1].id > 201 && wetter_data.voraus[1].id < 233)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.voraus[1].id > 601 && wetter_data.voraus[1].id < 623)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else
                        {
                            data_beete[i].auto_bew = true;
                        }
                        break;
                    //stark
                    case 2:
                        if (wetter_data.aktuell.id > 502 && wetter_data.aktuell.id < 532)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.aktuell.id > 202 && wetter_data.aktuell.id < 233)
                        { //Gewitter
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.aktuell.id > 602 && wetter_data.aktuell.id < 623)
                        { //schnee
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.voraus[1].id > 502 && wetter_data.voraus[1].id < 532)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.voraus[1].id > 202 && wetter_data.voraus[1].id < 233)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.voraus[1].id > 602 && wetter_data.voraus[1].id < 623)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else
                        {
                            data_beete[i].auto_bew = true;
                        }
                        break;
                    default:
                        if (wetter_data.aktuell.id > 501 && wetter_data.aktuell.id < 532)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.aktuell.id > 201 && wetter_data.aktuell.id < 233)
                        { //Gewitter
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.aktuell.id > 601 && wetter_data.aktuell.id < 623)
                        { //schnee
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.voraus[1].id > 501 && wetter_data.voraus[1].id < 532)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.voraus[1].id > 201 && wetter_data.voraus[1].id < 233)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else if (wetter_data.voraus[1].id > 601 && wetter_data.voraus[1].id < 623)
                        {
                            data_beete[i].auto_bew = false;
                        }
                        else
                        {
                            data_beete[i].auto_bew = true;
                        }
                        break;
                    }
                }
            }
        }
    }

    if (wetter_data.timestamp_heute_21 < wetter_data.aktuell.datum && wetter_data.timestamp_heute_21 + 1000 > wetter_data.aktuell.datum)
    {
        for (int i = 0; i < update_data_1.anzahl_beete; i++)
        {
            if (data_beete[i].bew_geplant && data_beete[i].auto_bew && !data_beete[i].bew_beendet)
            {
                char zeit[3];
                itoa(update_data_2.stand_bew_zeit[i], zeit, 10);
                set_ventil(i, zeit);
            }
        }
    }
};
