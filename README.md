# wireless-Arduino-weather-station-
Wireless Arduino weather station based on bme680.

With additional diy antenna its possible to achive 50m range 
Cut 173mm copper wire and solder on 'ANT' pad rf module pcb.

Used patrs:

-Arduino nano
-bme680 sensor with VOC ( volatile organic compounds)
-simple 433mhz radio transmitter


needed libraries:

-Radio head 433mhz

-Adafruit bme680 library


WIRING:

BME_SCK 13

BME_MISO 12

BME_MOSI 11

BME_CS 10

Rf module

RX D3

TX D4
