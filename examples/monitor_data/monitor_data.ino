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
  myraya.monitor_data(send_data); //add analog pin (sensor) at pin 25, 26, or 27
}

void loop() { 
  
}
