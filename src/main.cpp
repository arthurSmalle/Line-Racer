#include <Arduino.h>

void setup(){
  Serial.begin(115200);
}

void loop(){
  Serial.println("wheel to ir " + String(WHEELS_TO_IR));
}
