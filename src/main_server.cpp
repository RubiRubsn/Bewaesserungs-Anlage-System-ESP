#include <DNSServer.h>
#include <ESPUI.h>

#if defined(ESP32)
#include <WiFi.h>
#include <AsyncTCP.h>
#else
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <string.h>
#include "setup/setup.h"
#include "main_server.h"
#include "save_load.h"
#include <Update.h>
#include "language.h"

int main_server::tabs[11] = {0};
int main_server::wetter_id[4] = {0};
einstellungen_id main_server::einst_id;

bool main_server::reset = false;
bool main_server::aktiviere_ota_update = false;
int main_server::allgemein[20];
setup_data1 main_server::update_data_1;
setup_data2 main_server::update_data_2;
Data_Beete main_server::data_beete[20];
data_einstellungen main_server::data_einst;

flaggs main_server::load_flaggs;
uint8_t main_server::ausgew_beet = 99;
uint8_t main_server::manuelle_bew_zeit[20];

const char *OTA_INDEX PROGMEM = R"=====(<!DOCTYPE html><html><head><meta charset=utf-8><title>OTA</title></head><body><div class="upload"><form method="POST" action="/ota" enctype="multipart/form-data"><input type="file" name="data" /><input type="submit" name="upload" value="Upload" title="Upload Files"></form></div></body></html>)=====";

void main_server::handleOTAUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
{
    if (!index)
    {
        Serial.printf("UploadStart: %s\n", filename.c_str());
        if (!Update.begin(UPDATE_SIZE_UNKNOWN))
        {
            Update.printError(Serial);
        }
    }

    if (len)
    {
        Update.write(data, len);
    }
    if (final)
    {
        if (Update.end(true))
        {
            Serial.printf("Update Success: %ub written\nRebooting...\n", index + len);
            ESPUI.jsonReload();
            delay(100);
            ESP.restart();
        }
        else
        {
            Update.printError(Serial);
        }
    }
};

void main_server::init_ota_update(setup_data1 update_data_1, setup_data2 update_data_2)
{
    ESPUI.server->on(
        "/ota", HTTP_POST, [&](AsyncWebServerRequest *request) {
            if (!aktiviere_ota_update)
            {
                return request->redirect("/");
            }
            else
            {
                request->send(200);
            }
        },
        handleOTAUpload);

    ESPUI.server->on("/ota", HTTP_GET, [&](AsyncWebServerRequest *request) {
        if (!aktiviere_ota_update)
        {
            return request->redirect("/");
        }
        else
        {
            AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", OTA_INDEX);
            request->send(response);
        }
    });
};

void main_server::update_data_ex(setup_data1 &setup_data_1, setup_data2 &setup_data_2)
{
    setup_data_1 = update_data_1;
    setup_data_2 = update_data_2;
    load_flaggs.update_data = false;
};

void main_server::update_beet_einst_text(setup_data1 &setup_data_1, setup_data2 &setup_data_2)
{
    if (einst_id.ausgew_beet != 99)
    {
        ESPUI.print(einst_id.Beete[1], String(setup_data_2.beet_name[einst_id.ausgew_beet]));
        ESPUI.print(einst_id.Beete[2], String(setup_data_2.IP_ventil[einst_id.ausgew_beet]));
        if (setup_data_1.bew_typ != 1)
        {
            ESPUI.print(einst_id.Beete[4], String(setup_data_2.IP_sensor[einst_id.ausgew_beet]));
            ESPUI.print(einst_id.Beete[5], String(setup_data_2.stand_bew_zeit[einst_id.ausgew_beet]));
        }
        ESPUI.print(einst_id.Beete[3], String(setup_data_2.ventil_nr[einst_id.ausgew_beet]));
    };
    load_flaggs.update_text = false;
};

