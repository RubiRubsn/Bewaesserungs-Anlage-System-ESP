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
    <a href="https://github.com/RubiRubsn/Bewaesserungs-Anlage-System-ESP/issues">Features anfrage</a>
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
    </li>
    <li><a href="#Danksagung">Danke an!</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->

## #Über das Projekt

Das Ziel dieser Software ist es, ein gut funktionierendes teilautomatisiertes Bewässerungssystem zu sein.
Das System kann in 3 verschiedenen Modi betrieben werden.<br>

1. Manuell <br>
    im manuellen Modus wird keine automatische Bewässerung ausgeführt

2. Automatisiert mit Feuchtesensoren<br>
    Hier wird anhand von Feuchtesensoren die Feuchte im Beet gemessen und daran entschieden, ob bewässert werden soll.

3. Automatisiert mit Feuchtesensoren und Wetter vorhersage<br>
    Hier wird anhand von Feuchtesensoren die Feuchte im Beet gemessen und in Zusammenspiel mit der Wettervorhersage entschieden, ob bewässert werden soll.

<br>!!ACHTUNG in Version 1.0 ist nur Modi 3 und 1 Nutzbar!! <br><br>

Als Hauptserver dient ein ESP32 auf dem mit Hilfe der Bibliothek <a href="https://github.com/s00500/ESPUI">ESPUI von s00500</a> ein Webinterface gestaltet wurde.
Dieser Server sammelt die Feuchtewerte und plant auch die Bewässerung. Da dieser Server nur die Bewässerung startet, stoppt die Bewässerung automatisch auch im Falle eines Absturz des Systems.<br>
Dieser Server kann mit Freigaben auch öffentlich erreicht werden. Ich habe dies mit Hilfe von <a href="https://myfritz.net/">MY!FRITZ</a> realisiert. (setzt die Nutzung einer Fritz!box voraus). <br>
Es gibt 2 weitere Typen von Servern, ein Feuchteserver und ein Ventilserver. Beide Server werden mit ESP8266 realisiert.<br>
Der Feuchteserver sendet auf Anfrage des Hauptservers die Feuchte an den Server. Dieser Feuchteserver kann direkt am Beet angebracht werden.
Der Ventilserver kann in 3 verschiedenen Modis betrieben werden. <br>

1. Nutzung von bis zu vier Ventilen pro Server am Trinkwasseranschluss

2. Nutzung von bis zu vier Ventilen an einer Pumpe. Diese Pumpe kann geschalten werden.

3. Nutzung von bis zu vier Ventilen an einer Pumpe. Diese Pumpe kann geschalten werden in Abhängigkeit vom Füllstand, z.B. in einem Regenfass um das laufen der Pumpe im Trocknen zu verhindern.


### Details zur Oberfläche
Die Oberfläche unterstützt bis zu 20 Beete. das Aktuelle Wetter und auch die aktuelle feuchte werden im  Allgemein Tab angezeigt.

[![Allgemein Screenshot][product-screenshot]]()

Im Tab Beete ist eine detalierte Betrachtung jedes Beets möglich. vom ventil zustand, bis hin zur Manuellen Bewässerung oder auch ob eine Automatisierte Bewässerung geplant ist erfährst du hier alles.

[![Beete Screenshot][beet-screenshot]]()

Im Tab Allgemeine Einstellungen kannst du alles einstellen, ob deine Oberfläche Passwort geschützt sein soll, bis hin zu den Automatischen Bewässerungs Kriterien.

[![einst Screenshot][einst-screenshot]]()

Im Tab Beet Einstellungen kannst du alles zu den Beeten einstellen. wie, den Namen oder auch die Adressen der Feuchte bzw Ventil Sensoren.

[![beet einst Screenshot][beeteinst-screenshot]]()


### Was brauche ich

für die Nutzung der Oberfläche ist ein Kostenloser zugang zur <a href="https://openweathermap.org/api">Openweathermap API</a> notwendig.
nach der Anmeldung erhälst du einen API schlüssel den du im einrichtungs Prozess in der Oberfläche eintragen kannst.

