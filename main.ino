// Include the necessary library files
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <NewPing.h>

// Blynk auth token and WiFi credentials
char auth[] = "lGP6cpN_SjbTlVvZp-04WlSSPVKbHLqp"; // Auth token
char ssid[] = "You can go bankrupt"; // WiFi name
char pass[] = "test"; // WiFi password

BlynkTimer timer;
bool Relay = 0;

// Define component pins
#define soilMoistureSensor A0
#define waterPump D3
#define DHTPIN D1
#define DHTTYPE DHT11
#define LDR_PIN A0
#define TRIGGER_PIN D2
#define ECHO_PIN D3
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters)

DHT dht(DHTPIN, DHTTYPE);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH);

  dht.begin();
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  // Call the functions at intervals
  timer.setInterval(1000L, soilMoistureSensorFunction);
  timer.setInterval(2000L, sendTemperatureHumidity);
  timer.setInterval(2000L, sendLDRData);
  timer.setInterval(2000L, checkWaterLevel);
}

// Get the button value
BLYNK_WRITE(V1) {
  Relay = param.asInt();

  if (Relay == 1) {
    digitalWrite(waterPump, LOW);
  } else {
    digitalWrite(waterPump, HIGH);
  }
}

// Get the soil moisture values
void soilMoistureSensorFunction() {
  int value = analogRead(soilMoistureSensor);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V0, value);

  // Control the pump based on soil moisture and water level
  int distance = sonar.ping_cm();
  if (distance > 0 && distance <= 10 && value < 30) {
    digitalWrite(waterPump, LOW);
  } else {
    digitalWrite(waterPump, HIGH);
  }
}

// Get the DHT11 temperature and humidity values
void sendTemperatureHumidity() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V2, h);
  Blynk.virtualWrite(V3, t);
}

// Get the LDR values
void sendLDRData() {
  int ldrValue = analogRead(LDR_PIN);
  Blynk.virtualWrite(V6, ldrValue);
}

// Check the water level using the ultrasonic sensor
void checkWaterLevel() {
  int distance = sonar.ping_cm();
  if (distance > 10) { // If distance is greater than 10 cm, water level is low
    Blynk.virtualWrite(V7, "Water level low. Refill the tank!");
  } else {
    Blynk.virtualWrite(V7, "Water level sufficient.");
  }
}

void loop() {
  Blynk.run(); // Run the Blynk library
  timer.run(); // Run the Blynk timer
}
