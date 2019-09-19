---
title: "Versuchsaufbau"
author: "Thomas Petzoldt"
date: "2019-09-17"
output: 
  html_document:
    numbersections: true
    toc: true
    toc_float:
      collapsed: false
      smooth_scroll: true
    code_folding: show

---

# Grundidee

Die Grundidee besteht praktisch in einer "Lichtschranke", bestehend aus einer LED 
einem Lichtsensor und einem Messger�t. Das Prinzip �hnelt einem Photometer, allerdings
wird auf Pr�zisionsoptik und -mechanik verzichtet, um einen kosteng�nstigen Nachbau
zu erm�glichen.

Im Unterschied zu einem typischen Photometer kann direkt durch das Glas 
der Flasche gemessen werden. Das ist zwar optisch ung�nstiger als eine
K�vette, erm�glicht aber Messungen in geschlossenen Kolben oder Flaschen.

Je nach Ausbaustufe kann die Messung manuell erfolgen oder mit einem Mikrocontroller.
Dieser erlaubt dann auch weitere Steuerungsaufgaben, z.B. Licht und R�hrer.

Das Experiment ist als Sch�ler-, Studien- und Praktikumsexperiment vorgesehen. 
Bei entsprechend h�herem Aufwand und Kosten f�r Mechanik, Optik und Elektronik 
ist eine Weiterentwicklung f�r Forschungszwecke denkbar, allerdings sind
solche Ger�te bereits kommerziell erh�ltlich.

Im folgenden soll der Versuch, ausgehend von der Grundidee, schrittweise bis zur
Vollautomatisierung und zur Integration in ein Netzwerk (IoT -- Internet of Things)
vorgestellt werden.

Das hier vorgefundene Dokument stellt den jeweiligen Arbeitsstand dar.

# Phytoplanktonkultur

Im vorliegenden Fall wird eine Kultur der Gr�nalge *Scenedesmus* verwendet. Diese 
Art ist sehr konkurrenzstark und kann unsteril kultiviert werden, was den Versuch sehr 
erleichtert. Prinzipiell kann man auch eine sogenannte Verdr�ngungskultur aus einer
Freilandprobe ansetzen.

Als N�hrl�sung wird ein handels�blicher mineralischer Blumend�nger 
benutzt. Hier kann man schon einmal das chemische Rechnen �ben. Mehr dazu folgt sp�ter.

# Experiment 1: Manuelle Messung mit einem Voltmeter

Die einfachste Aufbaustufe zeigt bereits das Grundprinzip. Die Messtrecke wird durch eine
LED und ein Photowiderstand gebildet, die an einem
Gestell befestigt sind. Das Gestell besteht im vorliegenden Fall aus einer Sperrholzgrundplatte, 
Gewindestangen (M4) und etwas Plexiglas, k�nnte im Prinzip aber auch aus dem Lego- oder Metallbaukasten stammen.

Als elektronische Bauelemente gen�gen neben der LED und dem Photowiderstand ein sogenanntes *Breadboard* (Steckbrett),
2 Widerst�nde, Steckbr�cken bzw. etwas Draht und ein Voltmeter. Da nur Spannung gemessen werden muss, gen�gt ein preiswertes Ger�t. Zur LED ist zu sagen, dass es sich hier um eine g�nstige Laser-LED (�hnlich einem Laserpointer) handelt. 
Diese besitzt sogar eine kleine Linse zur Fokussierung. Grunds�tzlich sind auch andere LEDs geeignet. Wichtig ist, dass
eine LED fast immer mit einem Vorwiderstand oder einer Konstantstromquelle (siehe unten) betrieben werden muss, sonst geht sie kaputt. Laser-LEDs sind besonders empfindlich.

**Vorsicht:** Das man einen Laser nicht auf die Augen oder auf spiegelnde Fl�chen 
richtet, sollte selbstverst�ndlich sein. Achtung: auch die Flasche kann spiegeln!

Die gr�ne Farbe der Probe zeigt eine hohe Konzentration gegen Ende eines 
Wachstumsversuchs.

<!--
%![Manuelle Messung mit Voltmeter](led-phot-analog.jpg)
-->

<img src="led-phot-analog.jpg" alt="Manuelle Messung mit Voltmeter" width="500"/>
<img src="led-phot-analog-breadboard.png" alt="Schaltung auf dem Breadboard" width="260"/>