void main_server::update_beet_ui()
{
    if (ausgew_beet != 99)
    {

        ESPUI.print(tabs[1], data_beete[ausgew_beet].ventil_zustand);

        if (update_data_1.bew_typ != 1)
        {
            if (data_beete[ausgew_beet].beet_feuchte[0] < 101)
            {
                char *text = new char[strlen("000") + strlen("%")];

                char help[3];
                itoa(data_beete[ausgew_beet].beet_feuchte[0], help, 10);
                strcpy(text, help);
                strcat(text, "%");
                ESPUI.print(tabs[2], String(text));
            }
            else
            {
                ESPUI.print(tabs[2], String("nicht erreichbar"));
            }

            uint16_t help = 0;
            uint8_t zaehler = 0;
            for (int i = 0; i < 24; i++)
            {
                if (data_beete[ausgew_beet].beet_feuchte[i] < 101)
                {
                    help = help + data_beete[ausgew_beet].beet_feuchte[i];
                    zaehler++;
                }
            }
            if (zaehler != 0)
            {
                char *text = new char[strlen("000") + strlen("%")];
                char help_char[3];
                int rechnung = (help / zaehler);
                itoa(rechnung, help_char, 10);
                strcpy(text, help_char);
                strcat(text, "%");
                ESPUI.print(tabs[3], String(text));
            }
            else
            {
                ESPUI.print(tabs[3], "keine Daten");
            }

            if (data_beete[ausgew_beet].auto_bew && !data_beete[ausgew_beet].bew_beendet)
            {
                String ausgabe = "geplant in:";
                ausgabe += String(wetter_data.h_bis_21);
                ausgabe += ":";
                ausgabe += String(wetter_data.min_bis_21);
                ausgabe += "h";
                ESPUI.print(tabs[4], ausgabe);
            }
            else
            {
                Serial.print("auto bew");
                Serial.println(data_beete[ausgew_beet].auto_bew);
                Serial.print("bew beendet: ");
                Serial.println(data_beete[ausgew_beet].bew_beendet);
                ESPUI.print(tabs[4], String("nicht geplant"));
            }
            if (data_beete[ausgew_beet].bew_geplant == true)
            {
                ESPUI.print(tabs[5], String("1"));
                //load_flaggs.save_data_beete = true;
            }
            else
            {
                ESPUI.print(tabs[5], String("0"));
                //load_flaggs.save_data_beete = true;
            }

            ESPUI.print(tabs[6], String(update_data_2.stand_bew_zeit[ausgew_beet]));
        }
    }
    //update allgemeine anzeige
    for (int i = 0; i < update_data_1.anzahl_beete; i++)
    {
        if (data_beete[i].beet_feuchte[0] < 101)
        {
            char *text = new char[strlen("000") + strlen("%")];
            char help[3];
            itoa(data_beete[i].beet_feuchte[0], help, 10);
            strcpy(text, help);
            strcat(text, "%");
            ESPUI.print(allgemein[i], String(text));
        }
        else
        {
            ESPUI.print(allgemein[i], String("nicht erreichbar"));
        }
    }

    load_flaggs.update_UI = false;
};

void main_server::update_wetter_ui()
{
    Serial.println("reload wetter ui");
    ESPUI.print(wetter_id[1], wetter_klassifizierung(wetter_data.aktuell.id));
    ESPUI.print(wetter_id[2], wetter_klassifizierung(wetter_data.voraus[1].id));
};

void main_server::sliderCallback(Control *sender, int type)
{
    if (sender->id == einst_id.Allgemein[13])
    {
        data_einst.min_feuchte = sender->value.toInt();
    };
}

void main_server::switchCallback(Control *sender, int value)
{
    if (sender->id == einst_id.Allgemein[19])
    {
        switch (value)
        {
        case S_ACTIVE:
            aktiviere_ota_update = true;
            break;

        case S_INACTIVE:
            aktiviere_ota_update = false;
            break;
        }
    }
    if (sender->id == einst_id.Allgemein[3])
    {
        switch (value)
        {
        case S_ACTIVE:
            update_data_1.login = 1;
            break;

        case S_INACTIVE:
            update_data_1.login = 0;
            break;
        }
    }
    if (sender->id == tabs[5])
    {
        switch (value)
        {
        case S_ACTIVE:
            data_beete[ausgew_beet].bew_geplant = true;
            break;

        case S_INACTIVE:
            data_beete[ausgew_beet].bew_geplant = false;
            break;
        }
        load_flaggs.save_data_beete = true;
    }
    Serial.print(" ");
    Serial.println(sender->id);
}

