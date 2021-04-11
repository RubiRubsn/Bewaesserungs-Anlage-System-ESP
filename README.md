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
  <summary>Inhaltsverzeichniss</summary>
  <ol>
    <li>
      <a href="#über das Projekt">über das Projekt</a>
        <ul>
            <li><a href="#Details zur Oberfläche">Details zur Oberfläche</a></li>
            <li><a href="#Was Brauche ich">Was Brauche ich</a></li>
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

## #über das Projekt

Das ziehl dieser Software ist es, ein gut funktionierendes teil Automatisiertes Bewässerungssystem zu sein.
Das system kann in 3 verschiedenen Modi Betrieben Werden.
    1. Manuell
        im manuellen Modus wird keine Automatische bewässerung ausgeführt
    2. Automatisiert mit feuchte Sensoren
        Hier wird anhand von feuchtesensoren die Feuchte im Beet Gemessen und daran entschieden, ob bewässert werden soll.
    3. Automatisiert mit feuchte Sensoren und Wetter vorhersage
        Hier wird anhand von feuchtesensoren die Feuchte im Beet Gemessen und in zusammenspiel mit der Wettervorhersage entschieden, ob bewässert werden soll.
!!ACHTUNG in Version 1.0 ist nur modi 3 und 1 Nutzbar!!

Als Haup Server dient ein ESP32 auf dem mithilfe der Bibliothek <a href="https://github.com/s00500/ESPUI">ESPUI von s00500</a> ein Webinterface gestaltet wurde.
dieser Server sammelt die Fuchtewerte und plant auch die Bewässerung. Da dieser server nur die Bewässerung startet stoppt die bewässerung automatisch auch im falle eines Absturz des Systems.
Dieser server kann mit freigaben auch an öffentlich erreichbar werden. ich habe dies mithilfe von <a href="https://myfritz.net/">MY!FRITZ</a> getan (setzt die nutzung einer Fritz!box voraus). 
Es gibt 2 weitere typen von Servern, ein Feuchte Server und ein Ventil server. beide Server werden mit ESP8266 realisiert.
Der feuchte server sendet auf anfrage des Hauptservers die Feuchte an den Server. Dieser Feuchte Server kann direkt am beet angebracht werden.
der Ventil Server kann in 3 verschiedenen Modis betrieben werden.
    1. nutzung von bis zu vier Ventilen pro server am Trinkwasseranschluss
    2. nutzung von bis zu vier Ventilen an einer Pumpe. diese Pumpe kann geschaltet werden.
    3. nutzung von bis zu vier Ventilen an einer Pumpe. diese Pumpe kann geschaltet werden und zusätzliche überprüfung des Füllstandes, z.B. in
       einem Regenfass um das Laufen im Trocknen zu verhindern.


### Details zur Oberfläche
Die Oberfläche unterstützt bis zu 20 Beete. das Aktuelle Wetter und auch die aktuelle feuchte werden im  Allgemein Tab angezeigt.

[![Allgemein Screenshot][product-screenshot]]()

Im Tab Beete ist eine detalierte Betrachtung jedes Beets möglich. vom ventil zustand, bis hin zur Manuellen Bewässerung oder auch ob eine Automatisierte Bewässerung geplant ist erfährst du hier alles.

[![Beete Screenshot][beet-screenshot]]()

Im Tab Allgemeine Einstellungen kannst du alles einstellen, ob deine Oberfläche Passwort geschützt sein soll, bis hin zu den Automatischen Bewässerungs Kriterien.

[![einst Screenshot][einst-screenshot]]()

Im Tab Beet Einstellungen kannst du alles zu den Beeten einstellen. wie, den Namen oder auch die Adressen der Feuchte bzw Ventil Sensoren.

[![beet einst Screenshot][beeteinst-screenshot]]()


### Was Brauche ich

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
2. clone das Repository für den Feuchte Server und Trage SSID und Passwort deines Netzwerks hier ein. 
2.1. flashe einen ESP8266 mit dieser Software und warte bis dieser sich mit deinem Router verbunden hat.
2.2. nach dem du den Feuchte Sensor an den Pin A0 angelötet hast, musst du diesen Noch kallibrieren mit (im webbrowser auf einem gerät das im selben netzwerk ist): http.//IP_Des_ESP/kalibrierung?typ=0
    für Trocken und dann tue den Sensor ins wasser und http.//IP_Des_ESP/kalibrierung?typ=1 für nass. die IP des ESP muss im Haupt Server Eingetragen Werden.
2.3 nach der Einrichtung stelle bei deinem Router ein, dass die IP des ESP8266 immer gleich bleibt.
3. clone das Repository für den ventil Server und Trage SSID und Passwort deines Netzwerks ein. zusätzlich die anzahl der Genutzten Ventile und ob eine Pumpe verwendet wird und ob füllstand verwendet wird.
3.1 flashe einen ESP8266 mit dieser Software und warte bis dieser sich mit deinem Router verbunden hat. verbinde die Relays mit dem im Code genannten Pins. 
3.2 trage die IP des Ventilservers im Hauptserver ein.
3.3 nach der Einrichtung stelle bei deinem Router ein, dass die IP des ESP8266 immer gleich bleibt.
Fertig!
Schalt diagramme Folgen noch


## Danksagung

- <a href="https://github.com/s00500">s00500 zur Bereitstellung seiner genialen UI Lib</a>




[product-screenshot]: images/allgemein.png
[beet-screenshot]: images/beete.png
[einst-screenshot]: images/einstellungenAllg.png
[beeteinst-screenshot]: images/beet-einst.png