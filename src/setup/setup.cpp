#include <DNSServer.h>
#include <ESPUI.h>
#if defined(ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <string.h>
#include "setup.h"

int server_setup::ID_init_1[7] = {0, 0, 0, 0, 0, 0, 0};

setup_data1 server_setup::setup_data_1;

void server_setup::select_set_1(Control *sender, int value)
{
    Serial.print("Select: ID: ");
    Serial.print(sender->id);
    Serial.print(", Value: ");
    Serial.println(sender->value);
    if (sender->id == ID_init_1[3])
    {
        if (sender->value == String("1"))
        {
            setup_data_1.anzahl_beete = 1;
        };
        if (sender->value == String("2"))
        {
            setup_data_1.anzahl_beete = 2;
        };
        if (sender->value == String("3"))
        {
            setup_data_1.anzahl_beete = 3;
        };
        if (sender->value == String("4"))
        {
            setup_data_1.anzahl_beete = 4;
        };
        if (sender->value == String("5"))
        {
            setup_data_1.anzahl_beete = 5;
        };
        if (sender->value == String("6"))
        {
            setup_data_1.anzahl_beete = 6;
        };
        if (sender->value == String("7"))
        {
            setup_data_1.anzahl_beete = 7;
        };
        if (sender->value == String("8"))
        {
            setup_data_1.anzahl_beete = 8;
        };
        if (sender->value == String("9"))
        {
            setup_data_1.anzahl_beete = 9;
        };
        if (sender->value == String("10"))
        {
            setup_data_1.anzahl_beete = 10;
        };
        if (sender->value == String("11"))
        {
            setup_data_1.anzahl_beete = 11;
        };
        if (sender->value == String("12"))
        {
            setup_data_1.anzahl_beete = 12;
        };
        if (sender->value == String("13"))
        {
            setup_data_1.anzahl_beete = 13;
        };
        if (sender->value == String("14"))
        {
            setup_data_1.anzahl_beete = 14;
        };
        if (sender->value == String("15"))
        {
            setup_data_1.anzahl_beete = 15;
        };
        if (sender->value == String("16"))
        {
            setup_data_1.anzahl_beete = 16;
        };
        if (sender->value == String("17"))
        {
            setup_data_1.anzahl_beete = 17;
        };
        if (sender->value == String("18"))
        {
            setup_data_1.anzahl_beete = 18;
        };
        if (sender->value == String("19"))
        {
            setup_data_1.anzahl_beete = 19;
        };
        if (sender->value == String("20"))
        {
            setup_data_1.anzahl_beete = 20;
        };
    };
    if (sender->id == ID_init_1[5])
    {
        if (sender->value == String("Opt1"))
        {
            setup_data_1.bew_typ = 1;
        };
        if (sender->value == String("Opt2"))
        {
            setup_data_1.bew_typ = 2;
        };
        if (sender->value == String("Opt3"))
        {
            setup_data_1.bew_typ = 3;
        };
    }
    Serial.println(setup_data_1.anzahl_beete);
    Serial.println(setup_data_1.bew_typ);
}

void server_setup::switch_set_1(Control *sender, int value)
{
    if (sender->id == ID_init_1[4])
    {
        switch (value)
        {
        case S_ACTIVE:
            setup_data_1.login = 1;
            break;

        case S_INACTIVE:
            Serial.print("Inactive");
            setup_data_1.login = 0;
            break;
        }
    };
}

void server_setup::textCall_set_1(Control *sender, int type)
{
    Serial.print("Text: ID: ");
    Serial.print(sender->id);
    if (sender->id == ID_init_1[0])
    {
        strcpy(setup_data_1.ssid, sender->value.c_str());
        Serial.println(setup_data_1.ssid);
    };
    if (sender->id == ID_init_1[1])
    {
        strcpy(setup_data_1.password, sender->value.c_str());
        Serial.println(setup_data_1.password);
    };
    if (sender->id == ID_init_1[2])
    {
        strcpy(setup_data_1.hostname, sender->value.c_str());
        Serial.println(setup_data_1.hostname);
    };
}