void main_server::selectCallback(Control *sender, int value)
{
    Serial.print("Select: ID: ");
    Serial.print(sender->id);
    Serial.print(", Value: ");
    Serial.println(sender->value);
    //Beet einstellungen
    if (sender->id == einst_id.Beete[0] || sender->id == einst_id.Allgemein[12] || sender->id == einst_id.Allgemein[2] || sender->id == tabs[10] || sender->id == einst_id.Allgemein[14])
    {
        if (sender->value == "0")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 0;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 0;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 1;
            }
            else if (sender->id == einst_id.Allgemein[12])
            {
                data_einst.farb_id = 0;
                data_einst.farbe = Turquoise;
            }
            else if (sender->id == einst_id.Allgemein[14])
            {
                data_einst.min_regen_id = 0;
            }
        };
        if (sender->value == "1")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 1;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 1;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 2;
            }
            else if (sender->id == einst_id.Allgemein[12])
            {
                data_einst.farb_id = 1;
                data_einst.farbe = Emerald;
            }
            else if (sender->id == einst_id.Allgemein[14])
            {
                data_einst.min_regen_id = 1;
            }
        };
        if (sender->value == "2")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 2;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 2;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 3;
            }
            else if (sender->id == einst_id.Allgemein[12])
            {
                data_einst.farb_id = 2;
                data_einst.farbe = Peterriver;
            }
            else if (sender->id == einst_id.Allgemein[14])
            {
                data_einst.min_regen_id = 2;
            }
        };
        if (sender->value == "3")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 3;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 3;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 4;
            }
            else if (sender->id == einst_id.Allgemein[12])
            {
                data_einst.farb_id = 3;
                data_einst.farbe = Wetasphalt;
            }
        };
        if (sender->value == "4")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 4;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 4;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 5;
            }
            else if (sender->id == einst_id.Allgemein[12])
            {
                data_einst.farb_id = 4;
                data_einst.farbe = Sunflower;
            }
        };
        if (sender->value == "5")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 5;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 5;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 6;
            }
            else if (sender->id == einst_id.Allgemein[12])
            {
                data_einst.farb_id = 5;
                data_einst.farbe = Carrot;
            }
        };
        if (sender->value == "6")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 6;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 6;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 7;
            }
            else if (sender->id == einst_id.Allgemein[12])
            {
                data_einst.farb_id = 6;
                data_einst.farbe = Alizarin;
            }
        };
        if (sender->value == "7")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 7;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 7;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 8;
            }
            else if (sender->id == einst_id.Allgemein[12])
            {
                data_einst.farb_id = 7;
                data_einst.farbe = Dark;
            }
        };
        if (sender->value == "8")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 8;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 8;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 9;
            }
            else if (sender->id == einst_id.Allgemein[12])
            {
                data_einst.farb_id = 8;
                data_einst.farbe = None;
            }
        };
        if (sender->value == "9")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 9;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 9;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 10;
            }
        };
        if (sender->value == "10")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 10;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 10;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 11;
            }
        };
        if (sender->value == "11")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 11;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 11;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 12;
            }
        };
        if (sender->value == "12")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 12;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 12;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 13;
            }
        };
        if (sender->value == "13")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 13;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 13;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 14;
            }
        };
        if (sender->value == "14")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 14;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 14;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 15;
            }
        };
        if (sender->value == "15")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 15;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 15;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 16;
            }
        };
        if (sender->value == "16")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 16;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 16;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 17;
            }
        };
        if (sender->value == "17")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 17;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 17;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 18;
            }
        };
        if (sender->value == "18")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 18;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 18;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                update_data_1.anzahl_beete = 19;
            }
        };
        if (sender->value == "19")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 19;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 19;
            }
            else if (sender->id == einst_id.Allgemein[2])
            {
                Serial.println("anzahl beete geändert");
                update_data_1.anzahl_beete = 20;
            }
        };
        if (sender->value == "99")
        {
            if (sender->id == tabs[10])
            {
                ausgew_beet = 99;
            }
            else if (sender->id == einst_id.Beete[0])
            {
                einst_id.ausgew_beet = 99;
            }
        };

        if (sender->id == tabs[10])
        {
            load_flaggs.update_UI = true;
        }
        else
        {
            load_flaggs.update_text = true;
        }
    }
    if (sender->id == einst_id.Beete[5] && einst_id.ausgew_beet != 99 && update_data_1.bew_typ != 1)
    {
        if (sender->value == String("15"))
        {
            update_data_2.stand_bew_zeit[einst_id.ausgew_beet] = 15;
        };
        if (sender->value == String("30"))
        {
            update_data_2.stand_bew_zeit[einst_id.ausgew_beet] = 30;
        };
        if (sender->value == String("45"))
        {
            update_data_2.stand_bew_zeit[einst_id.ausgew_beet] = 45;
        };
        if (sender->value == String("60"))
        {
            update_data_2.stand_bew_zeit[einst_id.ausgew_beet] = 60;
        };
        if (sender->value == String("75"))
        {
            update_data_2.stand_bew_zeit[einst_id.ausgew_beet] = 75;
        };
        if (sender->value == String("90"))
        {
            update_data_2.stand_bew_zeit[einst_id.ausgew_beet] = 90;
        };
        if (sender->value == String("105"))
        {
            update_data_2.stand_bew_zeit[einst_id.ausgew_beet] = 105;
        };
        if (sender->value == String("120"))
        {
            update_data_2.stand_bew_zeit[einst_id.ausgew_beet] = 120;
        };
        load_flaggs.update_data = true;
    }
    if (sender->id == einst_id.Beete[3] && einst_id.ausgew_beet != 99)
    {
        if (sender->value == String("1"))
        {
            update_data_2.ventil_nr[einst_id.ausgew_beet] = 1;
        };
        if (sender->value == String("2"))
        {
            update_data_2.ventil_nr[einst_id.ausgew_beet] = 2;
        };
        if (sender->value == String("3"))
        {
            update_data_2.ventil_nr[einst_id.ausgew_beet] = 3;
        };
        if (sender->value == String("4"))
        {
            update_data_2.ventil_nr[einst_id.ausgew_beet] = 4;
        };
        load_flaggs.update_data = true;
    }
    //Algemeine einstellungen
    if (sender->id == einst_id.Allgemein[1])
    {
        if (sender->value == "1")
        {
            update_data_1.bew_typ = 1;
        }
        if (sender->value == "2")
        {
            update_data_1.bew_typ = 2;
        }
        if (sender->value == "3")
        {
            update_data_1.bew_typ = 3;
        }
    }
    if (sender->id == tabs[6])
    {
        if (sender->value == String("15"))
        {
            manuelle_bew_zeit[ausgew_beet] = 15;
        };
        if (sender->value == String("30"))
        {
            manuelle_bew_zeit[ausgew_beet] = 30;
        };
        if (sender->value == String("45"))
        {
            manuelle_bew_zeit[ausgew_beet] = 45;
        };
        if (sender->value == String("60"))
        {
            manuelle_bew_zeit[ausgew_beet] = 60;
        };
        if (sender->value == String("75"))
        {
            manuelle_bew_zeit[ausgew_beet] = 75;
        };
        if (sender->value == String("90"))
        {
            manuelle_bew_zeit[ausgew_beet] = 90;
        };
        if (sender->value == String("105"))
        {
            manuelle_bew_zeit[ausgew_beet] = 105;
        };
        if (sender->value == String("120"))
        {
            manuelle_bew_zeit[ausgew_beet] = 120;
        };
    }
}

