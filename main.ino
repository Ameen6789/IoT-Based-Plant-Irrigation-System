// Include Library
#include <ESP8266WiFi.h>


// Constants
#define SSID	""
#define PWD	""


void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(SSID, PWD);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

}
