<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/RubiRubsn/Bewaesserungs-Anlage-System-ESP/">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Bewässerungsanlage</h3>

  <p align="center">
    Programmiert für die ESP-Plattform mit PlatformIO
    <br />
    <a href="#Installation"><strong>zur Installation»</strong></a>
    <br />
    <br />
    <a href="#Beispiele">Beispiele</a>
    ·
    <a href="https://github.com/RubiRubsn/Bewaesserungs-Anlage-System-ESP/issues">Bugs melden</a>
    ·
    <a href="https://github.com/RubiRubsn/Bewaesserungs-Anlage-System-ESP/issues">Features anfragen</a>
  </p>
</p>

<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Inhaltsverzeichnis</summary>
  <ol>
    <li>
      <a href="#Über-das-Projekt">Über das Projekt</a>
        <ul>
            <li><a href="#Details-zur-Oberfläche">Details zur Oberfläche</a></li>
            <li><a href="#Was-brauche-ich">Was brauche ich?</a></li>
      </ul>
    </li>
    <li><a href="#Beispiele">Beispiele</a></li>
    <li>
      <a href="#Installation">Installation</a>
      <ul>
            <li><a href="#Update">update</a></li>
      </ul>
    </li>
    <li><a href="#Schaltungen">Schaltungen</a></li>
    <li><a href="#Danksagung">Danksagung!</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->

### Über das Projekt

Das Ziel dieser Software ist, ein gut funktionierendes teilautomatisiertes Bewässerungssystem.
Das System kann in 3 verschiedenen Modi betrieben werden.<br>

1. Manuell <br>
    im manuellen Modus wird keine automatische Bewässerung ausgeführt

2. Automatisiert mit Feuchtesensoren<br>
    Hier wird anhand von Feuchtesensoren die Feuchte im Beet gemessen und daran entschieden, ob bewässert werden soll.

3. Automatisiert mit Feuchtesensoren und Wettervorhersage<br>
    Hier wird anhand von Feuchtesensoren die Feuchte im Beet gemessen und in Zusammenspiel mit der Wettervorhersage entschieden, ob bewässert werden soll.

<br>!!ACHTUNG in Version 1.- ist nur Modi 3 und 1 Nutzbar!! <br><br>

Als Hauptserver dient ein ESP32 auf dem mit Hilfe der Bibliothek <a href="https://github.com/s00500/ESPUI">ESPUI von s00500</a> ein Webinterface gestaltet wurde.
Dieser Server sammelt die Feuchtewerte und plant auch die Bewässerung. Da dieser Server nur die Bewässerung startet, stoppt die Bewässerung automatisch auch im Falle eines Absturz des Systems.<br>
Dieser Server kann mit Freigaben auch öffentlich erreicht werden. Dies wurde mit Hilfe von<a href="https://myfritz.net/">MY!FRITZ</a> realisiert (setzt die Nutzung einer Fritz!box voraus). <br>
Es gibt 2 weitere Typen von Servern, ein Feuchteserver und ein Ventilserver. Beide Server werden mit ESP8266 realisiert.<br>
Der Feuchteserver sendet auf Anfrage des Hauptservers die Feuchte an den Hauptserver. Dieser Feuchteserver kann direkt am Beet angebracht werden.
Der Ventilserver kann in 3 verschiedenen Modi betrieben werden. <br>

1. Nutzung von bis zu vier Ventilen pro Server am Trinkwasseranschluss

2. Nutzung von bis zu vier Ventilen an einer Pumpe. Diese Pumpe kann geschalten werden.

3. Nutzung von bis zu vier Ventilen an einer Pumpe. Diese Pumpe kann geschalten werden in Abhängigkeit vom Füllstand, z.B. in einem Regenfass um das laufen der Pumpe im Trocknen zu verhindern.


### Details zur Oberfläche
Die Oberfläche unterstützt bis zu 20 Beete. Das aktuelle Wetter und auch die aktuelle Feuchte werden im "Allgemein" Tab angezeigt.

[![Allgemein Screenshot][product-screenshot]]()

