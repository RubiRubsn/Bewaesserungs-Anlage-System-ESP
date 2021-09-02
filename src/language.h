#include <Arduino.h>

#define LANG GER

#define GER 'G'

#if LANG == GER

struct lang_setup_1
{
    const char *name_tab = "Setup schritt 1";
    const char *welcome = "willkommen";
    const char *welcome_description = "Bitte füllen sie die Nachfolgenden felder aus: nach dem bestätigen Startet der Server neu und ist dann unter der IP: 192.168.178.1 zu erreichen. ist dies nicht der fall schauen sie die IP in den einstellungen ihres Routers nach.";
    const char *SSID = "SSID:";
    const char *psw = "Passwort:";
    const char *name_system = "Name des systems:";
    const char *number_of_bed = "Anzahl der Beete:";
    const char *secure_ui_with_login = "Benutzeroberfläche mit Login Schützen?";
    const char *irrigation_type = "Bewässerungs Typ";
    const char *irrigation_manuel = "Manuell";
    const char *irrigation_moist = "nach Bodenfeuchte";
    const char *irrigation_moist_weather = "nach Bodenfeuchte + Wetter";
    const char *confirm_changes = "Angaben Bestätigen";
    const char *press = "Drücken";
    const char *hostname = "Einrichtung der Bewässerungsanlage";
};

struct lang_setup_2
{
    const char *name_tab_general = "Allgemein";
    const char *name_tab_bed = "Beete";
    const char *login_header = "Login des Webinterface:";
    const char *login_description = "Bitte gib sie Nachfolgend deine gewünschten Logindaten ein";
    const char *login_usr = "Login Benutzername:";
    const char *login_psw = "Login passwort:";
    const char *weather_data = "Wetterdaten:";
    const char *weather_data_description = "Bitte gib Nachfolgend den Zugangscode deiner openweathermap.org API, wenn du diesen nicht haben solltest erstelle dir Kostenfrei einen Account, ein und darauffolgend den Breiten und Längengrad deines Gartens";
    const char *weather_api = "Wetter API Code";
    const char *weather_latitude = "Breitengrad";
    const char *weather_longitude = "Längengrad";
    const char *nothing_for_you = "Hier gibt es für dich nichts zu sehen!";
    const char *nothing_for_you_description = "bitte gehen sie direkt zu den einstellungen ihres beetes weiter, nutze die tabs oben ^^";
    const char *go_on = "Weiter gehts";
    const char *go_on_description = "jetzt geht es mit den einstellungen der beete weiter, nutze die tabs oben ^^";
    const char *choose_bed = "Beet_Auswählen";
    const char *please_choose_a_bed = "bitte wählen sie ein Beet aus";
    const char *name_of_bed = "Bitte gib den Namen dieses Beets an";
    const char *IP_info = "info zu den IP eingaben";
    const char *IP_info_description = "Da der Code des Ventil Server bis zu 4 Relays pro ESP unterstützt, gib unter der Ip an, welches Relay du genutzt hast. falls du nur ein Relay von dem server nutzt wähle 1 aus. falls du mehrere nutzt, trage bei allen genutzten die selbe IP ein und wähle dann das passende Relay.";
    const char *IP_relay = "IP Relai";
    const char *used_relay = "genutztes Relai an Ventil server ESP";
    const char *info_irrigation_time = "info zu Bewässerungszeit";
    const char *info_irrigation_time_description = "die Bewässerungszeit solltest du dir errechnen aus, bewässerungs leistung deines schlauchs und beetgröße, diese einstellung kannst du später noch ändern.";
    const char *IP_sensor = "IP Sensor ";
    const char *default_irrigation_time = "Standart Bewässerungs zeit";
    const char *confirm_changes = "Angaben Bestätigen:";
    const char *press = "Drücken";
    const char *secure_ui_with_login = "Benutzeroberfläche mit Login Schützen?";
};

