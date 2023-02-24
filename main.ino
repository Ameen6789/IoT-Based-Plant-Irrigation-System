// Include Library
#include <ESP8266WiFi.h>
#include <TimeLib.h>


// Constants
#define SSID            ""
#define PWD             ""
#define solenoidPin     D1


void setup()
{
  Serial.begin(115200);
  pinMode(solenoidPin, OUTPUT);
  digitalWrite(solenoidPin, LOW);
  Serial.println();

  WiFi.begin(SSID, PWD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  server.begin();
  Serial.println("Server started");
}

void loop() {
  if (hour() == 7 && minute() == 0 && second() == 0) {
    digitalWrite(solenoidPin, HIGH);
    Serial.println("Solenoid valve opened");
    delay(30000); // Keep the valve open for 30 seconds
    digitalWrite(solenoidPin, LOW);
    Serial.println("Solenoid valve closed");
  } else if (hour() == 18 && minute() == 0 && second() == 0) {
    digitalWrite(solenoidPin, HIGH);
    Serial.println("Solenoid valve opened");
    delay(30000); // Keep the valve open for 30 seconds
    digitalWrite(solenoidPin, LOW);
    Serial.println("Solenoid valve closed");
  }
}