Im Tab "Beete" ist eine detallierte Betrachtung jedes Beets möglich. Vom Ventilzustand, bis hin zur manuellen Bewässerung oder auch ob eine automatisierte Bewässerung geplant ist, erfährst man hier alles.<br>

[![Beete Screenshot][beet-screenshot]]()

Im Tab "Allgemeine Einstellungen" findest man Einstellungen, wie: <br> - ob deine Oberfläche passwortgeschützt sein soll <br> - Einstellung der automatischen Bewässerungskriterien.<br>

[![einst Screenshot][einst-screenshot]]()

Im Tab "Beete Einstellungen" kannst man alles zu den Beeten einstellen, wie: <br> -  den Namen der Beete <br> - die Adressen der Feuchte- bzw Ventilsensoren <br> - die Standartbewässerungszeit der Beete<br>

[![beet einst Screenshot][beeteinst-screenshot]]()


### Was-brauche-ich

Für die Nutzung der Oberfläche ist ein kostenloser Zugang zur <a href="https://openweathermap.org/api">Openweathermap API</a> notwendig.
Nach der Anmeldung erhälst man einen API-Schlüssel den man im Einrichtungsprozess in der Weboberfläche eintragen kannst.<br>
Als Ventile für das Wasser nutze ich: <a href="https://www.amazon.de/gp/product/B06XCSVZPT/ref=ppx_yo_dt_b_asin_image_o02_s01?ie=UTF8&psc=1">UEETEK 1/2 Zoll 12V Elektro Magnetventile</a>.<br>
Als Relais für die Ventile nutze ich <a href="https://www.amazon.de/gp/product/B07TZ778VH/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1">eine Standart 4er Relai Platine</a>.<br>
Als Feuchtesensoren nutze ich <a href="https://www.az-delivery.de/products/bodenfeuchte-sensor-modul-v1-2?_pos=6&_sid=22262207f&_ss=r">capacitiv soil moisture Sensor v1.2</a>, deren Ende (also der belötete Teil der Platine) ich mit Hilfe eines Plastikshotglases in Epoxidharz eingegossen habe. <br>
Dieser Sensor wird auch für die Füllstandmessung im Regenfass benutzt (Optional).<br>
Als Hauptserver habe ich den <a href="https://www.az-delivery.de/products/esp32-dev-kit-c-unverlotet?_pos=5&_sid=72925e31b&_ss=r">ESP32 Dev Kit c</a> verwendet.<br>
Als Server für die Feuchtigkeit habe ich <a href="https://www.az-delivery.de/products/nodemcu-lua-lolin-v3-modul-mit-esp8266-12e-unverlotet?_pos=28&_sid=f7dcaf8b6&_ss=r">ESP8266</a> verwendet.<br>
Dazu nutze ich passende 5v Netzteile für die ESP´s und 12V Netzteile für die Ventile.<br>
Als Bewässerungsschlauch habe ich den Perlschlauch von  <a href="https://cs-wss.com/">CS systeme</a> verwendet.<br>
Dazu noch passende Rohre um zu den Beeten zu kommen.<br>

## Beispiele
<br>
Hier folgt in Kürze ein Video
<br>

## Installation 
<br>
1.a. Lade dir aus dem <a href="https://github.com/RubiRubsn/Bewaesserungs-Anlage-System-ESP/releases">"Releas"</a> das File "firmware.bin" herunter und nutze  <a href="https://github.com/Grovkillen/ESP_Easy_Flasher">ESP_Easy_Flasher</a> um das File auf den Hauptserver zu flashen.<br>
1.b. oder klone dieses Repository und flashe das File mit VSCode und Platform IO <br>
1.1. Zum Einrichten gehe in das offene Netzwerk des ESP32. <br>
1.2 Der Server befindet sich nach dem ersten Einrichtungsschritt unter <Festgelegtername>.local/<br>
1.3 Nach der Einrichtung stelle bei deinem Router ein, dass die IP des ESP32 immer gleich bleibt.<br><br>
2. <a href="https://github.com/RubiRubsn/feuchte_server">Klone das Repository für den Feuchteserver</a>  und trage die SSID und das Passwort deines Netzwerks ein. 
2.1(optional) Lege den Namen für den Zugriff per mDNS fest. (Version 1.- des Hauptservers unterstützt noch keine mDNS Auflösung)<br>