struct lang_main_server
{
    const char *name_tab_general = "Allgemein";
    const char *currently_not_available = "nicht erreichbar";
    const char *current_weather = "aktuelles Wetter:";
    const char *weather_tomorrow = "Wetter morgen:";
    const char *moisture_in_bed = "Feuchte im ";
    const char *reload = "neu laden";
    const char *press = "DRÜCKEN";
    const char *name_tab_bed = "Beete";
    const char *choose_bed = "Beet auswählen";
    const char *please_choose_bed = "bitte ein Beet auswählen";
    const char *valve_condition = "Ventil zustand";
    const char *current_moisture = "aktuelle Feuchte";
    const char *average_moisture = "durchschnittliche Feuchte der letzten 24 H";
    const char *planed_irrigation = "geplante Bewässerung";
    const char *not_planed = "nicht geplant";
    const char *do_planed_irrigation = "geplante Bewässerung durchführen";
    const char *time_for_manual_irrigation = "Bewässerungszeit für eine manuelle Bewässerung";
    const char *start_manual_irrigation = "manuelle Bewässerung starten";
    const char *stop_irrigation = "Bewässerung stoppen";
    const char *name_tab_general_settings = "Allgemeine Einstellungen";
    const char *irrigation_type = "Bewässerungs Typ";
    const char *irrigation_manuel = "Manuell";
    const char *irrigation_moist = "nach Bodenfeuchte";
    const char *irrigation_moist_weather = "nach Bodenfeuchte + Wetter";
    const char *number_of_bed = "Anzahl der Beete:";
    const char *name_of_system = "Name des Systems:";
    const char *SSID = "SSID:";
    const char *psw = "Wifi Passwort:";
    const char *weather_api = "Wetter API Code";
    const char *weather_latitude = "Breitengrad";
    const char *weather_longitude = "Längengrad";
    const char *color = "Farbe";
    const char *plan_irrigation_info = "Bewässerung planen";
    const char *plan_irrigation_info_description = "Bewässerung wird geplant, wenn :";
    const char *moisture_under = "Feuchte ist unter ...%";
    const char *rain_over = "und kein Regen über .. angesagt ist:";
    const char *light = "leicht";
    const char *moderate = "moderat";
    const char *heavy = "stark";
    const char *reset_info = "zum zurücksetzten hier bitte ZURÜCKSETZEN eingeben und dann bestätigen";
    const char *reset_info_description = "willst du das wirklich?";
    const char *reset_server = "Server zurücksetzen";
    const char *software_version = "Software Version:";
    const char *activate_ota_update = "Aktiviere OTA Update";
    const char *name_tab_bed_settings = "Beete Einstellungen";
    const char *name_of_bed = "Bitte gib den Namen dieses Beets an";
    const char *IP_info = "info zu den IP eingaben";
    const char *IP_info_description = "Da der Code des Ventil Server bis zu 4 Relays pro ESP unterstützt, gib unter der Ip an, welches Relay du genutzt hast. falls du nur ein Relay von dem server nutzt wähle 1 aus. falls du mehrere nutzt, trage bei allen genutzten die selbe IP ein und wähle dann das passende Relay.";
    const char *IP_relay = "IP Relai";
    const char *used_relay = "genutztes Relai an Ventil server ESP";
    const char *info_irrigation_time = "info zu Bewässerungszeit";
    const char *info_irrigation_time_description = "die Bewässerungszeit solltest du dir errechnen aus, bewässerungs leistung deines schlauchs und beetgröße, diese einstellung kannst du später noch ändern.";
    const char *IP_sensor = "IP Sensor ";
    const char *default_irrigation_time = "Standart Bewässerungs zeit";
    const char *save = "Speichern";
    const char *secure_ui_with_login = "Benutzeroberfläche mit Login Schützen?";
    const char *login_usr = "Login Benutzername:";
    const char *login_psw = "Login passwort:";
};

#else

struct lang_setup_1
{
    const char *name_tab = "Setup schritt 1";
    const char *welcome = "willkommen";
    const char *welcome_description = "Bitte füllen sie die Nachfolgenden felder aus: nach dem bestätigen Startet der Server neu und ist dann unter der IP: 192.168.178.1 zu erreichen. ist dies nicht der fall schauen sie die IP in den einstellungen ihres Routers nach.";
    const char *SSID = "SSID:";
    const char *psw = "Passwort:";
    const char *name_system = "Name des systems:";
    const char *number_of_bed = "Anzahl der Beete:";
    const char *secure_ui_with_login = "Benutzeroberfläche mit Login Schützen?";
    const char *irrigation_type = "Bewässerungs Typ";
    const char *irrigation_manuel = "Manuell";
    const char *irrigation_moist = "nach Bodenfeuchte";
    const char *irrigation_moist_weather = "nach Bodenfeuchte + Wetter";
    const char *confirm_changes = "Angaben Bestätigen";
    const char *press = "Drücken";
    const char *hostname = "Einrichtung der Bewässerungsanlage";
};

