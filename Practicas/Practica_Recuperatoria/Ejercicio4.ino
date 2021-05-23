//!libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "config.h"
#include <SPI.h>
//!Define
#define BLYNK_PRINT Serial

//!Variables
char auth[] = "Ig6Lmkl4mVIJITFOALlSdUZV3nsufseU";
char ssid[] = "Fernandez";
char pass[] = "sparkie5919";
const int btnPin = 2;
float temperature,x,y,z,out;
String mail,text;
boolean btnState = false;
int i=1,q=1;

//!Function prototypes
void ej4(float *temperature,float *out,String *text,int*q);

//!Functions
BLYNK_WRITE(V0){Blynk.virtualWrite(0,out);}
WidgetLCD lcd(V1);
BLYNK_WRITE(V2){q=param.asInt();}
WidgetLED led3(V3);

void ej4(float* temperature,float *out,String *text,int*q){
  Blynk.run();
  boolean isPressed = (digitalRead(btnPin) == LOW);
  if (isPressed != btnState) {
    if (isPressed) {
      led3.on();
      *temperature=analogRead(A0);
      x=*temperature* 330.0/1024.0;
      y=(x*9/5)+32;
      z=x+273.15;
      String aux=String(x);String aux2=String(y);String aux3=String(z);
      mail="Temperature: "+aux+" C, "+aux2+" F, "+aux3+" K.";
      Blynk.email("sergiorodrigofernandeztesta@gmail.com", "Temperature", mail);
    }
    else{led3.off();}
    btnState = isPressed;
  }
  if(*q==1){
    switch(i){
        case 1:
        *out=x; *text="Celsius: "; 
        Blynk.email("sergiorodrigofernandeztesta@gmail.com", "Changed", "Celsius");
        break;
        case 2:
        *out=y; *text="Farenheit: ";
        Blynk.email("sergiorodrigofernandeztesta@gmail.com", "Changed", "Farenheit");
        break;
        case 3:
        *out=z; *text="Kelvin: ";
        Blynk.email("sergiorodrigofernandeztesta@gmail.com", "Changed", "Kelvin");
        break;
        default:
        i=1;*out=x; *text="Celsius: "; 
        Blynk.email("sergiorodrigofernandeztesta@gmail.com", "Changed", "Celsius");
        break;
        }i++;
    }
  delay(1000);
}


void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  String aux;
  Blynk.run();
  ej4(&temperature,&out,&text,&q);
  aux=text+String(out);
  Blynk.virtualWrite(0,out);
  lcd.clear();
  lcd.print(0,0,aux); 
}


