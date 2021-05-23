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
int y=1,x=1;
float a=0,mean1,mean2,abs_value,rel,temperature,farenheit;

//!Function prototypes
void function(float *mean1,float* temperature,float *farenheit);

//!Functions
WidgetTerminal terminal(V0);
BLYNK_WRITE(V1){x=param.asInt();}
BLYNK_WRITE(V5){y=param.asInt();  }
BLYNK_WRITE(V2){Blynk.virtualWrite(2,mean1);}
BLYNK_WRITE(V3){Blynk.virtualWrite(2,mean2);}
BLYNK_WRITE(V6){Blynk.virtualWrite(6,temperature);}
BLYNK_WRITE(V7){Blynk.virtualWrite(7,farenheit);}

void function(float *mean1,float* temperature,float *farenheit){
  a=0;  float b[1][20];
  for(int i=0;i<x;i++){
    b[0][i]=analogRead(A0)* 330.0/1024.0; *temperature=b[0][i];
    b[1][i]=(b[0][i]*9/5)+32; *farenheit=b[1][i];
    a=a+(b[0][i]); 
    delay(y*1000);
    } 
  (*mean1)=((a)/x)*1.0;
  terminal.println("Temperature en C ");
  Serial.println("Temperature in C : ");
  for(int i=0;i<x;i++){
    abs_value=(*mean1)-b[0][i];
    rel=abs(abs_value/b[0][i] *100);
    terminal.print("C: ");terminal.print(b[0][i]);
    terminal.print(", Abs: ");terminal.print(abs_value);
    terminal.print(", Rel: %");terminal.println(rel);
    Serial.print("C: ");Serial.print(b[0][i]);
    Serial.print(", Abs: ");Serial.print(abs_value);
    Serial.print(", Rel: %");Serial.println(rel);
    }
  terminal.println("Data obtained!!!\n");
  terminal.flush();
}

//!Setup
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

//!Loop
void loop()
{
  Blynk.run();
  Serial.print("Amount of data: ");Serial.println(x);
  Serial.print("Seconds : ");Serial.println(y);
  function(&mean1,&temperature,&farenheit);
  Blynk.virtualWrite(2,mean1);
  Blynk.virtualWrite(6,temperature);
  Blynk.virtualWrite(7,farenheit);
  Serial.print("Mean value: ");Serial.println(mean1);
  Serial.println("Data obtained!!!");
}

