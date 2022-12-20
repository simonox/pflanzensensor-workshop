#include <DHT.h>
#define DHT_SENSOR_PIN  21 // ESP32 pin GIOP21 connected to DHT11 sensor
#define DHT_SENSOR_TYPE DHT11
#define AOUT_PIN 36 // ESP32 pin GIOP36 (ADC0) that connects to AOUT pin of moisture sensor

DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

void setup() {
  Serial.begin(9600);
  dht_sensor.begin(); // initialize the DHT sensor
}

void loop() {
  // read humidity
  float humi  = dht_sensor.readHumidity();
  // read temperature in Celsius
  float tempC = dht_sensor.readTemperature();
  // read temperature in Fahrenheit
  float tempF = dht_sensor.readTemperature(true);

  // read soil
  int soil = analogRead(AOUT_PIN); // read the analog value from sensor


  // check whether the reading is successful or not
  if ( isnan(tempC) || isnan(tempF) || isnan(humi)) {
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
    Serial.print(tempF);
    Serial.print(" F");
    Serial.print("  |  ");
    Serial.print("Moisture value: ");
    Serial.println(soil);

  }

  // wait a 2 seconds between readings
  delay(2000);
}