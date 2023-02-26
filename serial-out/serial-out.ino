#include "DHTesp.h"
#define AOUT_PIN A0 

DHTesp dht;

void setup() {
  Serial.begin(115200); // use this baud rate in serial monitor to see stuff
  dht.setup(D1, DHTesp::DHT11); // Connect DHT sensor to D1
}

void loop() {
  // read humidity
  float humi  = dht.getHumidity();
  // read temperature in Celsius
  float tempC = dht.getTemperature();
  // read soil
  int soil = analogRead(AOUT_PIN); // read the analog value from sensor

  // check whether the reading is successful or not
  if (isnan(tempC) || isnan(humi)) {
    Serial.println("Failed to read from DHT sensor!");
  } if (isnan(soil)) { 
    Serial.println("Failed to read from soil sensor!");
  } else {
    
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");

    Serial.print("  |  ");

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print(" C  ");

    Serial.print("  |  ");

    Serial.print("Moisture value: ");
    Serial.println(soil);

  }

  // wait a 2 seconds between readings
  delay(2000);
}