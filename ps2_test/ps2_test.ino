#include "PS2X_lib.h" //for v1.6
#include "Controller.h"

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

void setup()
{
  Serial.begin(2000000);
  mycontroller.init(PS2_BUTTON_PIN, PS2_GND_1, PS2_VCC_1, PS2_CLK_1, PS2_CMD_1, PS2_SEL_1, PS2_DAT_1,
            PS2_GND_2, PS2_VCC_2, PS2_CLK_2, PS2_CMD_2, PS2_SEL_2, PS2_DAT_2);
}

void loop()
{
  mycontroller.print();
  delay(10);
}
