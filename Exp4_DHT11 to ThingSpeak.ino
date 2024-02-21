#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define DHTPIN 27 // GPIO pin where the DHT11 is connected
#define DHTTYPE DHT11 // Type of the sensor

const char *ssid = "Soudeep (OnePlus Nord)";
const char *password = "12345678";
const char *thingSpeakApiKey = "7JMQLCD5UM43MTC3";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  delay(2000); // Wait for 2 seconds between measurements

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the temperature and humidity values.
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  // Send data to ThingSpeak
  sendToThingSpeak(temperature, humidity);
}

void sendToThingSpeak(float temperature, float humidity) {
  HTTPClient http;

  String url = "http://api.thingspeak.com/update";
  url += "?api_key=";
  url += thingSpeakApiKey;
  url += "&field1=";
  url += String(temperature);
  url += "&field2=";
  url += String(humidity);

  http.begin(url);

  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}
