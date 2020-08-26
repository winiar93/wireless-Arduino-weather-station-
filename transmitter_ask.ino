
#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <Wire.h>
#include <SPI.h>

#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#endif

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)
RH_ASK driver(2000, 3, 4, 0); // ATTiny, RX on D3 (pin 2 on attiny85) TX on D4 (pin 3 on attiny85), 
Adafruit_BME680 bme;

struct dataStructure
{
  byte id;
  float temp;
  float pressure;
  float hum;
  float gasres;
  float alt;
};

typedef struct dataStructure Package;
Package data;

void setup()
{
#ifdef RH_HAVE_SERIAL
    Serial.begin(9600);	  // Debugging only
#endif
    if (!driver.init())
    
#ifdef RH_HAVE_SERIAL
         Serial.println("init failed");
#else
  ;
#endif         
bme.begin();
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void loop()
{
  uint8_t buf[11];
    uint8_t buflen = sizeof(buf);

  data.id = 1;
  bme.performReading();
  data.temp = bme.temperature;
  data.pressure = bme.pressure;
  data.hum = bme.humidity;
  data.gasres = bme.gas_resistance;
  data.alt = bme.readAltitude(SEALEVELPRESSURE_HPA);
  Serial.print(data.temp);
  Serial.print(" , "); 
  Serial.print(data.pressure / 100);
  Serial.print(" , "); 
  Serial.print(data.hum);
  Serial.print(" , ");
  Serial.print(data.gasres / 1000.0);
  Serial.print(" , ");
  Serial.print(data.alt);
  Serial.println();



 

   driver.send((uint8_t *)&data, sizeof(data));
    driver.waitPacketSent();
    delay(2000);
  
}