void server_setup::buttonCallback_set_1(Control *sender, int type)
{
    switch (type)
    {
    case B_DOWN:
        if (sender->id == ID_init_1[6])
        {
            setup_data_1.end_setup = true;
        }
        Serial.println(setup_data_1.end_setup);
        break;

    case B_UP:
        Serial.println("Button UP");
        break;
    }
}

void server_setup::init_1()
{
    //init data
    setup_data_1.anzahl_beete = 1;
    setup_data_1.bew_typ = 3;
    setup_data_1.login = 0;
    strcpy(setup_data_1.ssid, "bewaesserungssystem");
    strcpy(setup_data_1.password, "bewaesserungssystem");
    strcpy(setup_data_1.hostname, "bewaesserungssystem");
    ESPUI.setVerbosity(Verbosity::VerboseJSON);

    uint16_t tab1 = ESPUI.addControl(ControlType::Tab, "Setup schritt 1", "Setup schritt 1");
    ESPUI.addControl(ControlType::Label, "Wilkommen:", "Bitte füllen sie die Nachfolgenden felder aus: nach dem bestätigen Startet der Server neu und ist dann unter der IP: 192.168.178.1 zu erreichen. ist dies nicht der fall schauen sie die IP in den einstellungen ihres Routers nach.", ControlColor::Turquoise, tab1);
    ID_init_1[0] = ESPUI.addControl(ControlType::Text, "SSID:", "Martin Router King", ControlColor::Alizarin, tab1, &textCall_set_1);
    ID_init_1[1] = ESPUI.addControl(ControlType::Text, "Passwort:", "ABC123BlaBla", ControlColor::Alizarin, tab1, &textCall_set_1);
    ID_init_1[2] = ESPUI.addControl(ControlType::Text, "Name des systems:", "Bewässerungsanlage", ControlColor::Alizarin, tab1, &textCall_set_1);
    ID_init_1[3] = ESPUI.addControl(ControlType::Select, "Anzahl der beete", "", ControlColor::Alizarin, tab1, &select_set_1);
    ESPUI.addControl(ControlType::Option, "1", "1", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "2", "2", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "3", "3", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "4", "4", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "5", "5", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "6", "6", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "7", "7", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "8", "8", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "9", "9", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "10", "10", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "11", "11", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "12", "12", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "13", "13", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "14", "14", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "15", "15", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "16", "16", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "17", "17", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "18", "18", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "19", "19", ControlColor::Alizarin, ID_init_1[3]);
    ESPUI.addControl(ControlType::Option, "20", "20", ControlColor::Alizarin, ID_init_1[3]);
    ID_init_1[4] = ESPUI.addControl(ControlType::Switcher, "Benutzeroberfläche mit Login Schützen", "", ControlColor::Alizarin, tab1, &switch_set_1);
    ID_init_1[5] = ESPUI.addControl(ControlType::Select, "Bewässerungs Typ:", "Opt3", ControlColor::Alizarin, tab1, &select_set_1);
    ESPUI.addControl(ControlType::Option, "Manuell", "Opt1", ControlColor::Alizarin, ID_init_1[5]);
    ESPUI.addControl(ControlType::Option, "nach Bodenfeuchte", "Opt2", ControlColor::Alizarin, ID_init_1[5]);
    ESPUI.addControl(ControlType::Option, "nach Bodenfeuchte + Wetter", "Opt3", ControlColor::Alizarin, ID_init_1[5]);
    ID_init_1[6] = ESPUI.addControl(ControlType::Button, "Angaben Bestätigen:", "Drücken", ControlColor::Wetasphalt, tab1, &buttonCallback_set_1);
    ESPUI.begin("Einrichtung der Bewässerungsanlage");
};

setup_data1 server_setup::handle_setup_1()
{

    return setup_data_1;
};