void main_server::textCallback(Control *sender, int type)
{
    if (sender->id == einst_id.Beete[1] && einst_id.ausgew_beet != 99)
    {
        strcpy(update_data_2.beet_name[einst_id.ausgew_beet], sender->value.c_str());
        load_flaggs.update_data = true;
    };
    if (sender->id == einst_id.Beete[2] && einst_id.ausgew_beet != 99)
    {
        strcpy(update_data_2.IP_ventil[einst_id.ausgew_beet], sender->value.c_str());
        load_flaggs.update_data = true;
    };
    if (sender->id == einst_id.Beete[4] && einst_id.ausgew_beet != 99 && update_data_1.bew_typ != 1)
    {
        strcpy(update_data_2.IP_sensor[einst_id.ausgew_beet], sender->value.c_str());
        load_flaggs.update_data = true;
    };
    if (sender->id == einst_id.Allgemein[4])
    {
        strcpy(update_data_2.login[0], sender->value.c_str());
    }
    if (sender->id == einst_id.Allgemein[5])
    {
        strcpy(update_data_2.login[1], sender->value.c_str());
    }
    if (sender->id == einst_id.Allgemein[6])
    {
        strcpy(update_data_2.wetter[0], sender->value.c_str());
    }
    if (sender->id == einst_id.Allgemein[7])
    {
        strcpy(update_data_2.wetter[1], sender->value.c_str());
    }
    if (sender->id == einst_id.Allgemein[8])
    {
        strcpy(update_data_2.wetter[2], sender->value.c_str());
    }
    if (sender->id == einst_id.Allgemein[16])
    {
        strcpy(update_data_1.hostname, sender->value.c_str());
    }
    if (sender->id == einst_id.Allgemein[17])
    {
        strcpy(update_data_1.ssid, sender->value.c_str());
    }
    if (sender->id == einst_id.Allgemein[18])
    {
        strcpy(update_data_1.password, sender->value.c_str());
    }
    if (sender->id == einst_id.Allgemein[15])
    {
        if (sender->value == "ZURÜCKSETZEN")
        {
            Serial.println("ZURÜCKSETZEN");
            reset = true;
        }
        else
        {
            reset = false;
        }
    }
}

void main_server::buttonCallback(Control *sender, int type)
{

    if (sender->id == einst_id.Allgemein[10] || sender->id == einst_id.Allgemein[11])
    {
        switch (type)
        {
        case B_DOWN:
            load_flaggs.save_data = true;
            break;
        }
    }
    if (sender->id == einst_id.Allgemein[9])
    {
        switch (type)
        {
        case B_DOWN:
            if (reset == true)
            {
                load_flaggs.reset_data = true;
            }
            break;
        }
    }
    if (sender->id == wetter_id[3])
    {
        switch (type)
        {
        case B_DOWN:
            load_flaggs.reload_wetter = true;
            break;
        }
    }
    if (sender->id == tabs[7])
    {
        switch (type)
        {
        case B_DOWN:
            char zeit[3];
            itoa(manuelle_bew_zeit[ausgew_beet], zeit, 10);
            set_ventil(ausgew_beet, zeit);
            load_flaggs.update_UI = true;
            break;
        }
    }
    if (sender->id == tabs[8])
    {
        switch (type)
        {
        case B_DOWN:
            stop_ventil(ausgew_beet);
            load_flaggs.update_UI = true;
            break;
        }
    }
    if (sender->id == tabs[9])
    {
        switch (type)
        {
        case B_DOWN:
            load_flaggs.update_UI = true;
            break;
        }
    }
}

