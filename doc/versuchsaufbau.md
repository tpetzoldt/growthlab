---
title: "Versuchsaufbau"
author: "Thomas Petzoldt"
date: "2019-09-17"
output: html_document
---

# Grundidee

Die Grundidee besteht praktisch in einer "Lichtschranke", bestehend aus einer LED 
einem Lichtsensor und einem Messger�t. Das Prinzip �hnelt einem Photometer, allerdings
wird auf Pr�zisionsoptik und -mechanik verzichtet, um einen kosteng�nstigen Nachbau
zu erm�glichen.

Au�erdem kann im Unterschied zu einem typischen Photometer direkt durch das Glas 
der Flasche gemessen werden. Das ist optisch zwar wesentlich ung�nstiger als eine
K�vette, erm�glicht jedoch Messungen in geschlossenen Kolben oder Flaschen.

Je nach Ausbaustufe kann die Messung manuell erfolgen oder mit einem Mikrocontroller.
Dieser erlaubt dann auch weitere Steuerungsaufgaben, z.B. Licht und R�hrer.

Das Experiment ist als Sch�ler-, Studien- und Praktikumsexperiment vorgesehen. 
Bei entsprechend h�herem Aufwand und Kosten f�r Mechanik, Optik und Elektronik 
ist w�re eine Weiterentwicklung f�r Forschungszwecke denkbar, allerdings sind
solche Ger�te bereits kommerziell erh�ltlich.

Im folgenden soll der Versuch, ausgehend von der Grundidee, schrittweise bis zur
Vollautomatisierung und zur Integration in ein Netzwerk (IoT -- Internet of Things)
vorgestellt werden.

Das hier vorgefundene Dokument stellt den jeweiligen Arbeitsstand dar.

# Phytoplanktonkultur

Im vorliegenden Fall wird eine Kultur der Gr�nalge *Scenedesmus* verwendet. Diese 
Art ist sehr konkurrenzstark und kann unsteril gehalten werden, was den Versuch sehr 
erleichtert. Prinzipiell kann man auch eine sogenannte Verdr�ngungskultur aus einer
Freilandprobe ansetzen.

Als N�hrl�sung wird ein handels�blicher mineralischer Blumend�nger 
benutzt. Hier kann man schon einmal das chemische Rechnen �ben. Mehr dazu folgt sp�ter.

# Experiment 1: Manuelle Messung mit einem Voltmeter

Die einfachste Aufbaustufe zeigt bereits das Grundprinzip. Die Messtrecke wird durch eine
LED und ein Photowiderstand gebildet, die in einem
Gestell befestigt sind. Das Gestell besteht im vorliegenden Fall aus einer Sperrholzgrundplatte, 
Gewindestangen (M4) und etwas Plexiglas, k�nnte im Prinzip aber auch aus dem Lego- oder Metallbaukasten stammen.

Als elektronische Bauelemente gen�gen neben der LED und dem Photowiderstand ein sogenanntes *Breadboard* (Steckbrett),
2 Widerst�nde, Steckbr�cken bzw. etwas Draht und ein Voltmeter. Da nur Spannung gemessen werden muss, gen�gt ein preiswertes Ger�t. Zur LED ist zu sagen, dass es sich hier um eine preiswere Laser-LED (�hnlich einem Laserpointer) handelt. 
Diese besitzt sogar eine kleine Linse zur Fokussierung. Grunds�tzlich sind auch andere LEDs geeignet. Wichtig ist, dass
jede LED mit einem Vorwiderstand oder einer Konstantstromquelle (siehe unten) betrieben werden muss, sonst geht sie kaputt. Laser-LEDs sind besonders empfindlich.

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

Der Arduino Uno und seine kompatiblen Nachbauten (nur Uno genannt) sind Microcontroller-Bastelszene
praktisch die "Klassiker". Es gibt inzwischen zwar viel leistungsf�higere Controller: schneller, mehr Speicher, WLAN usw., aber der UNO ist nach wie vor weit verbreitet und besonders einfach zu programmieren.

Im folgenden Experiment wird das Voltmeter durch einen Uno ersetzt, die �brige 
Schaltung bleibt gleich. Die USB-Verbindung mit einem Computer hat gleich dreifache Bedeutung:

- Stromversorgung des Uno (Spannung 5V) 
- Programmierung des Uno mit der Arduino-IDE (IDE = ingegrierte Entwicklungsumgebung)
- Ausgabe der Daten auf dem Bildschirm mittels "Seriellem Monitor" bzw. "Seriellem Plotter" der Arduino-IDE


<img src="led-phot-arduino.png" alt="Messung Arduino" width="500"/>

## Der Code

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
ben�tigt und dass man beide Schaltkreise einfach parallel schalten kann.

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
Luxmeter einsetzen.


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

<img src="esp-full-experiment.jpg" alt="Experimenteller Aufbau" width="600"/>

<img src="esp-full-circuit.png" alt="Schaltplan" width="600"/>


# Tipps und Tricks

## Biologie

* Planktonkultur
* N�hrmedien
* Versuchsideen

## Elektronik

* Temperaturabh�ngigkeit von Sensor und Laserdiode
* Bau eines R�hrers
* Spannungsversorgung von LED-Streifen

## Programmierung

* Arduino / ESP
* Raspberry Pi
* Python-Server-Script und MariaDB-Datenbank
* Visualisierung mit R und Shiny

## Datenanalyse und Statistik




