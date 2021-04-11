#include <ESPUI.h>

struct setup_data1
{
    char ssid[40];
    char password[40];
    char hostname[40];
    uint8_t bew_typ = 1;
    uint8_t login = 0;
    uint8_t anzahl_beete = 1;
    bool end_setup = false;
};

struct setup_data2
{
    uint8_t setup_zust = 2;
    char login[2][40] = {{126}};
    //0 == id 1 ==breit 2==läng
    char wetter[3][40] = {{126}};
    char beet_name[20][40] = {{126}};
    char IP_ventil[20][40] = {{126}};
    uint8_t ventil_nr[20];
    uint8_t stand_bew_zeit[20];
    char IP_sensor[20][40] = {{126}};
    bool end_setup = false;
};

struct beet
{
    int id_name = 0;
    int id_ip_sensor = 0;
    int id_ip_relay = 0;
    int id_ip_relay_nr = 0;
    int id_stand_bew_zeit = 0;
};

struct id_init2
{
    int login[2] = {0};
    int wetter[3] = {0};
    beet id_beet;
    uint16_t ausgew_beet_id;
    int absenden = 0;
    uint8_t ausgew_beet = 0;
};

class server_setup
{
private:
    static int dev_button_id;
    static int ID_init_1[7];
    static id_init2 id_init_2;

    static void textCall_set_2(Control *sender, int type);
    static void select_set_2(Control *sender, int value);
    static void buttonCallback_set_2(Control *sender, int type);
    static void select_set_1(Control *sender, int value);
    static void switch_set_1(Control *sender, int value);
    static void textCall_set_1(Control *sender, int type);
    static void numberCall_set_1(Control *sender, int type);
    static void buttonCallback_set_1(Control *sender, int type);
    static void update_text();

public:
    static setup_data1 setup_data_1;
    static setup_data2 setup_data_2;
    void init_1();
    setup_data1 handle_setup_1();
    void init_2(const char *ssid, const char *password, const char *hostname, const uint8_t anz_bee, const uint8_t bew_typ, const uint8_t login);
    setup_data2 handle_setup_2();
};