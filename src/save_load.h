#include <Arduino.h>

struct adress_register
{
    //hier werden alle adressen im EEPROM speicher definiert
    const uint8_t setup_zust = 0;
    const uint8_t ssid = 1;
    const uint8_t psw = 41;
    const uint8_t hostname = 81;
    const uint8_t anz_beete = 121;
    const uint8_t login_usr = 122;
    const uint8_t login_psw = 163;
    const uint8_t bew_typ = 204;
    const uint8_t login = 205;
    const uint16_t login_dat[2] = {206, 246};
    const uint16_t wetter[3] = {286, 326, 366};
    const uint16_t beet_name = 406;
    const uint16_t IP_ventil = 1206;
    const uint16_t ventil_nr = 2006;
    const uint16_t stand_bew_zeit = 2026;
    const uint16_t IP_sensor = 2046;
    const uint16_t data_beete = 2847;
    const uint16_t data_einst = 3347;
    //ende aller speicheranforderungen um die Platzreservierung zu vereinfachen
    const uint16_t ende = 3351;
};

class save_load
{
private:
public:
    void init_eeprom();
    void Save_1(char ssid[], char pw[], char hostname[], uint8_t anz_beete, uint8_t bew_typ, uint8_t login);
    void Load_1(uint8_t &setup_zust, char ssid[], char pw[], char hostname[], uint8_t &anz_beete, uint8_t &bew_typ, uint8_t &login);
    void Save_2(setup_data2 setup_data_2);
    void Load_2(setup_data2 &setup_data_2);
    void save_data_beete(Data_Beete data_beete[]);
    void load_data_beete(Data_Beete data_beete[]);
    void save_data_einst(data_einstellungen data_einstellungen);
    void load_data_einst(data_einstellungen &data_einstellungen);
};
