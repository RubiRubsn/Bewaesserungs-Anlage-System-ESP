#include <arduino.h>
#include <ESPUI.h>

struct datum_id
{
  long datum;
  int id;
};

struct wetter_dat
{
  datum_id aktuell;
  datum_id voraus[2];
  int h_bis_21;
  int min_bis_21;
  int sek_bis_21;
  long timestamp_heute_21;
};

struct einstellungen_id
{
  int einst_tab_id;
  int Allgemein[20];

  int beete_einst_tab_id;
  int Beete[7];
  uint8_t ausgew_beet = 99;
};

struct Data_Beete
{
  uint8_t beet_feuchte[24] = {111};
  String ventil_zustand;
  bool bew_geplant = true;
  bool auto_bew = false;
  bool bew_beendet = false;
};

struct flaggs
{
  bool update_text = false;
  bool update_UI = false;
  bool update_data = false;
  bool reload_wetter = false;
  bool save_data = false;
  bool reset_data = false;
  bool save_data_beete = false;
  bool logout = false;
};

struct data_einstellungen
{
  ControlColor farbe;
  uint8_t farb_id;
  uint8_t min_feuchte;
  uint8_t min_regen_id;
};

class main_server
{
private:
  static bool aktiviere_ota_update;
  static uint32_t timer_zwischenspeicher_sensoren;
  static uint32_t timer_zwischenspeicher_refresh;
  static uint8_t ausgew_beet;
  static setup_data1 update_data_1;
  static setup_data2 update_data_2;
  static data_einstellungen data_einst;
  static int tabs[11];
  static bool reset;
  static int allgemein[20];
  static int wetter_id[4];
  static einstellungen_id einst_id;
  static flaggs load_flaggs;
  static wetter_dat wetter_data;
  static uint8_t manuelle_bew_zeit[20];
  static void update_beet_ui();
  static void update_wetter_ui();
  static void sliderCallback(Control *sender, int value);
  static void update_data_ex(setup_data1 &setup_data_1, setup_data2 &setup_data_2);
  static void switchCallback(Control *sender, int value);
  static void textCallback(Control *sender, int type);
  static void selectCallback(Control *sender, int type);
  static void buttonCallback(Control *sender, int type);
  static void update_beet_einst_text(setup_data1 &setup_data_1, setup_data2 &setup_data_2);
  wetter_dat abfrage_wetter(const char *breitengrad, const char *laengengrad, const char *appid);
  static String wetter_klassifizierung(int id);
  bool flaggs_abfragen(setup_data1 &setup_data_1, setup_data2 &setup_data_2);
  bool refresh_timer_sensoren();
  bool refresh_timer();
  static String httpGETRequest(const char *serverName);
  void abfrage_sensoren();
  void abfrage_ventil();
  void berechnung_bewaesserung();
  static void set_ventil(int i, char zeit[]);
  static void stop_ventil(int ausgew_beet);
  void reset_var_check();
  static void handleOTAUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);
  static void init_ota_update(setup_data1 update_data_1, setup_data2 update_data_2);

public:
  static Data_Beete data_beete[20];
  void init_server(setup_data1 &setup_data_1, setup_data2 &setup_data_2);
  bool handle_server(setup_data1 &setup_data_1, setup_data2 &setup_data_2);
};