<!--
![Schaltung](led-phot-analog-breadboard.png)
-->


Die Schaltung (rechts) zeigt f�r die LED den Vorwiderstand und f�r den Photowiderstand 
den typischen Aufbau einer Spannungsteilers. Spannungen lassen sich grunds�tzlich 
einfacher und genauer messen als Str�me. Es empfiehlt sich, die Schaltung zun�chst 
auf dem Steckbrett aufzubauen. Wenn alles funktioniert, werden LED und Photowiderstand 
mit l�ngeren Leitungen versehen und am Gestell befestigt.

# Experiment 2: Messung mit einem Arduino Uno

Der [Arduino Uno](https://www.arduino.cc) und seine kompatiblen Nachbauten (nur Uno genannt) sind in der Mikrocontroller-Bastelszene
praktisch die "Klassiker". Es gibt inzwischen zwar viel leistungsf�higere Controller: schneller, mehr Speicher, WLAN usw., aber der UNO ist nach wie vor weit verbreitet und besonders einfach zu programmieren.

Im folgenden Experiment wird das Voltmeter durch einen Uno ersetzt, die �brige 
Schaltung bleibt gleich. Die USB-Verbindung mit einem Computer hat eine dreifache Funktion:

- Stromversorgung des Uno (Spannung 5V) 
- Programmierung des Uno mit der [Arduino-IDE](https://www.arduino.cc/en/Main/Software) (IDE = ingegrierte Entwicklungsumgebung)
- Ausgabe der Daten auf dem Bildschirm mittels "Seriellem Monitor" bzw. "Seriellem Plotter" der Arduino-IDE


<img src="led-phot-arduino.png" alt="Messung Arduino" width="500"/>

### Der Code

Eine Detaillierte Einf�hrung in die Mikrocontrollerprogrammierung w�rde den Rahmen dieses Projekts
sprengen. Die Installation Arduino-IDE sowie erste Gehversuche sind auf diversen Internetseiten sehr ausf�hrlich beschrieben, z.B. auf https://www.arduino.cc/en/Guide/HomePage

Wenn man die IDE installiert hat und das Blink-Beispiel funktioniert, kann man 
sich bereits and das unten stehende Beispiel trauen. Die Messwerte des Sensors 
erscheinen dann als relative Einheiten auf dem Computer.

```{C++}
/*
  Arduino analog light sensor example
  Output can be shown via the Arduino serial monitor or serial plotter
  License: public domain
*/

int sensorPin = A0;    // pin number where analog input is connected

void setup() {
  Serial.begin(115200);
}

void loop() {
  float sensorValue = analogRead(sensorPin);
  Serial.print("Light: ");
  Serial.println(sensorValue);
  delay(100);
}
```

# Experiment 3: Arduino mit digitalem Lichtsensor und eigenem Display

F�r das folgende Experiment ben�tigen wir einen digitalen Lichtsensor (BH1750) 
und ein OLED-Display (z.B. ein SH1106 mit 128 x 64 Pixeln), beide mit 
sogenannter I2C-Schnittstelle. Der Vorteil on I2C ist, dass man nur 4 Leitungen 
ben�tigt (Stromversorgung, Masse und 2 Datenleitungen) und dass mehrere beide Schaltkreise 
einfach parallel schalten kann.

Prinzipiell sind auch andere Sensoren und Displays geeignet. In diesem Fall sind 
Schaltung und Code entsprechend anzupassen. Vorher sollte man die Chips 
mit den dazuge�rigen Beispielen einzeln ausprobieren.


<img src="led-phot-digital-arduino.jpg" alt="Arduino mit digitalem Sensor und digitalem Display" width="600"/>

<img src="led-phot-digital-arduino-breadboard.png" alt="Schaltung auf dem Breadboard" width="600"/>

Die Abbildungen zeigen oben ein Foto (ohne die Laserdiodenschaltung) 
und unten den kompletten Schaltungsaufbau auf dem Breadboard. Zur Vermeidung von Kabelsalat
wurde der Sensor an ein Flachbandkabel gel�tet. F�r den Anschluss an den Arduino dienen vier 
Adern eines Dupont-Jumperkabels. Im Foto wurde im Interesse der �bersicht die 
Laserdiodenschaltung weggelassen. Der Versuchsaufbau l�sst sich auch als behelfsm��iges
Luxmeter einsetzen. Man beachte, dass die Stromversorgung �ber ein Netzteil erfolgen kann 
(runde Buchse) und nicht �ber USB, d.h. die Schaltung ist nach der Programmierung
autark ohne Computer lauff�hig.


```{C++}
/*
  Combines the BH1750 digital Light sensor with an OLED display

  Purpose:
  - simple lux meter 
    (the values are of course not precise, but surprisingly close 
     to a commercial hobby lux meter)
  - in combination with a (laser) LED: digital light sensor for growth experiments

  Connection of light sensor and display to the controller
  The I2C interface allows to connect both in parallel.
  
  Sensor    Arduino Uno
  VCC        3V3
  GND        GND
  SDA        SDA
  SCL        SCL

  Note: available OLED displays have different pinout.
        Be very careful, NEVER CONFUSE 3.3V and GND!

  License: GPL 2.0
*/


//https://github.com/olikraus/u8g2/wiki/u8x8reference
#include <U8x8lib.h>   // OLED display library

// Create the Lightsensor instance
#include <BH1750FVI.h> // light sensor library

// enable one of the following lines to set resolution
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
//BH1750FVI LightSensor(BH1750FVI::k_DevModeContHighRes);

// change the following line if you own a different display
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(9600);
  LightSensor.begin();  

  /* Initialize OLED display */
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_7x14_1x2_r);
  u8x8.drawString(0,0,"Start ...");
  delay(100);
  u8x8.clearDisplay();
}

void loop() {
  uint16_t lux = LightSensor.GetLightIntensity();

  // Output to Serial monitor or plotter of the Arduino IDE
  Serial.print("Light: ");
  Serial.println(lux);

  // Output to the OLED display
  u8x8.drawString(0, 2,"Light          "); //overwrite leftover chars from lux
  u8x8.drawString(7, 2, String(lux).c_str());
  delay(1000);
}

```


# Ausblick: Internet of Things: Automatische Messeinrichtung mit WLAN

Die oben beschriebene Versuchsanordnung l�sst sich beliebig anpassen und erweitern. 
In einer weiteren Ausbaustufe soll der Controller vollautomatisch agieren und die
Messdaten abspeichern. Da der Uno hier schnell an seine Grenzen gelangt, sollte man
einen leistungsf�higen Controller einsetzen, z.B. einen ESP8266 oder einen ESP32.
Entwicklerboards mit diesen Controllern sind kaum teurer als ein Arduino, bieten 
jedoch viel mehr Leistung: kleiner, schneller, mehr Speicher, flexiblere Schnittstellen, 
WLAN, Bluetooth, Stromsparfunktionen.

F�r den folgenden Aufbau wurde ein "ESP32 Dev Kit C" verwendet. Er steuert folgende Funktionen:

* Messung der optischen Dichte (mit Photowiderstand)
* Messung der Temperatur mit ein ider mehreren digitalen temperatursensoren (DS18B20)
* An- und ausschalten der Laserdiode
* Steuerung der Beleuchtung (eines LED-Streifens): An/Aus, Helligkeit
* Steuerung eines Magnetr�hrers
* Zeitsynchronisation von einem Internet-Zeitserver
* WLAN-�bertragung von Messdaten und Steuerinformationen �berdas MQTT-Protokoll 
  an einen Datenbankserver.
* M�glichkeit, die Steuerungssoftware im laufenden Betrieb "over the air" 
  (OTA per WLAN) zu aktualisieren. �ber diesen Weg lassen sich z.B. das Messintervall
  oder das R�hr- oder Lichtregime (Dauerlicht, 16:8, gepulst) ver�ndern.

<img src="esp-full-experiment.jpg" alt="Experimenteller Aufbau" width="600"/>

<img src="esp-full-circuit.png" alt="Schaltplan" width="600"/>

### Spannungs- und Stromversorgung

Die f�r den Versuchsaufbau verwendeten Bauelemente ben�tigen unterschiedliche 
Spannungen (z.B. 3.3V. 5V, 12V, 24V) und Str�me. W�hrend der ESP32 und die Sensoren 
3.3V ben�tigen (und keinesfalls mehr als 3.6V), ben�tigt der verwendete R�hrermotor 5V
und die LED-Streifen je nach Typ 12V oder 18-24V.

Diese unterschiedlichen Anforderungen wurden wie folgt gel�st.

#### Spannung

* 5V: der ESP32 wird �ber seinen USB-Eingang mit 5V aus einem Handynetzteil versorgt. 
  Der interne Spannungsregler des "Dev Boards" stellt daraus die 3.3V her.
* 3.3V: Die Sensoren (Photowiderstand, temperatursensoren) m�ssen mit dem selben 
Pegel arbeiten wie der ESP. Die daf�r ben�tigte Spannung wird vom 3.3V-Ausgang 
des "Dev Boards" abgezweigt.
* 12V bzw. 24V: Hierzu wird ein kleines aber sehr effizientes Transformatormodul
benutzt (MT3608 DC-DC Step up Modul, auf dem Foto die kleinere Platine). 
Mit Hilfe eines Einstellpotentiometers (blaues bauteil auf der Platine) 
l�sst sich die gew�nschte Ausgangsspannung einstellen. Je nach Leistungsf�higkeit der Handy-Netzteils und der maximalen Leistungsaufnahme des LED-Streifens kann die volle Leistung eventuell nicht ganz abgerufen werden, damit f�r den ESP und die anderen bauteile gen�gend Strom �brigbleibt. Im vorliegenden Fall wird der 24V-LED-Streifen nur mit 20V betrieben.

Details sind dem Schaltplan und der folgenden Erl�uterung zu entnehmen.

#### Strom

Motoren und LEDs ben�tigen eventuell mehr Strom (und ggf. eine andere Spannung) 
als der ESP32 von sich aus bereitstellen kann. Prinzipiell kann man das mit Relais l�sen.
Als energiesparendere (und billigere) Alternative wurden f�r diesen Zweck Transistoren verwendet,
konkret MOSFETS vom Typ IRLZ24N. Sie bieten f�r den verwendungszweck gen�gend Leistungsreserven.

Mit Hilfe der MOSFETs lassen sich die jeweils ben�tigten Spannungen schalten.

#### Temperaturabh�ngigkeit

Laser-LEDs sind stark temperaturabh�ngig. Bei einem ersten Versuch kam es trotz 
temperiertem Raum zu relativ starken Schwankungen des Messignals. Eine vorgeschaltete
Konstantstromquelle (CL2N3-G, 20mA, 0.6W) konnte die Temperaturabh�ngigkeit sehr stark vermindern.
Das Bauteil hat 2 beschaltete Pins und wird einfach in Reihe zum Laser eingef�gt. 
Da am Bauteil jedoch immer ein gewisser Spannungsabfall stattfindet, ben�tigt 
man nun allerdings eine Spannung von mindestens circa 7 Volt, so dass die Laser-LED
nun �ber die 12 bzw. 20V-Leitung versorgt werden muss. Ein zus�tzlicher Vorwiderstand 
(33o Ohm) sorgt daf�r, dass bei 20V die Verlustleistung nicht allein 
an der Konstantstromquelle abf�llt.

#### R�hrer

Als R�hrer kommt ein Selbstbau-Magnetr�hrer zum Einsatz, bestehend aus 
einem kleinen PC-L�fter mit aufgeklebten Neodym-Magnetw�rfeln. Da Motoren selbst 
Magnete besitzen, funktioniert das nur bei bestimmten Typen (vorher ausprobieren).

Im Versuchsgef�� befindet sich ein handels�blicher Labor-Magnetr�hrer 
(sogenannter [R�hrfisch](https://de.wikipedia.org/wiki/Magnetr%C3%BChrer)) 
oder ein Selbstbau aus Schrumpfschlauch, Magnetw�rfeln und Kleber.

# Folgt demn�chst ...

## Biologie

* Planktonkultur
* N�hrmedien
* Versuche und Ideen


## Programmierung

* Arduino / ESP
* Raspberry Pi
* Python-Server-Script und MariaDB-Datenbank
* Visualisierung mit R und Shiny

## Datenanalyse und Statistik

* Datenmanagement
* Plotten, Zeitreihen, Gl�ttung
* ANOVA-Beispiel




