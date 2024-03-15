#define BLYNK_TEMPLATE_ID "TMPL3v0epPtII"
#define BLYNK_TEMPLATE_NAME "Esp32 DHT11"
#define BLYNK_AUTH_TOKEN "f8XEulC6ry-vkLRMJ1gZ5jBCn7wqgiCh"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Soudeep (OnePlus Nord)";   
char pass[] = "12345678";

#define DHTPIN 26          // What digital pin we're connected to
int LED1 = 27; // Define LED as an Integer (whole numbers) and pin D8 on Wemos D1 Mini Pro

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(LED1, OUTPUT); //Set the LED (D33) as an output
  pinMode(27, OUTPUT); //Set the LED (D33) as an output
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);

}

void loop()
{
   float h = dht.readHumidity();
   float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("%");

    Serial.print("  |  ");

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println("°C  ~  ");
 
  Blynk.run();
  timer.run();
}
// This function will be called every time button Widget
// in Blynk app writes values to the Virtual Pin V0
BLYNK_WRITE(V2) {
 int pinValue = param.asInt(); // Assigning incoming value from pin V0 to a variable
 if (pinValue == 1) {
    digitalWrite(LED1, HIGH); // Turn LED on.
  } else {
    digitalWrite(LED1, LOW); // Turn LED off.
 }
}