#include <Arduino.h>
#include "setup/setup.h"
#include "main_server.h"
#include "save_load.h"
#include <EEPROM.h>

#define ausgabe_serial 0

void save_load::init_eeprom()
{
    adress_register adress_register;
    EEPROM.begin(adress_register.ende);
}

void save_load::Save_1(char ssid[], char pw[], char hostname[], uint8_t anz_beete, uint8_t bew_typ, uint8_t login)
{
    adress_register adress_register;
    // nächster setup zustand:
    EEPROM.write(adress_register.setup_zust, 2);
    //save ssid
    for (int i = 0; i < 40; i++)
    {
        EEPROM.write(adress_register.ssid + i, ssid[i]);
    };
    for (int i = 0; i < 40; i++)
    {
        EEPROM.write(adress_register.psw + i, pw[i]);
    };
    for (int i = 0; i < 40; i++)
    {
        EEPROM.write(adress_register.hostname + i, hostname[i]);
    };
    EEPROM.write(adress_register.anz_beete, anz_beete);
    EEPROM.write(adress_register.bew_typ, bew_typ);
    EEPROM.write(adress_register.login, login);

    //schreibe an leerstellen um bugs zu vermeiden
    EEPROM.commit();
};

void save_load::Load_1(uint8_t &setup_zust, char ssid[], char pw[], char hostname[], uint8_t &anz_beete, uint8_t &bew_typ, uint8_t &login)
{
    adress_register adress_register;
    setup_zust = EEPROM.read(adress_register.setup_zust);
#if ausgabe_serial == 1
    Serial.print("setup_zust: ");
    Serial.println(setup_zust);
#endif
    for (int i = 0; i < 40; i++)
    {
        ssid[i] = EEPROM.read(adress_register.ssid + i);
    };
#if ausgabe_serial == 1
    Serial.print("ssid: ");
    Serial.println(ssid);
#endif
    for (int i = 0; i < 40; i++)
    {
        pw[i] = EEPROM.read(adress_register.psw + i);
    };
#if ausgabe_serial == 1
    Serial.print("pw: ");
    Serial.println(pw);
#endif
    for (int i = 0; i < 40; i++)
    {
        hostname[i] = EEPROM.read(adress_register.hostname + i);
    };
#if ausgabe_serial == 1
    Serial.print("hostname: ");
    Serial.println(hostname);
#endif
    anz_beete = EEPROM.read(adress_register.anz_beete);
#if ausgabe_serial == 1
    Serial.print("anz_beete: ");
    Serial.println(anz_beete);
#endif
    bew_typ = EEPROM.read(adress_register.bew_typ);
#if ausgabe_serial == 1
    Serial.print("bew_typ: ");
    Serial.println(bew_typ);
#endif
    login = EEPROM.read(adress_register.login);
#if ausgabe_serial == 1
    Serial.print("login: ");
    Serial.println(login);
#endif
};

void save_load::Save_2(setup_data2 setup_data_2)
{
    adress_register adress_register;
    // nächster setup zustand:
    Serial.print("IP_relay:");
    Serial.println(setup_data_2.IP_ventil[0]);
    EEPROM.write(adress_register.setup_zust, setup_data_2.setup_zust);
    //save login
    for (int i = 0; i < 40; i++)
    {
        EEPROM.write(adress_register.login_usr + i, setup_data_2.login[0][i]);
    };
    for (int i = 0; i < 40; i++)
    {
        EEPROM.write(adress_register.login_psw + i, setup_data_2.login[1][i]);
    };
    //save wetter
    for (int a = 0; a < 3; a++)
    {
        for (int i = 0; i < 40; i++)
        {
            EEPROM.write(adress_register.wetter[a] + i, setup_data_2.wetter[a][i]);
        };
    };
    //save beet name
    for (int a = 0; a < 20; a++)
    {
        for (int i = 0; i < 40; i++)
        {
            EEPROM.write(adress_register.beet_name + i + a * 40, setup_data_2.beet_name[a][i]);
        };
    };
    //save IP_ventil
    for (int a = 0; a < 20; a++)
    {

        for (int i = 0; i < 40; i++)
        {
            EEPROM.write(adress_register.IP_ventil + i + a * 40, setup_data_2.IP_ventil[a][i]);
            if (setup_data_2.IP_ventil[a][i] == 0)
            {
                Serial.println(i);
                break;
            }
        };
    };
    //save IP_sensor
    for (int a = 0; a < 20; a++)
    {
        for (int i = 0; i < 40; i++)
        {
            EEPROM.write(adress_register.IP_sensor + i + a * 40, setup_data_2.IP_sensor[a][i]);
        };
    };
    //save ventil_nr
    for (int i = 0; i < 20; i++)
    {
        EEPROM.write(adress_register.ventil_nr + i, setup_data_2.ventil_nr[i]);
    };
    //save stand_bew_zeit
    for (int i = 0; i < 20; i++)
    {
        EEPROM.write(adress_register.stand_bew_zeit + i, setup_data_2.stand_bew_zeit[i]);
    };
    EEPROM.commit();
};

