#include "triraya.h"
#include <Arduino.h>
#include "ESPAsyncWebServer.h"
#include "AsyncTCP.h"

#ifdef ESP32
    #include <WiFi.h>
#elif defined(ESP8266)
    #include <ESP8266WiFi.h>
#else
    #error Platform not supported
#endif

AsyncWebServer server(80);
String inputMessage1 = "";
String inputMessage2 = "";
int pin;

typedef void (*CallBackFunction)();

Triraya::Triraya(int freq, int resolution)
{
    _pin1 = 2;
    _pin2 = 4;
    _pin3 = 5;
    _pin4 = 13;
    _pin5 = 14;
    _pin6 = 15;
    _pin7 = 16;
    _pin8 = 17;
    _pin9 = 25;
    _pin10 = 26;
    _pin11 = 27;
    _pin12 = 12;
    _freq = freq;
    _resolution = resolution;
}

void Triraya::initAP(char* ssid, char* password)
{
  Serial.println();
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);
  IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.begin();
}

void Triraya::initSTA(char* ssid, char* password)
{
   WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/plain", "Connected");
    });
}

void Triraya::default_pin()
{
    ledcSetup(0, _freq, _resolution);
    ledcSetup(1, _freq, _resolution);
    ledcSetup(2, _freq, _resolution);
    ledcSetup(3, _freq, _resolution);
    ledcAttachPin(_pin1, 0);
    ledcAttachPin(_pin2, 1);
    ledcAttachPin(_pin3, 2);
    ledcAttachPin(_pin4, 3);
    pinMode(_pin5, OUTPUT);
    pinMode(_pin6, OUTPUT);
    pinMode(_pin7, OUTPUT);
    pinMode(_pin8, OUTPUT);
    digitalWrite(_pin5, LOW);
    digitalWrite(_pin6, LOW);
    digitalWrite(_pin7, LOW);
    digitalWrite(_pin8, LOW);
    _status = 0;
}

void Triraya::custom_pin()
{
	_status = 1;
}

void Triraya::monitor_data()
{
    server.on("/triraya1", HTTP_GET, [](AsyncWebServerRequest *request){
    int my_analog = analogRead(25);
    Serial.println(String(my_analog).c_str());
    request->send_P(200, "text/plain", String(my_analog).c_str());
  });
    server.on("/triraya2", HTTP_GET, [](AsyncWebServerRequest *request){
    int my_analog = analogRead(26);
    Serial.println(String(my_analog).c_str());
    request->send_P(200, "text/plain", String(my_analog).c_str());
  });
    server.on("/triraya3", HTTP_GET, [](AsyncWebServerRequest *request){
    int my_analog = analogRead(27);
    Serial.println(String(my_analog).c_str());
    request->send_P(200, "text/plain", String(my_analog).c_str());
  });
    server.on("/triraya4", HTTP_GET, [](AsyncWebServerRequest *request){
    int my_analog = analogRead(12);
    Serial.println(String(my_analog).c_str());
    request->send_P(200, "text/plain", String(my_analog).c_str());
  });
}

void Triraya::pwm_controller(uint8_t pwm_pin)
{
  if(_status == 1){
    server.on("/pwm", HTTP_GET, [pwm_pin] (AsyncWebServerRequest *request) {
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam("pin") && request->hasParam("value")) {
      inputMessage1 = request->getParam("pin")->value();
      inputMessage2 = request->getParam("value")->value();
      }
    Serial.println("Param accepted pin: " + inputMessage1 + " Value: " + inputMessage2);
    pin = inputMessage1.toInt();
    if (pin == pwm_pin){
      ledcWrite(pwm_pin, inputMessage2.toInt());
      //analogWrite(pwm_pin, inputMessage2.toInt());
      Serial.println(inputMessage1 + " now has pwm param " + inputMessage2);
      }
    request->send(200, "text/plain", "OK");
    });
  }
} 

void Triraya::push_button(int output_pin)
{
  if(_status == 1){
    server.on("/pb", HTTP_GET, [output_pin] (AsyncWebServerRequest *request) {
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam("pin") && request->hasParam("value")) {
      inputMessage1 = request->getParam("pin")->value();
      inputMessage2 = request->getParam("value")->value();
      }
    Serial.println("Param accepted pin: " + inputMessage1 + " Value: " + inputMessage2);
    pin = inputMessage1.toInt();
    if (pin == output_pin){
      digitalWrite(output_pin, inputMessage2.toInt());
      Serial.println(inputMessage1 + " now in condition " + inputMessage2);
      }
    request->send(200, "text/plain", "OK");
    });
  }
}

void Triraya::enable_pwm_pin()
{
  if(_status == 0){
    server.on("/en_pwm", HTTP_GET, [] (AsyncWebServerRequest *request) {
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam("pin") && request->hasParam("value")) {
      inputMessage1 = request->getParam("pin")->value();
      inputMessage2 = request->getParam("value")->value();
    }
    Serial.println("Param accepted pin: " + inputMessage1 + " Value: " + inputMessage2);
    ledcWrite(inputMessage1.toInt(), inputMessage2.toInt());
    //analogWrite(inputMessage1.toInt(), inputMessage2.toInt());
    request->send(200, "text/plain", "OK");
    });
    
  }
}

void Triraya::enable_button_pin()
{
  if(_status == 0){
    server.on("/en_pb", HTTP_GET, [] (AsyncWebServerRequest *request) {
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam("pin") && request->hasParam("value")) {
      inputMessage1 = request->getParam("pin")->value();
      inputMessage2 = request->getParam("value")->value();
    }
    Serial.println("Param accepted pin: " + inputMessage1 + " Value: " + inputMessage2);
    digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    request->send(200, "text/plain", "OK");
    });
  }
}