void main_server::init_server(setup_data1 &setup_data_1, setup_data2 &setup_data_2)
{
    lang_main_server language;
    update_data_1 = setup_data_1;
    update_data_2 = setup_data_2;
    for (int i = 0; i < 20; i++)
    {
        manuelle_bew_zeit[i] = update_data_2.stand_bew_zeit[i];
    }

    save_load save_load;
    save_load.load_data_einst(data_einst);
    Serial.println(setup_data_2.login[0]);
    Serial.println(update_data_2.login[1]);
    ESPUI.setVerbosity(Verbosity::VerboseJSON);
    wetter_id[0] = ESPUI.addControl(ControlType::Tab, language.name_tab_general, String(language.name_tab_general));
    if (setup_data_1.bew_typ == 3)
    {
        wetter_id[1] = ESPUI.addControl(ControlType::Label, language.current_weather, String(language.currently_not_available), data_einst.farbe, wetter_id[0]);
        wetter_id[2] = ESPUI.addControl(ControlType::Label, language.weather_tomorrow, String(language.currently_not_available), data_einst.farbe, wetter_id[0]);
    }
    for (int i = 0; i < update_data_1.anzahl_beete; i++)
    {
        char *titel = new char[strlen(language.moisture_in_bed) + strlen(update_data_2.beet_name[i]) + strlen(":")];
        strcpy(titel, language.moisture_in_bed);
        strcat(titel, update_data_2.beet_name[i]);
        strcat(titel, ":");
        allgemein[i] = ESPUI.addControl(ControlType::Label, titel, String(language.currently_not_available), data_einst.farbe, wetter_id[0]);
    }
    if (setup_data_1.bew_typ == 3)
    {
        wetter_id[3] = ESPUI.addControl(ControlType::Button, language.reload, String(language.press), data_einst.farbe, wetter_id[0], &buttonCallback);
    }
    tabs[0] = ESPUI.addControl(ControlType::Tab, language.name_tab_bed, String(language.name_tab_bed));
    tabs[10] = ESPUI.addControl(ControlType::Select, language.choose_bed, "99", data_einst.farbe, tabs[0], &selectCallback);
    ESPUI.addControl(ControlType::Option, language.please_choose_bed, "99", data_einst.farbe, tabs[10]);
    for (int i = 0; i < setup_data_1.anzahl_beete; i++)
    {
        const char *name = setup_data_2.beet_name[i];
        ESPUI.addControl(ControlType::Option, name, String(i), data_einst.farbe, tabs[10]);
    }

    tabs[1] = ESPUI.addControl(ControlType::Label, language.valve_condition, String(language.currently_not_available), data_einst.farbe, tabs[0]);
    if (setup_data_1.bew_typ != 1)
    {
        tabs[2] = ESPUI.addControl(ControlType::Label, language.current_moisture, String(language.currently_not_available), data_einst.farbe, tabs[0]);
        tabs[3] = ESPUI.addControl(ControlType::Label, language.average_moisture, String(language.currently_not_available), data_einst.farbe, tabs[0]);
        tabs[4] = ESPUI.addControl(ControlType::Label, language.planed_irrigation, String(language.not_planed), data_einst.farbe, tabs[0]);
        tabs[5] = ESPUI.addControl(ControlType::Switcher, language.do_planed_irrigation, "", data_einst.farbe, tabs[0], &switchCallback);
    };

    tabs[6] = ESPUI.addControl(ControlType::Select, language.time_for_manual_irrigation, "", data_einst.farbe, tabs[0], &selectCallback);
    ESPUI.addControl(ControlType::Option, "15 min", "15", data_einst.farbe, tabs[6]);
    ESPUI.addControl(ControlType::Option, "30 min", "30", data_einst.farbe, tabs[6]);
    ESPUI.addControl(ControlType::Option, "45 min", "45", data_einst.farbe, tabs[6]);
    ESPUI.addControl(ControlType::Option, "60 min", "60", data_einst.farbe, tabs[6]);
    ESPUI.addControl(ControlType::Option, "75 min", "75", data_einst.farbe, tabs[6]);
    ESPUI.addControl(ControlType::Option, "90 min", "90", data_einst.farbe, tabs[6]);
    ESPUI.addControl(ControlType::Option, "105 min", "105", data_einst.farbe, tabs[6]);
    ESPUI.addControl(ControlType::Option, "120 min", "120", data_einst.farbe, tabs[6]);
    tabs[7] = ESPUI.addControl(ControlType::Button, language.start_manual_irrigation, String(language.press), data_einst.farbe, tabs[0], &buttonCallback);
    tabs[8] = ESPUI.addControl(ControlType::Button, language.stop_irrigation, String(language.press), data_einst.farbe, tabs[0], &buttonCallback);
    tabs[9] = ESPUI.addControl(ControlType::Button, language.reload, String(language.press), data_einst.farbe, tabs[0], &buttonCallback);

    einst_id.Allgemein[0] = ESPUI.addControl(ControlType::Tab, language.name_tab_general_settings, String(language.name_tab_general_settings), data_einst.farbe, einst_id.einst_tab_id);
    einst_id.Allgemein[1] = ESPUI.addControl(ControlType::Select, language.irrigation_type, String(update_data_1.bew_typ), data_einst.farbe, einst_id.Allgemein[0], &selectCallback);
    ESPUI.addControl(ControlType::Option, language.irrigation_manuel, "1", data_einst.farbe, einst_id.Allgemein[1]);
    ESPUI.addControl(ControlType::Option, language.irrigation_moist, "2", data_einst.farbe, einst_id.Allgemein[1]);
    ESPUI.addControl(ControlType::Option, language.irrigation_moist_weather, "3", data_einst.farbe, einst_id.Allgemein[1]);
    einst_id.Allgemein[2] = ESPUI.addControl(ControlType::Select, language.number_of_bed, String(update_data_1.anzahl_beete - 1), data_einst.farbe, einst_id.Allgemein[0], &selectCallback);
    ESPUI.addControl(ControlType::Option, "1", "0", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "2", "1", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "3", "2", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "4", "3", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "5", "4", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "6", "5", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "7", "6", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "8", "7", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "9", "8", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "10", "9", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "11", "10", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "12", "11", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "13", "12", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "14", "13", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "15", "14", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "16", "15", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "17", "16", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "18", "17", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "19", "18", data_einst.farbe, einst_id.Allgemein[2]);
    ESPUI.addControl(ControlType::Option, "20", "19", data_einst.farbe, einst_id.Allgemein[2]);
    einst_id.Allgemein[16] = ESPUI.addControl(ControlType::Text, language.name_of_system, String(update_data_1.hostname), data_einst.farbe, einst_id.Allgemein[0], &textCallback);
    einst_id.Allgemein[3] = ESPUI.addControl(ControlType::Switcher, language.secure_ui_with_login, String(update_data_1.login), data_einst.farbe, einst_id.Allgemein[0], &switchCallback);
    einst_id.Allgemein[4] = ESPUI.addControl(ControlType::Text, language.login_usr, String(update_data_2.login[0]), data_einst.farbe, einst_id.Allgemein[0], &textCallback);
    einst_id.Allgemein[5] = ESPUI.addControl(ControlType::Text, language.login_psw, String(update_data_2.login[1]), data_einst.farbe, einst_id.Allgemein[0], &textCallback);
    einst_id.Allgemein[17] = ESPUI.addControl(ControlType::Text, language.SSID, String(update_data_1.ssid), data_einst.farbe, einst_id.Allgemein[0], &textCallback);
    einst_id.Allgemein[18] = ESPUI.addControl(ControlType::Text, language.psw, String(update_data_1.password), data_einst.farbe, einst_id.Allgemein[0], &textCallback);
    einst_id.Allgemein[6] = ESPUI.addControl(ControlType::Text, language.weather_api, String(update_data_2.wetter[0]), data_einst.farbe, einst_id.Allgemein[0], &textCallback);
    einst_id.Allgemein[7] = ESPUI.addControl(ControlType::Text, language.weather_latitude, String(update_data_2.wetter[1]), data_einst.farbe, einst_id.Allgemein[0], &textCallback);
    einst_id.Allgemein[8] = ESPUI.addControl(ControlType::Text, language.weather_longitude, String(update_data_2.wetter[2]), data_einst.farbe, einst_id.Allgemein[0], &textCallback);
    einst_id.Allgemein[12] = ESPUI.addControl(ControlType::Select, language.color, String(data_einst.farb_id), data_einst.farbe, einst_id.Allgemein[0], &selectCallback);
    ESPUI.addControl(ControlType::Option, "Türkis", "0", data_einst.farbe, einst_id.Allgemein[12]);
    ESPUI.addControl(ControlType::Option, "Emerald (Grün)", "1", data_einst.farbe, einst_id.Allgemein[12]);
    ESPUI.addControl(ControlType::Option, "Peterriver (Blau)", "2", data_einst.farbe, einst_id.Allgemein[12]);
    ESPUI.addControl(ControlType::Option, "Nasser Asphalt (dunkles Blau)", "3", data_einst.farbe, einst_id.Allgemein[12]);
    ESPUI.addControl(ControlType::Option, "Sonnenblume (Gelb)", "4", data_einst.farbe, einst_id.Allgemein[12]);
    ESPUI.addControl(ControlType::Option, "Karotte (Orange)", "5", data_einst.farbe, einst_id.Allgemein[12]);
    ESPUI.addControl(ControlType::Option, "Alizerin (starkes Rot)", "6", data_einst.farbe, einst_id.Allgemein[12]);
    ESPUI.addControl(ControlType::Option, "Dunkel", "7", data_einst.farbe, einst_id.Allgemein[12]);
    ESPUI.addControl(ControlType::Option, "Keine", "8", data_einst.farbe, einst_id.Allgemein[12]);
    ESPUI.addControl(ControlType::Label, language.plan_irrigation_info, String(language.plan_irrigation_info_description), data_einst.farbe, einst_id.Allgemein[0]);
    einst_id.Allgemein[13] = ESPUI.addControl(ControlType::Slider, language.moisture_under, String(data_einst.min_feuchte), data_einst.farbe, einst_id.Allgemein[0], &sliderCallback);
    einst_id.Allgemein[14] = ESPUI.addControl(ControlType::Select, language.rain_over, String(data_einst.min_regen_id), data_einst.farbe, einst_id.Allgemein[0], &selectCallback);
    ESPUI.addControl(ControlType::Option, language.light, "0", data_einst.farbe, einst_id.Allgemein[14]);
    ESPUI.addControl(ControlType::Option, language.moderate, "1", data_einst.farbe, einst_id.Allgemein[14]);
    ESPUI.addControl(ControlType::Option, language.heavy, "2", data_einst.farbe, einst_id.Allgemein[14]);
    einst_id.Allgemein[15] = ESPUI.addControl(ControlType::Text, language.reset_info, String(language.reset_info_description), data_einst.farbe, einst_id.Allgemein[0], &textCallback);
    einst_id.Allgemein[9] = ESPUI.addControl(ControlType::Button, language.reset_server, String(language.press), data_einst.farbe, einst_id.Allgemein[0], &buttonCallback);
    ESPUI.addControl(ControlType::Label, language.software_version, String(update_data_1.versions_nr), data_einst.farbe, einst_id.Allgemein[0], &textCallback);
    einst_id.Allgemein[19] = ESPUI.addControl(ControlType::Switcher, language.activate_ota_update, String("0"), data_einst.farbe, einst_id.Allgemein[0], &switchCallback);
    einst_id.beete_einst_tab_id = ESPUI.addControl(ControlType::Tab, language.name_tab_bed_settings, String(language.name_tab_bed_settings));
    einst_id.Beete[0] = ESPUI.addControl(ControlType::Select, language.choose_bed, "99", data_einst.farbe, einst_id.beete_einst_tab_id, &selectCallback);
    ESPUI.addControl(ControlType::Option, language.please_choose_bed, "99", data_einst.farbe, einst_id.Beete[0]);
    for (int i = 0; i < setup_data_1.anzahl_beete; i++)
    {
        ESPUI.addControl(ControlType::Option, setup_data_2.beet_name[i], String(i), data_einst.farbe, einst_id.Beete[0]);
    }
    einst_id.Beete[1] = ESPUI.addControl(ControlType::Text, language.name_of_bed, "Beeter Call me", data_einst.farbe, einst_id.beete_einst_tab_id, &textCallback);
    einst_id.Beete[2] = ESPUI.addControl(ControlType::Text, language.IP_relay, "192.168.178.10", data_einst.farbe, einst_id.beete_einst_tab_id, &textCallback);
    einst_id.Beete[3] = ESPUI.addControl(ControlType::Select, language.used_relay, "", data_einst.farbe, einst_id.beete_einst_tab_id, &selectCallback);
    ESPUI.addControl(ControlType::Option, "1", "1", data_einst.farbe, einst_id.Beete[3]);
    ESPUI.addControl(ControlType::Option, "2", "2", data_einst.farbe, einst_id.Beete[3]);
    ESPUI.addControl(ControlType::Option, "3", "3", data_einst.farbe, einst_id.Beete[3]);
    ESPUI.addControl(ControlType::Option, "4", "4", data_einst.farbe, einst_id.Beete[3]);
    if (setup_data_1.bew_typ != 1)
    {
        einst_id.Beete[4] = ESPUI.addControl(ControlType::Text, language.IP_sensor, "192.168.178.11", data_einst.farbe, einst_id.beete_einst_tab_id, &textCallback);
        einst_id.Beete[5] = ESPUI.addControl(ControlType::Select, language.default_irrigation_time, "", data_einst.farbe, einst_id.beete_einst_tab_id, &selectCallback);
        ESPUI.addControl(ControlType::Option, "15 min", "15", data_einst.farbe, einst_id.Beete[5]);
        ESPUI.addControl(ControlType::Option, "30 min", "30", data_einst.farbe, einst_id.Beete[5]);
        ESPUI.addControl(ControlType::Option, "45 min", "45", data_einst.farbe, einst_id.Beete[5]);
        ESPUI.addControl(ControlType::Option, "60 min", "60", data_einst.farbe, einst_id.Beete[5]);
        ESPUI.addControl(ControlType::Option, "75 min", "75", data_einst.farbe, einst_id.Beete[5]);
        ESPUI.addControl(ControlType::Option, "90 min", "90", data_einst.farbe, einst_id.Beete[5]);
        ESPUI.addControl(ControlType::Option, "105 min", "105", data_einst.farbe, einst_id.Beete[5]);
        ESPUI.addControl(ControlType::Option, "120 min", "120", data_einst.farbe, einst_id.Beete[5]);
    }

    einst_id.Allgemein[10] = ESPUI.addControl(ControlType::Button, language.save, String(language.press), data_einst.farbe, einst_id.Allgemein[0], &buttonCallback);
    einst_id.Allgemein[11] = ESPUI.addControl(ControlType::Button, language.save, String(language.press), data_einst.farbe, einst_id.beete_einst_tab_id, &buttonCallback);

    if (setup_data_1.login == 1)
    {
        const char *hostname = setup_data_1.hostname;
        const char *usr = setup_data_2.login[0];
        const char *pw = setup_data_2.login[1];
        ESPUI.begin(hostname, usr, pw);
    }
    else
    {
        const char *hostname = setup_data_1.hostname;
        ESPUI.begin(hostname);
    }
    if (setup_data_1.bew_typ == 3)
    {
        load_flaggs.reload_wetter = true;
    };
    save_load.load_data_beete(data_beete);

    ESPUI.print(tabs[10], "0");
    ausgew_beet = 0;
    load_flaggs.update_UI = true;
    init_ota_update(update_data_1, update_data_2);
}