void save_load::Load_2(setup_data2 &setup_data_2)
{
    adress_register adress_register;

    setup_data_2.setup_zust = EEPROM.read(adress_register.setup_zust);
#if ausgabe_serial == 1
    Serial.print("setup_zust: ");
    Serial.println(setup_data_2.setup_zust);
#endif
    //load login
    for (int i = 0; i < 40; i++)
    {
        setup_data_2.login[0][i] = EEPROM.read(adress_register.login_usr + i);
    };
#if ausgabe_serial == 1
    Serial.print("Login usr: ");
    Serial.println(setup_data_2.login[0]);
#endif
    for (int i = 0; i < 40; i++)
    {
        setup_data_2.login[1][i] = EEPROM.read(adress_register.login_psw + i);
    };
#if ausgabe_serial == 1
    Serial.print("Login psw: ");
    Serial.println(setup_data_2.login[1]);
#endif
    //load wetter
    for (int a = 0; a < 3; a++)
    {
        for (int i = 0; i < 40; i++)
        {
            setup_data_2.wetter[a][i] = EEPROM.read(adress_register.wetter[a] + i);
        };
#if ausgabe_serial == 1
        Serial.print("wetter ");
        Serial.print(a);
        Serial.print(": ");
        Serial.println(setup_data_2.wetter[a]);
#endif
    };
    //load beet name
    for (int a = 0; a < 20; a++)
    {
        for (int i = 0; i < 40; i++)
        {
            setup_data_2.beet_name[a][i] = EEPROM.read(adress_register.beet_name + i + a * 40);
        };
#if ausgabe_serial == 1
        Serial.print("Beet name ");
        Serial.print(a);
        Serial.print(": ");
        Serial.println(setup_data_2.beet_name[a]);
#endif
    };
    //load IP_ventil
    for (int a = 0; a < 20; a++)
    {
        for (int i = 0; i < 40; i++)
        {
            setup_data_2.IP_ventil[a][i] = EEPROM.read(adress_register.IP_ventil + i + a * 40);
            if (setup_data_2.IP_ventil[a][i] == 0)
            {
                break;
            }
        };
#if ausgabe_serial == 1
        Serial.print("IP_ventil ");
        Serial.print(a);
        Serial.print(": ");
        Serial.println(setup_data_2.IP_ventil[a]);
#endif
    };
    //load IP_sensor
    for (int a = 0; a < 20; a++)
    {
        for (int i = 0; i < 40; i++)
        {
            setup_data_2.IP_sensor[a][i] = EEPROM.read(adress_register.IP_sensor + i + a * 40);
        };
#if ausgabe_serial == 1
        Serial.print("IP_sensor ");
        Serial.print(a);
        Serial.print(": ");
        Serial.println(setup_data_2.IP_sensor[a]);
#endif
    };
    //load ventil_nr
    for (int i = 0; i < 20; i++)
    {
        setup_data_2.ventil_nr[i] = EEPROM.read(adress_register.ventil_nr + i);
#if ausgabe_serial == 1
        Serial.print("Beet nr: ");
        Serial.print(i);
        Serial.print("ventil nr : ");
        Serial.println(setup_data_2.ventil_nr[i]);
#endif
    };

    //load stand_bew_zeit
    for (int i = 0; i < 20; i++)
    {
        setup_data_2.stand_bew_zeit[i] = EEPROM.read(adress_register.stand_bew_zeit + i);
#if ausgabe_serial == 1
        Serial.print("Beet nr: ");
        Serial.print(i);
        Serial.print("standart bew zeit : ");
        Serial.println(setup_data_2.stand_bew_zeit[i]);
#endif
    };
};

