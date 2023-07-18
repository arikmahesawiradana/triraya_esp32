#include <WiFi.h>
#include <WiFiAP.h>
#include <triraya.h>

char *ssid = "yourAP";
char *password = "yourPassword";

//initial for pwm's frequency and resolution
Triraya myraya(1000, 8); //1kHz freq and 8 bit resolution

void setup() {
  Serial.begin(115200);
  myraya.init(ssid, password); //activate the AP SSID and Password
  myraya.monitor_data(); //add analog pin (sensor) at pin 25, 26, or 27
}

void loop() { 
  
}
