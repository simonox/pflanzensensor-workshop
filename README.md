# ESP Pflanzensensor Workshop

Die Projektdokumentation zum Pflanzensensor Workshop.

<https://curious.bio/2022/11/remote-chaos-experience/>

## Komponenten

### Mikrocontroller

* [Wemos D1 mini ESP-8266](https://www.wemos.cc/en/latest/d1/d1_mini.html)

### Luftfeuchtigkeits- und Temperatursensor

* [Asair DHT11](https://asairsensors.com/product/dht11-sensor/)
* [Datenblatt](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf)

### Bodenfeuchtesensor

* Capacitive Soil Moisture Sensor v1.2
* analoges Signal!
* [Datenblatt](https://media.digikey.com/pdf/data%20sheets/dfrobot%20pdfs/sen0193_web.pdf)
* <https://thecavepearlproject.org/2020/10/27/hacking-a-capacitive-soil-moisture-sensor-for-frequency-output/>

## Systemanforderungen

* [Python Runtime Environment](https://www.python.org/)
* [VSCodium Code Editor](https://vscodium.com/)
* [Fritzing Prototyping Editor](https://fritzing.org/)

## Schaltplan

![Beadboard](breadboard.png "breadboard")

![Schaltplan](schaltplan.png "schaltplan")

## Arduino IDE

Download hier: https://www.arduino.cc/

Um mit den ESP-basierten Boards entwickeln zu können, müssen diese hinzugefügt werden (Einstellungen -> Board Manager URLs): "http://arduino.esp8266.com/stable/package_esp8266com_index.json,https://dl.espressif.com/dl/package_esp32_index.json"

![Einstellungen](preferences.png "board manager URLs")

Um den DHT11 auslesen, benötigen wir zusätzlich noch eine Library (Tools -> Manage Libraries): "DHT sensor library for ESPx by beegee_tokyo":

![Library Manager](librarymanager.png "library manager")

Zum Flashen (Upload) muss das richtige Board "LOLIN(WEMOS) D1 mino (clone)" und der richtige Port (ein serieller Port, an dem das Board über USB angeschlossen ist) ausgewählt sein.

![Flash](flash.png "flash")


Hier hilft die Doku sicherlich weiter: https://support.arduino.cc/hc/en-us/articles/4733418441116-Upload-a-sketch-in-Arduino-IDE


## Beispiele

Es gibt zwei Beispiele. 
* `serial-out` gibt einfach Messwerte über den Serial Monitor aus.
* `first-webserver` präsentiert die gleichen Messerte auf einer Website

Damit der Webserver im eigenen Netzwerk funktioniert, ist es am einfachsten, diese Zeile zu löschen: 
```
#include "credentials.h" // put your WIFI credentials in here
```

Statt dessen kann man dann die SSID und das Passwort des eigenen WLANS in diesen Zeilen eintragen:
```
// Replace with your network credentials
const char* ssid = secrect_ssid;
const char* password = secret_password;
```

Zum Beispiel so:

```
// Replace with your network credentials
const char* ssid = "MeinKabelWifi";
const char* password = "letMeIn123";
```

## ESPHome

### CLI

```sh
esphome --help
usage: esphome [-h] [-v] [-q] [-s key value] command ...

positional arguments:
  command               Command to run:
    config              Validate the configuration and spit it out.
    compile             Read the configuration and compile a program.
    upload              Validate the configuration and upload the latest binary.
    logs                Validate the configuration and show all logs.
    run                 Validate the configuration, create a binary, upload it, and start logs.
    clean-mqtt          Helper to clear retained messages from an MQTT topic.
    wizard              A helpful setup wizard that will guide you through setting up ESPHome.
    mqtt-fingerprint    Get the SSL fingerprint from a MQTT broker.
    version             Print the ESPHome version and exit.
    clean               Delete all temporary build files.
    dashboard           Create a simple web server for a dashboard.
    rename              Rename a device in YAML, compile the binary and upload it.

options:
  -h, --help            show this help message and exit
  -v, --verbose         Enable verbose ESPHome logs.
  -q, --quiet           Disable all ESPHome logs.
  -s key value, --substitution key value
                        Add a substitution
```

```sh
esphome compile esphome.yaml
esphome upload esphome.yaml
```

