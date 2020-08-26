
#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif

RH_ASK driver(2000, 4, 3, 0); // ATTiny, RX on D3 (pin 2 on attiny85) TX on D4 (pin 3 on attiny85), 

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
}

void loop()
{
    uint8_t buf[sizeof(data)];
    uint8_t buflen = sizeof(data);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
	    memcpy(&data,&buf,buflen);

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

	// Message with a good checksum received, dump it.
	//driver.printBuffer(buf, buflen);

  }

}
