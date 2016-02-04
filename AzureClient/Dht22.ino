#include "DHT.h"

#define DHTPIN22 2     // what digital pin we're connected to
#define DHTTYPE22 DHT22   // DHT 22  (AM2302), AM2321

DHT dht22(DHTPIN22, DHTTYPE22);
float dht22Calibration;
bool dht22Initialised = false;

void initDht22(){
  if (dht22Initialised) { return; }
  
  dht22.begin();
  dht22Calibration = getTemperatureCalibration();
  delay(50);

  dht22Initialised = true;
}

void getDht22Readings(){
  int retryCount = 0;
  initDht22();

  do {  
    data.temperature = dht22.readTemperature(); 
    data.humidity = dht22.readHumidity();
  } while ((isnan(data.temperature) || isnan(data.humidity)) && ++retryCount < 10);
}

