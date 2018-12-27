/*
 * Wetterstaion die alle 15 Minuten einen Mittelwert von 5 gemessenen Werten, Abstand 3 Sekunden, bildet und an ThingSpeak sendet
 * secret.h bechachten!!
 * PIN D0 muss mit RST verbunden werden, sonst kann der ESP nicht resettet werden
 */

#include "DHT.h"
#include "ThingSpeak.h"
#include "secrets.h"
#include <ESP8266WiFi.h>

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

DHT dht(DHTPIN, DHTTYPE);

int hum = 0;  // Humidity
int tem = 0;  // Temperature

void wlan(void) { 
  WiFi.mode(WIFI_STA);
  
  if(WiFi.status() != WL_CONNECTED){
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);
      delay(5000);     
    } 
  }
}

void readsensor(void) { 
  int igestem = 0;
  int igeshum = 0;
  int teiler = 0;
  for(int i = 0; i < 5; i++) {
     delay(3000);
     igestem += dht.readTemperature();
     igeshum += dht.readHumidity();
     teiler++;
  }
  tem = igestem/teiler;
  hum = igeshum/teiler;
}

void control(void) {
  if (tem < -10 or tem > 50 or hum < 0 or hum > 100) {
    ESP.reset();
  }
}

void sendsensor(void) { 
  ThingSpeak.begin(client);
  
  ThingSpeak.setField(1, tem);
  ThingSpeak.setField(2, hum);

  int test = 0;

  while (test != 200) {
  test = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (test == 200) {
  }
  else {
    delay(5000);  //after a fail the program will wait 5 seconds and try it again
  }
  }
}

void setup() { 
  wlan();
  readsensor();
  control();
  sendsensor();
  ESP.deepSleep(9e8); //reset after 15 minutes
}

void loop() {
}
