#include <WiFi.h>
#include <WiFiAP.h>
#include <triraya.h>
#define adc_pin 15

char *ssid = "yourAP";
char *password = "yourPassword";
char* param1 = "param1";

//initial for pwm's frequency and resolution
Triraya myraya(1000, 8); //1kHz freq and 8 bit resolution

void setup() {
  Serial.begin(115200);
  myraya.init(ssid, password); //activate the AP SSID and Password
}

void loop() { 
  int my_adc = analogRead(adc_pin);
  char* send_data = param1 + my_adc;
  myraya.monitor_data(send_data);
}
