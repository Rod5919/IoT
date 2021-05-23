// Define
#define BLYNK_PRINT Serial

// Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Variables
WidgetTerminal terminal(V0);

int x=10, y=100; //amount of data, time

// Connection variables
char auth[] = "Ig6Lmkl4mVIJITFOALlSdUZV3nsufseU";
char ssid[] = "Fernandez";
char pass[] = "sparkie5919";

// Function prototypes
void function(int *x, int *y, float m[][2], float sm[][2], float aux[]);
void sort(float v[]);

// Functions
BLYNK_WRITE(V1){x=param.asInt();}
BLYNK_WRITE(V2){y=param.asInt();}

void sort(float v[]){ //Insertion sort
    int aux, j;
    for (int i = 1; i < sizeof(v)/sizeof(v[0]); i++){ 
        aux = v[i];
        j = i - 1;
        while (j >= 0 && v[j] < aux){
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = aux;
    }
}

void sendData2Blynk(float m[][2], int *x){
    for (int i = 0; i < 2; i++)
    {
        switch (i)
        {
        case 0:
            Serial.print("Celsius:\t");
            terminal.print("Celsius:\t");
            break;
        case 1:
            Serial.print("Farenheit:\t");
            terminal.print("Farenheit:\t");
            break;

        default:
            break;
        }
        for (int j = 0; j < *x; j++)
        {
            Serial.print(m[j][i]);
            terminal.print(m[j][i]);
            Serial.print("\t");
            terminal.print("\t");
        }
        Serial.print("\n");
        terminal.print("\n");
    }
    
}


void function(int *x, int *y, float m[][2], float sm[][2], float aux[]){
    for (int i = 0; i < *x; i++)
    {
        m[i][0] = analogRead(A0)*330/1024;
        m[i][1] = m[i][0]*1.8+32;
        delay(*y);
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < *x; j++)
        {
            aux[j] = m[j][i];
        }
        
        sort(aux);
        
        for (int j = 0; j < *x; j++)
        {
            sm[j][i] = aux[j];
        }
    }
    Serial.print("---------------------------Datos obtenidos---------------------------\n");
    terminal.print("------------Datos obtenidos------------\n");
    sendData2Blynk(m, x);
    Serial.print("---------------------------Datos ordenados---------------------------\n");
    terminal.print("------------Datos ordenados------------\n");
    sendData2Blynk(sm, x);
    Serial.println("\n");
    terminal.println("\n");
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
    float m[x][2], sm[x][2], aux[x]; //matrix, sorted matrix, auxiliar array
    Blynk.run();
    function(&x, &y, m, sm, aux);
}
