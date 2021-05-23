// Define
#define BLYNK_PRINT Serial

// Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Variables
int x=10, y=100; //amount of data, time
float s = 0;
WidgetTerminal terminal(V0);

// Connection variables
char auth[] = "Ig6Lmkl4mVIJITFOALlSdUZV3nsufseU";
char ssid[] = "Fernandez";
char pass[] = "sparkie5919";

// Function prototypes
void function(float *s, int *x, int *y, float v[], float e[]);

// Functions
BLYNK_WRITE(V1){x=param.asInt();}
BLYNK_WRITE(V2){y=param.asInt();}
BLYNK_WRITE(V3){Blynk.virtualWrite(3,s);}

void function(float *s, int *x, int *y, float v[], float e[]){
    String text;
    Serial.print("Datos:\t\t\t");
    terminal.print("Datos:\t\t\t");
    *s = 0;
    for (int i = 0; i < *x; i++)
    {
        v[i] = analogRead(A0)*330/1024;
        delay(*y);
        Serial.print(v[i]);
        terminal.print(v[i]);
        Serial.print("\t");
        terminal.print("\t");
        *s+= (float)v[i];
        text+=String(v[i]);
        text+=" ";
    }
    // Blynk.email("sergiorodrigofernandeztesta@mail.com", "Ejercicio 2 ",text);
    *s/=*x;
    Blynk.virtualWrite(3,*s);
    Serial.print("\n");
    terminal.print("\n");
    Serial.print("Media:\t\t\t");
    terminal.print("Media:\t\t\t");
    Serial.print(*s);
    terminal.print(*s);
    Serial.print("\n");
    terminal.print("\n");

    Serial.print("Errores relativos:\t");
    terminal.print("Errores relativos:\t");
    for (int i = 0; i < *x; i++)
    {
        e[i]= fabs((*s-v[i])) / *s;
        Serial.print(e[i]);
        terminal.print(e[i]);
        Serial.print("\t");
        terminal.print("\t");
    }
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
    float v[x], e[x];
    Blynk.run();
    function(&s, &x, &y, v, e);
}
