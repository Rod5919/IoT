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
int x=22,y=25,z=28;
float temperature;
String mail;

//!Function prototypes
void ej3(float *temperature,int *x,int *y,int *z);
WidgetLED led1(V0);
WidgetLED led2(V1);
WidgetLED led3(V2);

//!Functions
BLYNK_WRITE(V3){Blynk.virtualWrite(3,temperature);}
BLYNK_WRITE(V4){x=param.asInt();}
BLYNK_WRITE(V5){y=param.asInt();}
BLYNK_WRITE(V6){z=param.asInt();}

void ej3(float* temperature,int *x,int *y,int *z){
  Blynk.run();
  *temperature=analogRead(A0)* 330.0/1024.0;
  String aux=String(*temperature);
  Serial.print("x : ");Serial.println(String(*x));
  Serial.print("y : ");Serial.println(String(*y));
  Serial.print("z : ");Serial.println(String(*z));
  if (*temperature<*x){
    led1.on(); led2.off(); led3.off();
    mail="Temperature: "+aux+" . Led green on, everything OK.";
    Blynk.email("sergiorodrigofernandeztesta@gmail.com", "Led G status...", mail);
    digitalWrite(16,LOW); digitalWrite(5,HIGH); digitalWrite(4,LOW);
    }
  else if(*temperature>*x && *temperature<*y){
    led1.off(); led2.on(); led3.off();
    mail="Temperature: "+aux+" . Led blue on, variable X exceeded, variable Y stable.";
    Blynk.email("sergiorodrigofernandeztesta@gmail.com", "Led B status...", mail);
    digitalWrite(16,LOW); digitalWrite(5,LOW); digitalWrite(4,HIGH);
    }
  else if(*temperature>*y && *temperature<*z){
    led1.off(); led2.off(); led3.on();
    mail="Temperature: "+aux+" . Led red on, variable Y exceeded, variable Z stable.";
    Blynk.email("sergiorodrigofernandeztesta@gmail.com", "Led R status...", mail);
    digitalWrite(16,HIGH); digitalWrite(5,LOW); digitalWrite(4,LOW);
    }
   else{
    led1.off(); led2.off(); led3.off();
    mail="Temperature: "+aux+" . ALERT, boiling.";
    Blynk.email("sergiorodrigofernandeztesta@gmail.com", "ALERT", mail);
    digitalWrite(16,LOW); digitalWrite(5,LOW); digitalWrite(4,LOW);
    }
    delay(500);
}


//!Setup
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

}

//!Loop
void loop()
{
  Blynk.run();
  Serial.print("Temperatura : ");Serial.println(temperature);
  ej3(&temperature,&x,&y,&z);
  Blynk.virtualWrite(3,temperature);
}