struct lang_setup_2
{
    const char *name_tab_general = "Allgemein";
    const char *name_tab_bed = "Beete";
    const char *login_header = "Login des Webinterface:";
    const char *login_description = "Bitte gib sie Nachfolgend deine gewünschten Logindaten ein";
    const char *login_usr = "Login Benutzername:";
    const char *login_psw = "Login passwort:";
    const char *weather_data = "Wetterdaten:";
    const char *weather_data_description = "Bitte gib Nachfolgend den Zugangscode deiner openweathermap.org API, wenn du diesen nicht haben solltest erstelle dir Kostenfrei einen Account, ein und darauffolgend den Breiten und Längengrad deines Gartens";
    const char *weather_api = "Wetter API Code";
    const char *weather_latitude = "Breitengrad";
    const char *weather_longitude = "Längengrad";
    const char *nothing_for_you = "Hier gibt es für dich nichts zu sehen!";
    const char *nothing_for_you_description = "bitte gehen sie direkt zu den einstellungen ihres beetes weiter, nutze die tabs oben ^^";
    const char *go_on = "Weiter gehts";
    const char *go_on_description = "jetzt geht es mit den einstellungen der beete weiter, nutze die tabs oben ^^";
    const char *choose_bed = "Beet_Auswählen";
    const char *please_choose_a_bed = "bitte wählen sie ein Beet aus";
    const char *name_of_bed = "Bitte gib den Namen dieses Beets an";
    const char *IP_info = "info zu den IP eingaben";
    const char *IP_info_description = "Da der Code des Ventil Server bis zu 4 Relays pro ESP unterstützt, gib unter der Ip an, welches Relay du genutzt hast. falls du nur ein Relay von dem server nutzt wähle 1 aus. falls du mehrere nutzt, trage bei allen genutzten die selbe IP ein und wähle dann das passende Relay.";
    const char *IP_relay = "IP Relai";
    const char *used_relay = "genutztes Relai an Ventil server ESP";
    const char *info_irrigation_time = "info zu Bewässerungszeit";
    const char *info_irrigation_time_description = "die Bewässerungszeit solltest du dir errechnen aus, bewässerungs leistung deines schlauchs und beetgröße, diese einstellung kannst du später noch ändern.";
    const char *IP_sensor = "IP Sensor ";
    const char *default_irrigation_time = "Standart Bewässerungs zeit";
    const char *confirm_changes = "Angaben Bestätigen:";
    const char *press = "Drücken";
    const char *secure_ui_with_login = "Benutzeroberfläche mit Login Schützen?";
};

struct lang_main_server
{
    const char *name_tab_general = "General";
    const char *currently_not_available = "not available";
    const char *current_weather = "current weather:";
    const char *weather_tomorrow = "weather tomorrow:";
    const char *moisture_in_bed = "moisture in ";
    const char *reload = "reload";
    const char *press = "PRESS";
    const char *name_tab_bed = "Bed";
    const char *choose_bed = "choose bed";
    const char *please_choose_bed = "Please choose a bed";
    const char *valve_condition = "valve condition";
    const char *current_moisture = "current moisture";
    const char *average_moisture = "avarrage moisture of the last 24 hours";
    const char *planed_irrigation = "planned irrigation";
    const char *not_planed = "not planed";
    const char *do_planed_irrigation = "do the planed irrigation";
    const char *time_for_manual_irrigation = "irrigation time for a manual irrigation";
    const char *start_manual_irrigation = "start manual irrigation";
    const char *stop_irrigation = "stop irrigation";
    const char *name_tab_general_settings = "General settings";
    const char *irrigation_type = "irrigation type";
    const char *irrigation_manuel = "manual";
    const char *irrigation_moist = "moisture";
    const char *irrigation_moist_weather = "moisture + weather";
    const char *number_of_bed = "number of beds:";
    const char *name_of_system = "name of beds:";
    const char *SSID = "SSID:";
    const char *psw = "Wifi password:";
    const char *weather_api = "weather API Code";
    const char *weather_latitude = "latitude";
    const char *weather_longitude = "logitude";
    const char *color = "color";
    const char *plan_irrigation_info = "plan irrigation";
    const char *plan_irrigation_info_description = "plan irrigation, when";
    const char *moisture_under = "moisture is under ...%";
    const char *rain_over = "and no rain over .. ist forecasted:";
    const char *light = "light";
    const char *moderate = "moderate";
    const char *heavy = "heavy";
    const char *reset_info = "to reset the server type ZURÜCKSETZEN and press commit";
    const char *reset_info_description = "do you really want that?";
    const char *reset_server = "reset server";
    const char *software_version = "software version:";
    const char *activate_ota_update = "activate ota update";
    const char *name_tab_bed_settings = "Bed settings";
    const char *name_of_bed = "please type the name of the bed";
    const char *IP_relay = "IP relay";
    const char *used_relay = "used relay on ESP valve-server";
    const char *IP_sensor = "IP sensor ";
    const char *default_irrigation_time = "default irrigation time";
    const char *save = "save";
    const char *secure_ui_with_login = "secure UI with login?";
    const char *login_usr = "login username:";
    const char *login_psw = "login password:";
};
#endif
