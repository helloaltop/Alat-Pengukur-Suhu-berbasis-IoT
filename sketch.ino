#include <WiFi.h>
#include "ThingSpeak.h"
#include "DHTesp.h"

unsigned long myChannelNumber = 1;
const char *myWriteAPIKey = "P3IPVWCSRD332ESU";
WiFiClient  client;


const int DHT_PIN = 15;

DHTesp dhtSensor;

void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  WiFi.begin("Wokwi-GUEST", "", 6);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  ThingSpeak.begin(client);
}

void loop() {
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  Serial.println("---");
  delay(1000);

  int x = ThingSpeak.writeField(myChannelNumber, 1, data.temperature, myWriteAPIKey);
  if(x == 200){
  Serial.println("Channel update successful.");
  }
  else{
  Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(30000); // TODO: Build something amazing!
}
