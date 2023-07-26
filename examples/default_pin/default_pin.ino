#include <WiFi.h>
#include <WiFiAP.h>
#include <triraya.h>

char *ssid = "yourAP";
char *password = "yourPassword";

//initial for pwm's frequency and resolution
Triraya myraya(1000, 8); //1kHz freq and 8 bit resolution

void setup() {
  Serial.begin(115200);
  myraya.initAP(ssid, password); //activate the AP SSID and Password
  myraya.default_pin(); //Using default pin that has been set in triraya
  myraya.enable_pwm_pin(); //enable the PWM pin
  myraya.enable_button_pin(); //enable the button Pin
}

void loop() {
  
}
