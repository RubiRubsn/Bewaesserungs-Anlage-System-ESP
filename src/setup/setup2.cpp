#include <DNSServer.h>
#include <ESPUI.h>
#if defined(ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <string.h>
#include "setup.h"
#include "../language.h"

#define debugmode 1

setup_data2 server_setup::setup_data_2;
id_init2 server_setup::id_init_2;

void server_setup::update_text()
{
    if (id_init_2.ausgew_beet != 99)
    {
        ESPUI.print(id_init_2.id_beet.id_name, String(setup_data_2.beet_name[id_init_2.ausgew_beet]));
        ESPUI.print(id_init_2.id_beet.id_ip_relay, String(setup_data_2.IP_ventil[id_init_2.ausgew_beet]));
        ESPUI.print(id_init_2.id_beet.id_ip_sensor, String(setup_data_2.IP_sensor[id_init_2.ausgew_beet]));
        ESPUI.print(id_init_2.id_beet.id_ip_relay_nr, String(setup_data_2.ventil_nr[id_init_2.ausgew_beet]));
        ESPUI.print(id_init_2.id_beet.id_stand_bew_zeit, String(setup_data_2.stand_bew_zeit[id_init_2.ausgew_beet]));
    };
};

int server_setup::dev_button_id = 0;

void server_setup::textCall_set_2(Control *sender, int type)
{
    //Login usrname
    if (sender->id == id_init_2.login[0])
    {
        strcpy(setup_data_2.login[0], sender->value.c_str());
#if debugmode == 1
        Serial.print("Login usrname: ");
        Serial.println(setup_data_2.login[0]);
#endif
    };
    //Login passwort
    if (sender->id == id_init_2.login[1])
    {
        strcpy(setup_data_2.login[1], sender->value.c_str());
#if debugmode == 1
        Serial.print("Login pw: ");
        Serial.println(setup_data_2.login[1]);
#endif
    };

    //Wetter API Code
    if (sender->id == id_init_2.wetter[0])
    {
        strcpy(setup_data_2.wetter[0], sender->value.c_str());
#if debugmode == 1
        Serial.print("Wetter API code ");
        Serial.println(setup_data_2.wetter[0]);
#endif
    };
    //Wetter API Breite
    if (sender->id == id_init_2.wetter[1])
    {
        strcpy(setup_data_2.wetter[1], sender->value.c_str());
#if debugmode == 1
        Serial.print("Wetter breite ");
        Serial.println(setup_data_2.wetter[1]);
#endif
    };
    //Wetter API Länge
    if (sender->id == id_init_2.wetter[2])
    {
        strcpy(setup_data_2.wetter[2], sender->value.c_str());
#if debugmode == 1
        Serial.print("Wetter Länge ");
        Serial.println(setup_data_2.wetter[2]);
#endif
    };
        //beete

#if debugmode == 1
    Serial.print("\n Beet: ");
    Serial.println(id_init_2.ausgew_beet);
#endif
    if (id_init_2.ausgew_beet != 99)
    {
        //beet name
        if (sender->id == id_init_2.id_beet.id_name)
        {
            strcpy(setup_data_2.beet_name[id_init_2.ausgew_beet], sender->value.c_str());
#if debugmode == 1
            Serial.print("Beet Name: ");
            Serial.println(setup_data_2.beet_name[id_init_2.ausgew_beet]);
#endif
        };
        //Relay IP
        if (sender->id == id_init_2.id_beet.id_ip_relay)
        {
            strcpy(setup_data_2.IP_ventil[id_init_2.ausgew_beet], sender->value.c_str());
#if debugmode == 1
            Serial.print("IP_ventil: ");
            Serial.println(setup_data_2.IP_ventil[id_init_2.ausgew_beet]);
#endif
        };
        //IP Sensor
        if (sender->id == id_init_2.id_beet.id_ip_sensor)
        {
            strcpy(setup_data_2.IP_sensor[id_init_2.ausgew_beet], sender->value.c_str());
#if debugmode == 1
            Serial.print("IP_sensor: ");
            Serial.println(setup_data_2.IP_sensor[id_init_2.ausgew_beet]);
#endif
        };
    }
}

