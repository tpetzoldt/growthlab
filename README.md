# growthlab

## Reale und virtuelle Wachstumsexperimente für Schule und Studium

## Real and virtual growth experiments for highschool and university students

Note to English speaking people: This repository is partly in German to support use by private persons and in schools in Germany.

Wachstums- und Verlustprozesse spielen in den ökologischen Wissenschaften eine entscheidende Rolle, nicht nur bei Symbolarten wie dem amerikanischen Bison [1], sondern auch bei Bakterien, beim Phytoplankton oder bei Fischen. Biologische Systeme besitzen eine vielfältige Dynamik und sind häufig komplex und rückgekoppelt, Simulationen und Experimente tragen zum Verständnis bei.

Das Repository ist eine lose Sammlung von Codes und Beschreibungen realer und virtueller Experimente zum Thema Wachstum für Schule und Studium. Beispiele sind web-basierte Simulationen (Laborversuch, Kläranlage, Flachsee) auf dem Computer oder Tablet, zum anderen um kleine Laborexperimente, die die reale mit der virtuellen Welt verbinden. Ziel ist Anschaulichkeit und ein einfacher Einstieg, die Luft nach oben ist offen.

Mit Hilfe von Flaschenversuchen wird das Populationswachstum einer Mikroalgenkultur beobachtet, z.B. von Scenedesmus. Die Messeinrichtung besteht aus kostengünstigen Bauteilen und eignet sich für Praktikumsversuche, Schulexperimente und Hobbyforscher. Das Grundprinzip ist ein Gestell mit roter Laserdiode, einem Fotowiderstand und einem Temperatursensor sowie einer LED-Beleuchtung und einem selbstgebauten Magnetrührer. Für die Stromversorgung genügt ein 5V-USB-Netzteil, z.B. von einem Handy. Die Messung kann direkt in der Flasche erfolgen, ohne den Versuch zu unterbrechen.

Die optische Dichte der Planktonkultur wird im einfachsten Fall manuell mit einem Voltmeter gemessen. In der vollen Ausbaustufe erfolgt die Messung mit einem WLAN-fähigen Mikrocontroller (Espressif ESP32), der gleichzeitig Beleuchtung und Rührer steuert, die Temperatur überwacht und die Daten an einen Server (z.B. einen Raspberry Pi „Bastelcomputer“) oder einen Cloudservice überträgt.

Je nach Ausbaustufe ist das Experiment sehr einfach und erfordert weder Programmierung noch den Umgang mit einem Lötkolben. Im größeren Maßstab kann es ein fächerübergreifendes „Maker-Projekt“ (siehe [1,2]) für Teams werden: mechanischer Aufbau der Versuchsanordnung, Aufbau einer Schaltung, Mikrocontroller-Programmierung, Datenübertragung („Internet of Things“), Finden und Kennenlernen geeigneter Organismen, mikroskopische oder fotometrische Kalibrierung, Herstellen von Kulturmedien, Datenbankstruktur, statistische Datenanalyse und mechanistische Modellierung.

Der Versuchsaufbau wurde im Rahmen eines Schülerpraktikums (Gymnasium 11. Klasse) entwickelt. Die gewonnen Daten werden in Kursen zu ökologischer Statistik und Modellierung verwendet.

Ausführliche Dokumentation auf https://tpetzoldt.github.io/growthlab

* Versuchsaufbau: https://tpetzoldt.github.io/growthlab/doc/versuchsaufbau.html
* Poster: https://tpetzoldt.github.io/growthlab/doc/petzoldt_dgl_2019_public.pdf
* Code-Beispiele: https://github.com/tpetzoldt/growthlab/tree/master/src

Literatur

[1] Snider, S. B. & Brimlow, J. N. (2013) An Introduction to Population Growth. Nature Education Knowledge 4(4):3 https://www.nature.com/scitable/knowledge/library/an-introduction-to-population-growth-84225544/

[2] Obama, B. (2014) Nation of Makers. https://obamawhitehouse.archives.gov/nation-of-makers abgerufen am 2019-05-28

[3] Wikipedia (2019) Makerbewegung. https://de.wikipedia.org/wiki/Maker abgerufen am 2019-05-28

Autor: [tpetzoldt](https://github.com/tpetzoldt)
