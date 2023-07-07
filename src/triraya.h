#ifndef triraya_h
#define triraya_h
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

typedef void (*CallBackFunction)();

class Triraya
{
    public:
        typedef enum
        {

        } my_mode;

        Triraya(int freq, int resolution);
        void init(char* ssid, char* password);
        void default_pin();
      	void custom_pin();
	void monitor_data(char *mydata);
	void pwm_controller(uint8_t pwm_pin);
	void push_button(uint8_t output_pin);
	void enable_pwm_pin();
	void enable_button_pin();

    private:
        byte _pin1;
        byte _pin2;
        byte _pin3;
        byte _pin4;
        byte _pin5;
        byte _pin6;
        byte _pin7;
        byte _pin8;
        byte _pin9;
        byte _pin10;
        byte _pin11;
        byte _pin12;
        IPAddress IP;
        int _status;
        int _freq;
        int _resolution;
        static void fakeCallback();
};

#endif
