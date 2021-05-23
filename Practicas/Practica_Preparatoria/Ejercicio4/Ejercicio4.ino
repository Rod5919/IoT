// Define
#define BLYNK_PRINT Serial

// Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Variables
WidgetTerminal terminal(V0);
float maxim=0, minim=1024;
int x=10, y=100; //amount of data, time

// Connection variables
char auth[] = "Ig6Lmkl4mVIJITFOALlSdUZV3nsufseU";
char ssid[] = "Fernandez";
char pass[] = "sparkie5919";

// Function prototypes
void function(int *x, int *y, float v[], float *maxim, float *minim);

// Functions
BLYNK_WRITE(V1){x=param.asInt();}
BLYNK_WRITE(V2){y=param.asInt();}
BLYNK_WRITE(V3){Blynk.virtualWrite(3,minim);}
BLYNK_WRITE(V4){Blynk.virtualWrite(4,maxim);}
void function(int *x, int *y, float v[], float *maxim, float *minim){
    String text;
    *maxim=0;
    *minim=1024;
    for (int i = 0; i < *x; i++)
    {
        v[i] = analogRead(A0)*330/1024;
        delay(*y);
        Serial.print(v[i]);
        terminal.print(v[i]);
        Serial.print("\t");
        terminal.print("\t");
        if(v[i] > *maxim)
            *maxim = v[i];
        
        if (v[i] < *minim)
            *minim = v[i];
        text+=String(v[i]);
        text+=" ";
    }
    Blynk.email("sergiorodrigofernandeztesta@mail.com", "Ejercicio 4 ",text);

    Serial.print("Max:\t");
    terminal.print("Max:\t");
    Serial.print(*maxim);
    terminal.print(*maxim);
    Blynk.virtualWrite(4,*maxim);
    
    Serial.print("\t\t");
    terminal.print("\t\t");

    Serial.print("Min:\t");
    terminal.print("Min:\t");
    Serial.print(*minim);
    terminal.print(*minim);
    Blynk.virtualWrite(3,*minim);

    Serial.print("\n\n");
    terminal.print("\n\n");
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
    function(&x, &y, v, &maxim, &minim);
}
