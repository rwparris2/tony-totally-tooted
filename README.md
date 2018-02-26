Tony Totally Tooted 🍑💨 💩
==========================

> A NodeMCU Project for reporting Tony's toots to his workforce.

Setup
-----

### Hardware

* NodeMCU Dev Kit
* MQ-4 Sensor
* 128x64 OLED Display

#### Wiring Connections

```
Devkit <> MQ-4
-----------------
   VIN <> VCC
   GND <> GND
    A0 <> A0
    D0 <> D0
```

```
Devkit <> OLED
-----------------
   VIN <> VCC
   GND <> GND
    D2 <> SDA
    D1 <> SCL
```

### Development Environment

* install arduino ide
* install esp266 board to ide
  * arduino ide > preferences > "additional boards manager urls": http://arduino.esp8266.com/stable/package_esp8266com_index.json
  * arduino ide > tools > board > boards manager > "esp266" > install
* install ACROBOTIC_SSD1306 library
  * arduino ide > sketch > include library > manage libraries > "acrobotic ssd1306"
