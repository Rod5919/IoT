// Define
#define BLYNK_PRINT Serial

// Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <string>
// Variables
int x=10, y=100; //amount of data, time
WidgetTerminal terminal(V0);

// Connection variables
char auth[] = "Ig6Lmkl4mVIJITFOALlSdUZV3nsufseU";
char ssid[] = "Fernandez";
char pass[] = "sparkie5919";

// Function prototypes
void function(int *x, int *y, float v[]);

// Functions
BLYNK_WRITE(V1){x=param.asInt();}
BLYNK_WRITE(V2){y=param.asInt();}

void function(int *x, int *y, float v[]){
    String text;
    for (int i = 0; i < *x; i++)
    {
        v[i] = analogRead(A0)*330/1024;
        delay(*y);
        Serial.print(v[i]);
        Serial.print("\t");
        terminal.print(v[i]);
        terminal.print("\t");
        text+=String(v[i]);
        text+=" ";
    }
    
    // Blynk.email("sergiorodrigofernandeztesta@mail.com", "Ejercicio 1 ",text);
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
    function(&x, &y, v);
}
