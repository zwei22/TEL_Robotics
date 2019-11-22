#include <SoftwareSerial.h>
#include "cmdParser.h"
#include "PS2X_lib.h"

SoftwareSerial BT(2,3);
uint8_t pins[8] = {4,5,6,7,8,9,10,11};
Body body(pins);
uint8_t armIds[3] = {0,1,2};
Arm arm(Serial2, armIds);
uint8_t shovelIds[3] = {3,4,5};
Shovel shovel(Serial2, shovelIds);
uint8_t bucketIds[2] = {6,7};
Bucket bucket(Serial2, bucketIds);

void setup() {
  BT.begin(115200);
  Serial2.begin(115200);
  Serial.begin(115200);

  shovel.ready();
  delay(3000);
  shovel.idle();
  
}

void loop() {
  
  if (BT.available()){
    char c = BT.read();
    Serial.println(c);
    switch(c){
      case 'F':
        body.forward();
        break;
      case 'R':
        body.moveRight();
        break;
      case 'L':
        body.moveLeft();
        break;
      case 'B':
        body.backward();
        break;
      case 'S':
        body.stop();
        break;
    }
  }
}
