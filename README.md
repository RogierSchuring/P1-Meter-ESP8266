# P1-Meter-ESP8266
Software for the ESP2866 that sends P1 smart meter data to Domoticz (with CRC checking, OTA firmware updates, crash protection and a simple webserver)

### Installation instrucions
- Make sure that your ESP8266 can be flashed from the Arduino environnment: https://github.com/esp8266/Arduino
- Install the SoftSerial library from: https://github.com/plerup/espsoftwareserial
- Place all files from this repository in a directory. Open the .ino file.
- Adjust WIFI, Domoticz and debug settings at the top of the file
- Compile and flash

### Connection of the P1 meter to the ESP8266
You need to connect the smart meter with a RJ11 connector. This is the pinout to use
![RJ11 P1 connetor](http://gejanssen.com/howto/Slimme-meter-uitlezen/RJ11-pinout.png)

Connect GND->GND on ESP, RTS->3.3V on ESP and RxD->any digital pin on ESP. In this sketch I use D5

### Generic Info
This repo is forked from Jantenhove: https://github.com/jantenhove/P1-Meter-ESP8266
Webserver comes from an early version of ESP Easy: https://github.com/letscontrolit/ESPEasy

### Added functionality
- Counter that will reset the ESP when 10 consecutive CRC Errors are encountered.
- Webserver to view some generic info about the ESP and a logging page where you can see the last 40 results.
