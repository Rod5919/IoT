//!Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "config.h"

//!Define
#define BLYNK_PRINT Serial

//!Variables
char auth[] = "Ig6Lmkl4mVIJITFOALlSdUZV3nsufseU";
char ssid[] = "Fernandez";
char pass[] = "sparkie5919";
int adcPin = A0;
float temperature;
bool flag = 0, pflag = 0;
byte selector = 0;

//!Function prototypes
int temp(bool previous, bool actual, byte temperature);

//!Functions
int temp(bool previous, bool actual, byte temperature){
  if (actual>previous)
  {
    return (temperature+1)%3;
  }else{
    return temperature;
  }
}

BLYNK_READ(V2){
  Blynk.virtualWrite(2,temperature);
}

//!Setup
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

//!Loop
void loop() {
  Blynk.run();
  // Valor ADC
  unsigned int adcValue = analogRead(A0);
  temperature = adcValue* 330/1024;
  flag = digitalRead(D1);
  selector = temp(pflag,flag,selector);

  //SEnd different temperatures
  switch (selector)
  {
  case 0:
    Serial.print('Celsius: ');
    Serial.println(temperature);
    Blynk.virtualWrite(2,temperature);
    Blynk.email("sergiorodrigofernandeztesta@gmail.com", "Temperature in celsius", temperature);
    break;
  case 1:
    Serial.print('Farenheit: ');
    Serial.println(temperature*1.8+32);
    Blynk.virtualWrite(2,temperature*1.8+32);
    Blynk.email("sergiorodrigofernandeztesta@gmail.com", "Temperature in farenheit", temperature*1.8+32);
    break;
  case 2:
    Serial.print('Kelvin: ');
    Serial.println(temperature+273.15);
    Blynk.virtualWrite(2,temperature+273.15);
    Blynk.email("sergiorodrigofernandeztesta@gmail.com", "Temperature in farenheit", temperature+273.15);
    break;
  
  }
  pflag = flag;
}
