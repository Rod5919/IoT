#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "config.h"

char auth[] = "Ig6Lmkl4mVIJITFOALlSdUZV3nsufseU";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Fernandez";
char pass[] = "sparkie5919";
int adcPin = A0;
float temperature;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}
BLYNK_READ(V2)
{
  Blynk.virtualWrite(2,temperature);
}
BLYNK_READ(V3)
{
  Blynk.virtualWrite(3,1.8*temperature+32);
}
int mean(){
  int p = 0;
  for(int i =0; i<10;i++){
   p+=analogRead(adcPin);
//   delay(500); 
  }
  return p/10;
}
void loop() {
  Blynk.run();
  unsigned int adcValue = mean();
  temperature = adcValue* 330/1024;
  Blynk.virtualWrite(2,temperature);
  Serial.print("Value ADC: "); Serial.print(adcValue);
  Serial.print("; (celsius): "); Serial.print(temperature);
  Serial.print("; (farenheit): "); Serial.println(temperature*1.8+32);

}
