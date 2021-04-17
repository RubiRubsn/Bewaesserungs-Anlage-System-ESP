#include <Arduino.h>

#define lang 'G'

#if lang == 'G'

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
    const char *name_tab_generally = "Allgemein";
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
    const char *name_of_beed = "Bitte gib den Namen dieses Beets an";
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
};

struct language
{
};
#endif
