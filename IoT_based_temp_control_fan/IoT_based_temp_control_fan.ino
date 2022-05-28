/*
 * Demo program to add your Nuttyfi, NodeMCU ESP8266 or ESP32 wifi board to 
 * Blynk2.0 IoT mobile app & web dashboard
 *	for any query visit to www.smedehradun.com
 *	To design your customized hardware, visit to www.nuttyengineer.com 
 *  Youtube Channel: https://www.youtube.com/c/SMEDehradun
 * pin description: 
 * DHT11 / dht22- D5
 *Relay for Fan - D2
 *
 *Virtual pin description
 * Virtual led for Fan- V0
 * temperature- V1
 * humidity- V2
 * Slider to set the Temperature value- V3
 * follow me on github for new update
 */ 
// Fill-in information from your Blynk Template here

#include "DHT.h"
DHT dht(D5, DHT11);

#define BLYNK_TEMPLATE_ID "TMPL4O3Es9K8"
#define BLYNK_DEVICE_NAME "IoT Automation Fan"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial 
#define USE_NODE_MCU_BOARD
//#define APP_DEBUG
#define FAN_PIN D2
float h, t;

#include "BlynkEdgent.h" 

int Val=0;
WidgetLED FAN(V0);

BLYNK_WRITE(V3)
{
  Val = param.asInt(); // assigning incoming value from pin V3 to a variable

  Serial.print(" The Threshhold value is: ");
  Serial.println(Val);
  Serial.println();
}

void setup()
{
  Serial.begin(9600);
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
  BlynkEdgent.begin();
  delay(2000);
  dht.begin();
}

void loop() {
    BlynkEdgent.run();
    dht_data();
}

void dht_data()
{
  h = dht.readHumidity();
  t = dht.readTemperature();
  if (Val > t)
  {
    Serial.println("Fan Off");
    digitalWrite(FAN_PIN, LOW);
    FAN.off();
}
  else {
    digitalWrite(FAN_PIN, HIGH);
    FAN.on();
    Serial.println("Fan ON"); 
  } 
  
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
  
}