void server_setup::select_set_2(Control *sender, int value)
{
    if (sender->id == id_init_2.ausgew_beet_id)
    {
        if (sender->value == "0")
        {
            id_init_2.ausgew_beet = 0;
        };
        if (sender->value == "1")
        {
            id_init_2.ausgew_beet = 1;
        };
        if (sender->value == "2")
        {
            id_init_2.ausgew_beet = 2;
        };
        if (sender->value == "3")
        {
            id_init_2.ausgew_beet = 3;
        };
        if (sender->value == "4")
        {
            id_init_2.ausgew_beet = 4;
        };
        if (sender->value == "5")
        {
            id_init_2.ausgew_beet = 5;
        };
        if (sender->value == "6")
        {
            id_init_2.ausgew_beet = 6;
        };
        if (sender->value == "7")
        {
            id_init_2.ausgew_beet = 7;
        };
        if (sender->value == "8")
        {
            id_init_2.ausgew_beet = 8;
        };
        if (sender->value == "9")
        {
            id_init_2.ausgew_beet = 9;
        };
        if (sender->value == "10")
        {
            id_init_2.ausgew_beet = 10;
        };
        if (sender->value == "11")
        {
            id_init_2.ausgew_beet = 11;
        };
        if (sender->value == "12")
        {
            id_init_2.ausgew_beet = 12;
        };
        if (sender->value == "13")
        {
            id_init_2.ausgew_beet = 13;
        };
        if (sender->value == "14")
        {
            id_init_2.ausgew_beet = 14;
        };
        if (sender->value == "15")
        {
            id_init_2.ausgew_beet = 15;
        };
        if (sender->value == "16")
        {
            id_init_2.ausgew_beet = 16;
        };
        if (sender->value == "17")
        {
            id_init_2.ausgew_beet = 17;
        };
        if (sender->value == "18")
        {
            id_init_2.ausgew_beet = 18;
        };
        if (sender->value == "19")
        {
            id_init_2.ausgew_beet = 19;
        };
        if (sender->value == "99")
        {
            id_init_2.ausgew_beet = 99;
        };
        update_text();
    }
    if (id_init_2.ausgew_beet != 99)
    {
        if (sender->id == id_init_2.id_beet.id_stand_bew_zeit)
        {
            if (sender->value == String("15"))
            {
                setup_data_2.stand_bew_zeit[id_init_2.ausgew_beet] = 15;
            };
            if (sender->value == String("30"))
            {
                setup_data_2.stand_bew_zeit[id_init_2.ausgew_beet] = 30;
            };
            if (sender->value == String("45"))
            {
                setup_data_2.stand_bew_zeit[id_init_2.ausgew_beet] = 45;
            };
            if (sender->value == String("60"))
            {
                setup_data_2.stand_bew_zeit[id_init_2.ausgew_beet] = 60;
            };
            if (sender->value == String("75"))
            {
                setup_data_2.stand_bew_zeit[id_init_2.ausgew_beet] = 75;
            };
            if (sender->value == String("90"))
            {
                setup_data_2.stand_bew_zeit[id_init_2.ausgew_beet] = 90;
            };
            if (sender->value == String("105"))
            {
                setup_data_2.stand_bew_zeit[id_init_2.ausgew_beet] = 105;
            };
            if (sender->value == String("120"))
            {
                setup_data_2.stand_bew_zeit[id_init_2.ausgew_beet] = 120;
            };

#if debugmode == 1
            Serial.print("Beet:");
            Serial.println(id_init_2.ausgew_beet);
            Serial.print("bew_zeit:");
            Serial.println(setup_data_2.stand_bew_zeit[id_init_2.ausgew_beet]);
#endif
        };
        if (sender->id == id_init_2.id_beet.id_ip_relay_nr)
        {
            if (sender->value == String("1"))
            {
                setup_data_2.ventil_nr[id_init_2.ausgew_beet] = 1;
            };
            if (sender->value == String("2"))
            {
                setup_data_2.ventil_nr[id_init_2.ausgew_beet] = 2;
            };
            if (sender->value == String("3"))
            {
                setup_data_2.ventil_nr[id_init_2.ausgew_beet] = 3;
            };
            if (sender->value == String("4"))
            {
                setup_data_2.ventil_nr[id_init_2.ausgew_beet] = 4;
            };
#if debugmode == 1
            Serial.print("Beet:");
            Serial.println(id_init_2.ausgew_beet);
            Serial.print("Relay Nr:");
            Serial.println(setup_data_2.ventil_nr[id_init_2.ausgew_beet]);
#endif
        }
    }
}

