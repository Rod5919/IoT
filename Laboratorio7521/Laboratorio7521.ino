#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "Fernandez"
#define STAPSK  "sparkie5919"
#endif


// OTA variables
const char* ssid = STASSID;
const char* password = STAPSK;

char auth[] = "Ig6Lmkl4mVIJITFOALlSdUZV3nsufseU";

// Your WiFi credentials.
// Set password to "" for open networks.
char bssid[] = "Fernandez";
char pass[] = "sparkie5919";

void otaconnect();
void otaconnect(){
    Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


float setpoint, valluz;
int foco=D4;
int adcVal=0;
int Valadc=A0;
int led = 0;

BLYNK_WRITE(V0)
{
  Blynk.virtualWrite(V0,Valadc);
  }
BLYNK_WRITE(V1)
{
  setpoint=param.asFloat();
}
BLYNK_WRITE(V2)
{
  led=param.asInt();
}
void setup()
{
  // Debug console
  Serial.begin(9600);
  otaconnect();
  Blynk.begin(auth, bssid, pass);
  pinMode(foco,OUTPUT);
  digitalWrite(foco,LOW);
}

void loop()
{
  ArduinoOTA.handle();
  adcVal = analogRead(Valadc);
  if(adcVal>setpoint)
  {
    digitalWrite(foco,LOW);
    }
    else{digitalWrite(foco,HIGH);}
  Blynk.run();
  delay(300);
}