als Ventile für das wasser nutzte ich: <a href="https://www.amazon.de/gp/product/B06XCSVZPT/ref=ppx_yo_dt_b_asin_image_o02_s01?ie=UTF8&psc=1">UEETEK 1/2 Zoll 12V Elektro Magnetventil</a>   

als Relays für die Ventile benutze ich <a href="https://www.amazon.de/gp/product/B07TZ778VH/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1">eine Standart 4er Relay Platine</a>.

als feuchte sensoren nutzte ich <a href="https://www.az-delivery.de/products/bodenfeuchte-sensor-modul-v1-2?_pos=6&_sid=22262207f&_ss=r">capacitiv soil moisture Sensor v1.2</a>.
deren ende (also da wo bauteile aufgelötet sind, die nicht nass werden dürfen) ich mit hilfe eine Plastik shotglases in Epoxidharz eingegossen habe.
dieser sensor wird auch für die Nutzung der Füllstandmessung im Regenfass benutzt (Optional)

Als haupt server habe ich den <a href="https://www.az-delivery.de/products/esp32-dev-kit-c-unverlotet?_pos=5&_sid=72925e31b&_ss=r">ESP32 Dev Kit c</a> verwendet.

als Server für die Feuchtigkeit habe ich <a href="https://www.az-delivery.de/products/nodemcu-lua-lolin-v3-modul-mit-esp8266-12e-unverlotet?_pos=28&_sid=f7dcaf8b6&_ss=r">ESP8266</a> verwendet.

dazu natürlich passende 5v netzteile für die ESP´s und 12V netzteile für die Ventile.

Als Bewässerungsschlauch habe ich den Perlschlauch von  <a href="https://cs-wss.com/">CS systeme</a> verwendet.

Dazu noch passend Rohre um zu den Beeten zu kommen.

## Beispiele

Hier folgt in kürze ein Video

## Installation
1.a. lade dir das Releas firmware.bin File herunter und nutze  <a href="https://github.com/Grovkillen/ESP_Easy_Flasher">ESP_Easy_Flasher</a> um den File auf den Haupt Server zu Flashen.

1.b. oder clone dieses Repository und flashe den File mit VSCode und Platform IO

1.2. zum Einrichten gehe in das offene Netzwerk des ESP32.

1.3 nach der Einrichtung stelle bei deinem Router ein, dass die IP des ESP32 immer gleich bleibt.

2. <a href="https://github.com/RubiRubsn/feuchte_server">clone das Repository für den Feuchte Server</a>  und Trage SSID und Passwort deines Netzwerks hier ein. 

2.1. flashe einen ESP8266 mit dieser Software und warte bis dieser sich mit deinem Router verbunden hat.

2.2. nach dem du den Feuchte Sensor an den Pin A0 angelötet hast, musst du diesen Noch kallibrieren mit (im webbrowser auf einem gerät das im selben netzwerk ist): http.//IP_Des_ESP/kalibrierung?typ=0
    für Trocken und dann tue den Sensor ins wasser und http.//IP_Des_ESP/kalibrierung?typ=1 für nass. die IP des ESP muss im Haupt Server Eingetragen Werden.

2.3. nach der Einrichtung stelle bei deinem Router ein, dass die IP des ESP8266 immer gleich bleibt.

3. <a href="https://github.com/RubiRubsn/ventil_server">clone das Repository für den ventil Server </a> und Trage SSID und Passwort deines Netzwerks ein. zusätzlich die anzahl der Genutzten Ventile und ob eine Pumpe verwendet wird und ob füllstand verwendet wird.

3.1. flashe einen ESP8266 mit dieser Software und warte bis dieser sich mit deinem Router verbunden hat. verbinde die Relays mit dem im Code genannten Pins. 

3.2. trage die IP des Ventilservers im Hauptserver ein.

3.3. nach der Einrichtung stelle bei deinem Router ein, dass die IP des ESP8266 immer gleich bleibt.

Fertig!

Schalt diagramme Folgen noch


## Danksagung

- <a href="https://github.com/s00500">s00500 zur Bereitstellung seiner genialen UI Lib</a>




[product-screenshot]: images/allgemein.png
[beet-screenshot]: images/beete.png
[einst-screenshot]: images/einstellungenAllg.png
[beeteinst-screenshot]: images/beet-einst.png