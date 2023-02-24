// Include Library
#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <BlynkSimpleEsp8266.h>

// Constants
#define SSID                ""      // WiFi ssid
#define PWD                 ""      // WiFi password
#define auth                ""      // Blynk authtoken
#define solenoidPin         D1
#define moisturePin         A0
#define moistureThreshold   30;

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  
  pinMode(solenoidPin, OUTPUT);
  digitalWrite(solenoidPin, LOW);
  
  pinMode(moisturePin, INPUT);
  Serial.println();

  WiFi.begin(SSID, PWD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Blynk.begin(auth, SSID, PWD, "blynk.cloud", 80);


  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          currentLine = "";
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.println("<html>");
          client.println("<head><title>ESP8266 Solenoid Valve Control</title></head>");
          client.println("<body>");
          client.println("<h1>ESP8266 Solenoid Valve Control</h1>");
          client.println("<p>Solenoid valve is currently " + String(digitalRead(solenoidPin) == HIGH ? "open" : "closed") + "</p>");
          client.println("</body>");
          client.println("</html>");
          break;
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }

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
  } else if (hour() > 7 && hour() < 18) { // Between 7 AM and 6 PM
    int moistureLevel = analogRead(moisturePin);
    if (moistureLevel < moistureThreshold) {
      digitalWrite(solenoidPin, HIGH);
      Serial.println("Solenoid valve opened");
      delay(30000); // Keep the valve open for 30 seconds
      digitalWrite(solenoidPin, LOW);
      Serial.println("Solenoid valve closed");
    }
  }
}
