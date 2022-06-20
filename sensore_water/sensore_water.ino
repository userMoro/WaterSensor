#include "rpcWiFi.h"
#include <MQTT.h>
#include <Arduino_JSON.h>
#include"TFT_eSPI.h"

TFT_eSPI tft;
const char ssid[] = "Its-guest";
const char pass[] = "eet6Euru";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  //while (!client.connect("arduino", "public", "public")) {
  while (!client.connect("AlexG")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/dddd-test-out-gnavi");
  // client.unsubscribe("/hello");
}
void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  JSONVar myObject = JSON.parse(payload);
  //Serial.println(JSON.typeof(myObject));

  if (myObject.hasOwnProperty("name")) {
    Serial.print("myObject[\"name\"] = ");

    Serial.println((const char*) myObject["name"]);
  }

  if (myObject.hasOwnProperty("status")) {
    Serial.print("myObject[\"status\"] = ");

    Serial.println((const char*) myObject["status"]);
    //   Serial.println(myObject["status"]);

  }
}

void setup(){
    Serial.begin(115200);
    WiFi.begin(ssid, pass);

    tft.begin();

    // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
    // by Arduino. You need to set the IP address directly.
    client.begin("broker.hivemq.com", net);
    client.onMessage(messageReceived);

    connect();
  tft.begin();
  pinMode(A0, 2);
  tft.fillScreen(0xF800);
  
}



void loop(){
    client.loop();
    delay(10);  // <- fixes some issues with WiFi stability

    if (!client.connected()) {
      connect();
    }

    // publish a message roughly every second.
    /*if (millis() - lastMillis > 1000) {
      lastMillis = millis();
      
    }*/
  
  if ((analogRead(A0) > 100)) {
    tft.fillScreen(0xF800);
    tft.setTextColor(0x0);
    tft.drawString((String)"attento perdita", 100, 100);
    client.publish("/dddd-test-in-gnavi", "attento perdita");
  }
  if ((analogRead(A0) < 100)) {
    tft.setTextColor(0x0);
    tft.drawString((String)"perdita bassa", 100, 100);
    client.publish("/dddd-test-in-gnavi", " perdita bassa");
  }

}
