#include <SoftwareSerial.h>
#include "cmdParser.h"
#include "Controller.h"
#include "PS2X_lib.h"

#define PS2_GND_1 8
#define PS2_VCC_1 9
#define PS2_DAT_1 10
#define PS2_CMD_1 11
#define PS2_SEL_1 12
#define PS2_CLK_1 13

#define PS2_GND_2 2
#define PS2_VCC_2 3
#define PS2_DAT_2 4
#define PS2_CMD_2 5
#define PS2_SEL_2 6
#define PS2_CLK_2 7
#define PS2_BUTTON_PIN A0

Controller mycontroller;
SoftwareSerial BT(2, 3);
uint8_t body_pins[8] = {3, 4, 6, 7, 9, 10, 12, 13};
Body body(body_pins);
uint8_t armIds[3] = {0, 1, 2};
Arm arm(Serial2, armIds);
uint8_t shovelIds[3] = {3, 4, 5};
Shovel shovel(Serial2, shovelIds);
uint8_t bucketIds[2] = {6, 7};
Bucket bucket(Serial2, bucketIds);

void setup()
{
  BT.begin(115200);
  Serial2.begin(115200);
  Serial.begin(115200);

  //arm.ready();
  //delay(2000);
  //arm.fold();
  // mycontroller.init(PS2_BUTTON_PIN, PS2_GND_1, PS2_VCC_1, PS2_CLK_1, PS2_CMD_1, PS2_SEL_1, PS2_DAT_1,
  //                   PS2_GND_2, PS2_VCC_2, PS2_CLK_2, PS2_CMD_2, PS2_SEL_2, PS2_DAT_2);
}

void loop()
{

  if (BT.available())
  {
    char c = BT.read();
    Serial.println(c);
    switch (c)
    {
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