void server_setup::buttonCallback_set_2(Control *sender, int type)
{
    switch (type)
    {
    case B_DOWN:
        if (sender->id == id_init_2.absenden)
        {

            setup_data_2.end_setup = true;
            setup_data_2.setup_zust = 99;
        }
#if debugmode == 1
        if (sender->id == dev_button_id)
        {
            setup_data_2.end_setup = true;
            setup_data_2.setup_zust = 1;
        }
#endif
        break;

    case B_UP:
        Serial.println("Button UP");
        break;
    }
}

void server_setup::init_2(const char *ssid, const char *password, const char *hostname, const uint8_t anz_bee, const uint8_t bew_typ, const uint8_t login)
{
    lang_setup_2 language;
    setup_data_1.anzahl_beete = anz_bee;
    strcpy(setup_data_2.login[0], "Eren Jaeger");
    strcpy(setup_data_2.login[1], "o mai ma mou shindeiru");
    strcpy(setup_data_2.wetter[0], "011235813");
    strcpy(setup_data_2.wetter[1], "52.516275");
    strcpy(setup_data_2.wetter[2], "13.377704");

    //init text Datein
    for (int i = 0; i < 20; i++)
    {
        strcpy(setup_data_2.beet_name[i], "Beet");
        strcpy(setup_data_2.IP_sensor[i], "IP_sensor");
        strcpy(setup_data_2.IP_ventil[i], "IP_ventil");
        setup_data_2.stand_bew_zeit[i] = 45;
        setup_data_2.ventil_nr[i] = 1;
    }

    ESPUI.setVerbosity(Verbosity::VerboseJSON);

    uint16_t Allgemein = ESPUI.addControl(ControlType::Tab, language.name_tab_generally, String(language.name_tab_generally));

    uint16_t Beete = ESPUI.addControl(ControlType::Tab, language.name_tab_bed, String(language.name_tab_bed));

    if (login == 1)
    {
        ESPUI.addControl(ControlType::Label, language.login_header, String(language.login_description), ControlColor::Turquoise, Allgemein);
        id_init_2.login[0] = ESPUI.addControl(ControlType::Text, language.login_usr, String(setup_data_2.login[0]), ControlColor::Alizarin, Allgemein, &textCall_set_2);
        id_init_2.login[1] = ESPUI.addControl(ControlType::Text, language.login_psw, String(setup_data_2.login[1]), ControlColor::Alizarin, Allgemein, &textCall_set_2);
    };
    if (bew_typ == 3)
    {
        ESPUI.addControl(ControlType::Label, language.weather_data, String(language.weather_data_description), ControlColor::Turquoise, Allgemein);
        id_init_2.wetter[0] = ESPUI.addControl(ControlType::Text, language.weather_api, "011235813", ControlColor::Alizarin, Allgemein, &textCall_set_2);
        id_init_2.wetter[1] = ESPUI.addControl(ControlType::Text, language.weather_latitude, "52.516275", ControlColor::Alizarin, Allgemein, &textCall_set_2);
        id_init_2.wetter[2] = ESPUI.addControl(ControlType::Text, language.weather_longitude, "13.377704", ControlColor::Alizarin, Allgemein, &textCall_set_2);
    }
    if (login != 1 && bew_typ != 3)
    {
        ESPUI.addControl(ControlType::Label, language.nothing_for_you, String(language.nothing_for_you_description), ControlColor::Turquoise, Allgemein);
    }
    else
    {
        ESPUI.addControl(ControlType::Label, language.go_on, language.go_on_description, ControlColor::Turquoise, Allgemein);
    }
#if debugmode == 1
    dev_button_id = ESPUI.addControl(ControlType::Button, "Setup zurück setzen:", "Drücken", ControlColor::Wetasphalt, Allgemein, &buttonCallback_set_2);
#endif

    id_init_2.ausgew_beet_id = ESPUI.addControl(ControlType::Select, "Beet_Auswählen", "99", ControlColor::Turquoise, Beete, &select_set_2);
    const char *namen[20] = {"Beet 1", "Beet 2", "Beet 3", "Beet 4", "Beet 5", "Beet 6", "Beet 7", "Beet 8", "Beet 9", "Beet 10", "Beet 11", "Beet 12", "Beet 13", "Beet 14", "Beet 15", "Beet 16", "Beet 17", "Beet 18", "Beet 19", "Beet 20"};
    ESPUI.addControl(ControlType::Option, "bitte wählen sie ein Beet aus", "99", ControlColor::Alizarin, id_init_2.ausgew_beet_id);
    for (int i = 0; i < setup_data_1.anzahl_beete; i++)
    {
        ESPUI.addControl(ControlType::Option, namen[i], String(i), ControlColor::Alizarin, id_init_2.ausgew_beet_id);
    }
    id_init_2.id_beet.id_name = ESPUI.addControl(ControlType::Text, "Bitte gib den Namen dieses Beets an", "Das Krasseste Beet", ControlColor::Alizarin, Beete, &textCall_set_2);
    ESPUI.addControl(ControlType::Label, "info zu den IP eingaben", "Da der Code des Ventil Server bis zu 4 Relays pro ESP unterstützt, gib unter der Ip an, welches Relay du genutzt hast. falls du nur ein Relay von dem server nutzt wähle 1 aus. falls du mehrere nutzt, trage bei allen genutzten die selbe IP ein und wähle dann das passende Relay.", ControlColor::Turquoise, Beete);
    id_init_2.id_beet.id_ip_relay = ESPUI.addControl(ControlType::Text, "IP Relay", "192.168.178.10", ControlColor::Alizarin, Beete, &textCall_set_2);
    id_init_2.id_beet.id_ip_relay_nr = ESPUI.addControl(ControlType::Select, "genutztes Relay an Ventil server ESP", "", ControlColor::Alizarin, Beete, &select_set_2);
    ESPUI.addControl(ControlType::Option, "1", "1", ControlColor::Alizarin, id_init_2.id_beet.id_ip_relay_nr);
    ESPUI.addControl(ControlType::Option, "2", "2", ControlColor::Alizarin, id_init_2.id_beet.id_ip_relay_nr);
    ESPUI.addControl(ControlType::Option, "3", "3", ControlColor::Alizarin, id_init_2.id_beet.id_ip_relay_nr);
    ESPUI.addControl(ControlType::Option, "4", "4", ControlColor::Alizarin, id_init_2.id_beet.id_ip_relay_nr);
    if (bew_typ != 1)
    {
        ESPUI.addControl(ControlType::Label, "info zu Bewässerungszeit", "die Bewässerungszeit solltest du dir errechnen aus, bewässerungs leistung deines schlauchs und beetgröße, diese einstellung kannst du später noch ändern.", ControlColor::Turquoise, Beete);
        id_init_2.id_beet.id_ip_sensor = ESPUI.addControl(ControlType::Text, "IP Sensor ", "192.168.178.11", ControlColor::Alizarin, Beete, &textCall_set_2);
        id_init_2.id_beet.id_stand_bew_zeit = ESPUI.addControl(ControlType::Select, "Standart Bewässerungs zeit", "", ControlColor::Alizarin, Beete, &select_set_2);
        ESPUI.addControl(ControlType::Option, "15 min", "15", ControlColor::Alizarin, id_init_2.id_beet.id_stand_bew_zeit);
        ESPUI.addControl(ControlType::Option, "30 min", "30", ControlColor::Alizarin, id_init_2.id_beet.id_stand_bew_zeit);
        ESPUI.addControl(ControlType::Option, "45 min", "45", ControlColor::Alizarin, id_init_2.id_beet.id_stand_bew_zeit);
        ESPUI.addControl(ControlType::Option, "60 min", "60", ControlColor::Alizarin, id_init_2.id_beet.id_stand_bew_zeit);
        ESPUI.addControl(ControlType::Option, "75 min", "75", ControlColor::Alizarin, id_init_2.id_beet.id_stand_bew_zeit);
        ESPUI.addControl(ControlType::Option, "90 min", "90", ControlColor::Alizarin, id_init_2.id_beet.id_stand_bew_zeit);
        ESPUI.addControl(ControlType::Option, "105 min", "105", ControlColor::Alizarin, id_init_2.id_beet.id_stand_bew_zeit);
        ESPUI.addControl(ControlType::Option, "120 min", "120", ControlColor::Alizarin, id_init_2.id_beet.id_stand_bew_zeit);
    }

    id_init_2.absenden = ESPUI.addControl(ControlType::Button, "Angaben Bestätigen:", "Drücken", ControlColor::Wetasphalt, Beete, &buttonCallback_set_2);
    ESPUI.begin(setup_data_1.hostname);
};

setup_data2 server_setup::handle_setup_2()
{

    return setup_data_2;
};