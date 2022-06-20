#include"TFT_eSPI.h"

TFT_eSPI tft;
float f;

void setup(){
  tft.begin();
  pinMode(A0, 2);
  tft.fillScreen(0x49F);
  tft.setRotation(3);
  tft.setTextColor(0xFFFF);

}



void loop(){

  f = analogRead(A0);
  if ((f > 201)) {
    tft.drawString((String)"Nessuna perdita rilevata...", 18, 120);
    tft.setTextSize(2);
    tft.fillScreen(0x49F);
    Serial.println(f);
  }
  if ((((f < 200)) && ((f > 101)))) {
    tft.setTextSize(3);
    tft.drawString((String)"Perdita rilevata!", 18, 120);
    tft.fillScreen(0xFFE0);
    Serial.println(f);
  }
  if ((((f < 100)) && ((f > 51)))) {
    tft.setTextSize(3);
    tft.drawString((String)"Grossa perdita!", 18, 120);
    tft.fillScreen(0xFCA0);
    Serial.println(f);
  }
  if ((f < 50)) {
    tft.setTextSize(4);
    tft.drawString((String)"Allagamento!", 18, 120);
    tft.fillScreen(0xF800);
    Serial.println(f);
  }

}
