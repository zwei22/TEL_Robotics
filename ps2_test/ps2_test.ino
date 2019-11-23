#include "PS2X_lib.h" //for v1.6
#include "Controller.h"

#define PS2_GND_1 22
#define PS2_VCC_1 24
#define PS2_DAT_1 26
#define PS2_CMD_1 28
#define PS2_SEL_1 30
#define PS2_CLK_1 32

#define PS2_GND_2 23
#define PS2_VCC_2 25
#define PS2_DAT_2 27
#define PS2_CMD_2 29
#define PS2_SEL_2 31
#define PS2_CLK_2 33
#define PS2_BUTTON_PIN 53

Controller mycontroller;

void setup()
{
  Serial.begin(2000000);
  Serial2.begin(115200);
  mycontroller.init(PS2_BUTTON_PIN, PS2_GND_1, PS2_VCC_1, PS2_CLK_1, PS2_CMD_1, PS2_SEL_1, PS2_DAT_1,
            PS2_GND_2, PS2_VCC_2, PS2_CLK_2, PS2_CMD_2, PS2_SEL_2, PS2_DAT_2);
}

void loop()
{
  mycontroller.readControllerCommand();
  delay(20);
}
