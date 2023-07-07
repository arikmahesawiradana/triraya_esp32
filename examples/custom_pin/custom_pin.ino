#include <WiFi.h>
#include <WiFiAP.h>
#include <triraya.h>
#define LED 2

char *ssid = "yourAP";
char *password = "yourPassword";

//initial for pwm's frequency and resolution
Triraya myraya(1000, 8); //1kHz freq and 8 bit resolution

void setup() {
  Serial.begin(115200);
  myraya.init(ssid, password); //activate the AP SSID and Password
  myraya.custom_pin(); //Using custom pin that has been set
  pinMode(LED, OUTPUT); //make LED as output
}

void loop() { 
  myraya.push_button(LED); //connect pin with triraya
}
