// Define
#define BLYNK_PRINT Serial

// Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Variables
int x=83, y=165, z=247; //red, yellow, green
float val;
WidgetLED led1(V1);
WidgetLED led2(V2);
WidgetLED led3(V3);

// Connection variables
char auth[] = "Ig6Lmkl4mVIJITFOALlSdUZV3nsufseU";
char ssid[] = "Fernandez";
char pass[] = "sparkie5919";

// Function prototypes
void function(int *x, int *y, int *z);

// Functions
BLYNK_WRITE(V0){Blynk.virtualWrite(1,val);}
BLYNK_WRITE(V4){x=param.asInt();}
BLYNK_WRITE(V5){y=param.asInt();}
BLYNK_WRITE(V6){z=param.asInt();}
void function(int *x, int *y, int *z){
    val = analogRead(A0)*330/1024;
    Blynk.virtualWrite(0,val);
    if (val > *z){
        Blynk.email("sergiorodrigofernandeztesta@mail.com", "Ejercicio 3 ","Alert: To Hot!");
        Serial.println("Alert: To Hot!");
    }else if (val > *y){
        Serial.println("Red");
        led1.on();
        led2.off();
        led3.off();
    }else if (val > *x){
        Serial.println("Yellow");
        led1.off();
        led2.on();
        led3.off();
    }else{
        Serial.println("Green");
        led1.off();
        led2.off();
        led3.on();
    }
}

// Setup
void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

// Loop
void loop()
{
    float v[x];
    Blynk.run();
    function(&x, &y, &z);
}