void save_load::save_data_beete(Data_Beete data_beete[])
{
    adress_register adress_register;
    for (int i = 0; i < 20; i++)
    {
        for (int a = 0; a < 24; a++)
        {
            EEPROM.write(adress_register.data_beete + a + 25 * i, data_beete[i].beet_feuchte[a]);
        }
        if (data_beete[i].bew_geplant)
        {
            EEPROM.write(adress_register.data_beete + 24 + 25 * i, 1);
        }
        else
        {
            EEPROM.write(adress_register.data_beete + 24 + 25 * i, 0);
        }
    };
    Serial.print("gespeichert Data_beete");
    EEPROM.commit();
};

void save_load::load_data_beete(Data_Beete data_beete[])
{
    adress_register adress_register;
    for (int i = 0; i < 20; i++)
    {
        //Serial.print("Beet ");
        //Serial.print(i);
        //Serial.println(": ");
        for (int a = 0; a < 24; a++)
        {
            data_beete[i].beet_feuchte[a] = EEPROM.read(adress_register.data_beete + a + 25 * i);
            //Serial.print("  feuchte von:");
            //Serial.print(a);
            //Serial.print(" ist: ");
            //Serial.println(data_beete[i].beet_feuchte[a]);
        }

        if (EEPROM.read(adress_register.data_beete + 24 + 25 * i) == 1)
        {
            //Serial.println("  bew. geplant ");
            data_beete[i].bew_geplant = true;
        }
        else
        {
            //Serial.println("  bew. geplant ");
            //Serial.println("  bew. nicht geplant ");
            data_beete[i].bew_geplant = false;
        }
    };
}

void save_load::save_data_einst(data_einstellungen data_einstellungen)
{
    adress_register adress_register;
    EEPROM.write(adress_register.data_einst, data_einstellungen.farb_id);
    EEPROM.write(adress_register.data_einst + 1, data_einstellungen.min_feuchte);
    EEPROM.write(adress_register.data_einst + 2, data_einstellungen.min_regen_id);
    EEPROM.commit();
    //Serial.println("Eistellung_data Gespeichert");
};

void save_load::load_data_einst(data_einstellungen &data_einstellungen)
{
    adress_register adress_register;
    data_einstellungen.farb_id = EEPROM.read(adress_register.data_einst);
#if ausgabe_serial == 1
    Serial.print("farb_id: ");
#endif
    Serial.println(data_einstellungen.farb_id);
    switch (data_einstellungen.farb_id)
    {
    case 0:
        data_einstellungen.farbe = Turquoise;
        break;
    case 1:
        data_einstellungen.farbe = Emerald;
        break;
    case 2:
        data_einstellungen.farbe = Peterriver;
        break;
    case 3:
        data_einstellungen.farbe = Wetasphalt;
        break;
    case 4:
        data_einstellungen.farbe = Sunflower;
        break;
    case 5:
        data_einstellungen.farbe = Carrot;
        break;
    case 6:
        data_einstellungen.farbe = Alizarin;
        break;
    case 7:
        data_einstellungen.farbe = Dark;
        break;
    case 8:
        data_einstellungen.farbe = None;
        break;
    default:
        data_einstellungen.farbe = Turquoise;
        data_einstellungen.farb_id = 0;
    }
    data_einstellungen.min_feuchte = EEPROM.read(adress_register.data_einst + 1);
    data_einstellungen.min_regen_id = EEPROM.read(adress_register.data_einst + 2);
    if (data_einstellungen.min_feuchte > 100)
    {
        data_einstellungen.min_feuchte = 50;
    }
    if (data_einstellungen.min_regen_id > 2)
    {
        data_einstellungen.min_regen_id = 1;
    }
};