```sh
12 const char *SSID = "******";
13 const char *PSW = "****";
14 //hier den Namen des Sensors eintragen um eine einfachere Handhabung bei der IP-Eingabe zu haben
15 const char *Nummnerierung_der_server = "Beet-vorm-fenster";
```
<br>
2.2. Flashe einen ESP8266 mit dieser Software und warte bis dieser sich mit deinem Router verbunden hat.<br>
2.3. Nach dem du den Feuchtesensor an den Pin A0 angelötet hast, musst du diesen noch kallibrieren mit (im Webbrowser auf einem Gerät das im selben Netzwerk ist): http://IP_Des_ESP/kalibrierung?typ=0 für "Trocken" und dann lege den Sensor ins Wasser und gebe http://IP_Des_ESP/kalibrierung?typ=1 für "Nass" ein. Die IP des ESP muss im Hauptserver eingetragen werden.<br>
2.4. Nach der Einrichtung stelle bei deinem Router ein, dass die IP des ESP8266 immer gleich bleibt.<br>
3. <a href="https://github.com/RubiRubsn/ventil_server">Klone das Repository für den Ventilserver </a> und trage die SSID und das Passwort deines Netzwerks ein. Zusätzlich die Anzahl der genutzten Ventile (Aktuell max 4 pro Ventilserver), ob eine Pumpe verwendet wird und ob Füllstandsmessung verwendet wird.<br>

```sh
8 const int anz_relays = 4;
9 const bool pumpe = true;
10 bool fuellstand_sensor = true;
11 const int pumpe_pin = D5;
12 const uint8_t Relay[anz_relays] = {D0, D1, D2, D4};
13 const char *SSID = "****";
14 const char *PSW = "****";
15 //Hier die Nr. bzw Namen des Ventilservers eintragen um eine einfachere Handhabung bei der IP-Eingabe zu haben
16 const char *Nummnerierung_der_server = "1";
```
<br>
3.1. Flashe einen ESP8266 mit dieser Software und warte bis dieser sich mit deinem Router verbunden hat. Verbinde die Relaais mit dem im Code genannten Pins. (optional auch den Sensor an Pin A0)<br>
3.2. Trage die IP des Ventilservers im Hauptserver ein.<br>
3.3. Nach der Einrichtung stelle bei deinem Router ein, dass die IP des ESP8266 immer gleich bleibt.

Fertig!
<br>
### Update

1. Lade die aktuelle Version herunter. <a href="https://github.com/RubiRubsn/Bewaesserungs-Anlage-System-ESP/releases">"HIER"</a><br>
2. Öffne die Weboberfläche deines Bewässerungsservers und aktiviere die Einstellung "Aktiviere OTA Update" unter "Allgemeine Einstellungen"<br>
3. Öffne im Browser "ESP_IP"/ota<br>
4. Lade das firmware.bin File hoch und lade nach ca. 5 minuten die Webseite neu.<br>
Fertig!

## Schaltungen

Schaltdiagramm Ventilserver:<br>
[![ventil-schaltplan][ventil-schaltplan]]()
<br>
Schaltdiagramm Feuchteserver:<br>
[![feuchte-schaltplan][feuchte-schaltplan]]()
<br>


## Danksagung

- <a href="https://github.com/s00500">s00500 zur Bereitstellung seiner genialen UI Lib</a>
- meine Freunde Markus und Stephan zum Helfen bei vielen Sachen ^^



[product-screenshot]: images/allgemein.png
[beet-screenshot]: images/beete.png
[einst-screenshot]: images/einstellungenAllg.png
[beeteinst-screenshot]: images/beet-einst.png
[ventil-schaltplan]: images/schaltplan_ventil.png
[feuchte-schaltplan]: images/schaltplan_feuchte.png