bool main_server::flaggs_abfragen(setup_data1 &setup_data_1, setup_data2 &setup_data_2)
{
    if (load_flaggs.update_text)
    {
        Serial.println("Lade Beet Einstellungs text neu");
        update_beet_einst_text(setup_data_1, setup_data_2);
    };
    if (load_flaggs.update_data)
    {
        Serial.println("sichere update data in setup_data ");
        update_data_ex(setup_data_1, setup_data_2);
    }
    if (load_flaggs.update_UI)
    {
        Serial.println("Lade Beet UI neu");
        abfrage_ventil();
        update_beet_ui();
    }
    if (load_flaggs.reload_wetter)
    {
        Serial.println("frage wetter ab");
        wetter_data = abfrage_wetter(update_data_2.wetter[1], update_data_2.wetter[2], update_data_2.wetter[0]);
        update_wetter_ui();
    }
    if (load_flaggs.save_data_beete)
    {
        save_load save_load;
        save_load.save_data_beete(data_beete);
        load_flaggs.save_data_beete = false;
    }
    if (load_flaggs.reset_data)
    {
        strcpy(setup_data_1.ssid, "undefined");
        setup_data_1.login = 0;
        setup_data_2.setup_zust = 1;
        delay(10);
        return (false);
    }
    if (load_flaggs.save_data)
    {
        delay(10);
        update_data_ex(setup_data_1, setup_data_2);
        save_load save_load;
        save_load.save_data_einst(data_einst);
        ESPUI.jsonReload();
        return (false);
    }
    return true;
};

bool main_server::handle_server(setup_data1 &setup_data_1, setup_data2 &setup_data_2)
{
    reset_var_check();
    if (refresh_timer_sensoren())
    {
        abfrage_sensoren();
        save_load save_load;
        save_load.save_data_beete(data_beete);
        load_flaggs.reload_wetter = true;
        load_flaggs.update_UI = true;
    };
    if (refresh_timer())
    {
        wetter_data = abfrage_wetter(update_data_2.wetter[1], update_data_2.wetter[2], update_data_2.wetter[0]);
        update_wetter_ui();
        berechnung_bewaesserung();
        load_flaggs.update_UI = true;
    }
    return flaggs_abfragen(setup_data_1, setup_data_2);
}
