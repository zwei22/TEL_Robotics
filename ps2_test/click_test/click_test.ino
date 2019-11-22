
//use serial plotter to see the changes in time

#include "ClickButton.h"

const int buttonPin1 = A0;
ClickButton button1(buttonPin1, LOW, CLICKBTN_PULLUP);


void setup() {
  Serial.begin(57600);
  button1.longClickTime = 10;
}

void loop() {
  button1.Update();
  if(button1.changed ){
    Serial.println("changed");
  }
}
