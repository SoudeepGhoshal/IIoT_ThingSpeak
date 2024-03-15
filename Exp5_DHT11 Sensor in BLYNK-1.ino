/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL3v0epPtII"
#define BLYNK_TEMPLATE_NAME "Esp32 DHT11"
#define BLYNK_AUTH_TOKEN "f8XEulC6ry-vkLRMJ1gZ5jBCn7wqgiCh"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <DHT.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Soudeep (OnePlus Nord)";
char pass[] = "12345678";
char auth[] = "f8XEulC6ry-vkLRMJ1gZ5jBCn7wqgiCh";

#define DHTPIN 13 // GPIO pin where the DHT11 is connected
#define DHTTYPE DHT11 // Type of the sensor

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensorData()
{
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("% | ");
  Blynk.virtualWrite(V1, humidity);     // Virtual pin 5 for humidity
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
  Blynk.virtualWrite(V0, temperature);  // Virtual pin 6 for temperature
}

void setup()
{
  Serial.begin(115200);
  dht.begin();

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(2000L, sendSensorData);  // Send sensor data every 2 seconds
}

void loop()
{
  Blynk.run();
  timer.run();
}