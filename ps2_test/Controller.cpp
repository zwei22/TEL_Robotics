#include "PS2X_lib.h" //for v1.6
#include "Controller.h"
#include "ClickButton.h"

#define JOY_CENTER_LX_1 128
#define JOY_CENTER_LY_1 127
#define JOY_CENTER_RX_1 128
#define JOY_CENTER_RY_1 127
#define JOY_CENTER_LX_2 128
#define JOY_CENTER_LY_2 127
#define JOY_CENTER_RX_2 128
#define JOY_CENTER_RY_2 127
#define JOY_CENTER_THR 10

#define DEBUG
void Controller::readControllerCommand()
{
    this->ps2x_1.read_gamepad(false, this->vibrate);
    this->ps2x_2.read_gamepad(false, this->vibrate);
    
    int LX_1 = int(this->ps2x_1.Analog(PSS_LX));
    int LY_1 = int(this->ps2x_1.Analog(PSS_LY));
    int RX_1 = int(this->ps2x_1.Analog(PSS_RX));
    int RY_1 = int(this->ps2x_1.Analog(PSS_RY));

    int LX_2 = int(this->ps2x_2.Analog(PSS_LX));
    int LY_2 = int(this->ps2x_2.Analog(PSS_LY));
    int RX_2 = int(this->ps2x_2.Analog(PSS_RX));
    int RY_2 = int(this->ps2x_2.Analog(PSS_RY));

    if (this->controller_state == 0)
    {
        if (this->ps2x_1.NewButtonState() && this->ps2x_1.Button(PSB_L1))
        {
            this->controller_state = 1;
        }
        if (abs(LX_1 - JOY_CENTER_LX_1) >= abs(LY_1 - JOY_CENTER_LY_1) && abs(LX_1 - JOY_CENTER_LX_1) >= JOY_CENTER_THR)
        {
            int motor_value[4] = {0};
            int turn_value = map(LX_1, 0, 255, -100, 100);
            motor_value[0] = turn_value;
            motor_value[1] = turn_value;
            motor_value[2] = -1 * turn_value;
            motor_value[3] = -1 * turn_value;

            this->move_all(motor_value);
        }
        else if (abs(LX_1 - JOY_CENTER_LX_1) < abs(LY_1 - JOY_CENTER_LY_1) && abs(LY_1 - JOY_CENTER_LY_1) >= JOY_CENTER_THR)
        {
            int motor_value[4] = {0};
            int turn_value = map(LY_1, 0, 255, -100, 100);
            motor_value[0] = turn_value;
            motor_value[1] = turn_value;
            motor_value[2] = turn_value;
            motor_value[3] = turn_value;

            if (abs(RX_1 - JOY_CENTER_RX_1) >= JOY_CENTER_THR)
            {
                int offset_value = map(RX_1, 0, 255, -20, 20);
                if (offset_value >= 0)
                {
                    // motor_value[0] -= offset_value;
                    // motor_value[3] -= offset_value;
                    motor_value[0] = int(float(motor_value[0]) * (130.0 - float(abs(offset_value))) / 100.0);
                    motor_value[3] = int(float(motor_value[0]) * (130.0 - float(abs(offset_value))) / 100.0);
                }
                else
                {
                    // motor_value[1] -= offset_value;
                    // motor_value[2] -= offset_value;
                    motor_value[1] = int(float(motor_value[0]) * (130.0 - float(abs(offset_value))) / 100.0);
                    motor_value[2] = int(float(motor_value[0]) * (130.0 - float(abs(offset_value))) / 100.0);
                }
            }
            this->move_all(motor_value);
        }
        else if (abs(RX_1 - JOY_CENTER_RX_1) >= JOY_CENTER_THR)
        {
            int motor_value[4] = {0};
            int turn_value = map(RX_1, 0, 255, -100, 100);
            motor_value[0] = turn_value;
            motor_value[1] = -1 * turn_value;
            motor_value[2] = -1 * turn_value;
            motor_value[3] = turn_value;

            this->move_all(motor_value);
        }
        else
        {
            int motor_value[4] = {0};
            this->move_all(motor_value);
        }
    }
    else
    {
        if (this->ps2x_1.NewButtonState() && this->ps2x_1.Button(PSB_L1))
        {
            this->controller_state = 0;
        }
        if (abs(LX_1 - JOY_CENTER_LX_1) >= abs(LY_1 - JOY_CENTER_LY_1) && abs(LX_1 - JOY_CENTER_LX_1) >= JOY_CENTER_THR)
        {
            int motor_value[4] = {0};
            int turn_value = map(LX_1, 0, 255, -100, 100);
            motor_value[0] = -1 * turn_value;
            motor_value[1] = -1 * turn_value;
            motor_value[2] = turn_value;
            motor_value[3] = turn_value;

            this->move_all(motor_value);
        }
        else if (abs(LX_1 - JOY_CENTER_LX_1) < abs(LY_1 - JOY_CENTER_LY_1) && abs(LY_1 - JOY_CENTER_LY_1) >= JOY_CENTER_THR)
        {
            int motor_value[4] = {0};
            int turn_value = map(LY_1, 0, 255, -100, 100);
            motor_value[0] = -1 * turn_value;
            motor_value[1] = -1 * turn_value;
            motor_value[2] = -1 * turn_value;
            motor_value[3] = -1 * turn_value;

            if (abs(RX_1 - JOY_CENTER_RX_1) >= JOY_CENTER_THR)
            {
                int offset_value = map(RX_1, 0, 255, -100, 100);
                if (offset_value >= 0)
                {   
                    // motor_value[0] += offset_value;
                    // motor_value[3] += offset_value;
                    motor_value[0] = int(float(motor_value[0]) * (130.0 - float(abs(offset_value))) / 100.0);
                    motor_value[3] = int(float(motor_value[0]) * (130.0 - float(abs(offset_value))) / 100.0);
                }
                else
                {
                    // motor_value[1] += offset_value;
                    // motor_value[2] += offset_value;
                    motor_value[1] = int(float(motor_value[0]) * (130.0 - float(abs(offset_value))) / 100.0);
                    motor_value[2] = int(float(motor_value[0]) * (130.0 - float(abs(offset_value))) / 100.0);
                }
            }
            this->move_all(motor_value);
        }
        else if (abs(RX_1 - JOY_CENTER_RX_1) >= JOY_CENTER_THR)
        {
            int motor_value[4] = {0};
            int turn_value = map(RX_1, 0, 255, -100, 100);
            motor_value[0] = turn_value;
            motor_value[1] = -1 * turn_value;
            motor_value[2] = -1 * turn_value;
            motor_value[3] = turn_value;

            this->move_all(motor_value);
        }
        else
        {
            int motor_value[4] = {0};
            this->move_all(motor_value);
        }
    }
}
void Controller::readControllerTest(PS2X &ps2x, int &error)
{
    if (error == 1) //skip loop if no controller found
        return;

    ps2x.read_gamepad(false, this->vibrate); //read controller and set large motor to spin at 'vibrate' speed
    if (ps2x.Button(PSB_START))              //will be TRUE as long as button is pressed
        Serial.println("Start is being held");
    if (ps2x.Button(PSB_SELECT))
        Serial.println("Select is being held");

    if (ps2x.Button(PSB_PAD_UP))
    { //will be TRUE as long as button is pressed
        Serial.print("Up held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
    if (ps2x.Button(PSB_PAD_RIGHT))
    {
        Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if (ps2x.Button(PSB_PAD_LEFT))
    {
        Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if (ps2x.Button(PSB_PAD_DOWN))
    {
        Serial.print("DOWN held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }

    vibrate = ps2x.Analog(PSAB_CROSS); //this will set the large motor vibrate speed based on how hard you press the blue (X) button
    if (ps2x.NewButtonState())
    { //will be TRUE if any button changes state (on to off, or off to on)
        if (ps2x.Button(PSB_L3))
            Serial.println("L3 pressed");
        if (ps2x.Button(PSB_R3))
            Serial.println("R3 pressed");
        if (ps2x.Button(PSB_L2))
            Serial.println("L2 pressed");
        if (ps2x.Button(PSB_R2))
            Serial.println("R2 pressed");
        if (ps2x.Button(PSB_TRIANGLE))
            Serial.println("Triangle pressed");
    }

    if (ps2x.ButtonPressed(PSB_CIRCLE)) //will be TRUE if button was JUST pressed
        Serial.println("Circle just pressed");
    if (ps2x.NewButtonState(PSB_CROSS)) //will be TRUE if button was JUST pressed OR released
        Serial.println("X just changed");
    if (ps2x.ButtonReleased(PSB_SQUARE)) //will be TRUE if button was JUST released
        Serial.println("Square just released");

    if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1))
    { //print stick values if either is TRUE
        Serial.print("Stick Values:");
        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC);
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC);
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC);
    }
}

void Controller::init(int PS2_BUTTON_PIN, int PS2_GND_1, int PS2_VCC_1, int PS2_CLK_1, int PS2_CMD_1, int PS2_SEL_1, int PS2_DAT_1,
                      int PS2_GND_2, int PS2_VCC_2, int PS2_CLK_2, int PS2_CMD_2, int PS2_SEL_2, int PS2_DAT_2)
{
    pinMode(PS2_GND_1, OUTPUT);
    pinMode(PS2_VCC_1, OUTPUT);
    pinMode(PS2_DAT_1, INPUT);
    pinMode(PS2_CMD_1, OUTPUT);
    pinMode(PS2_SEL_1, OUTPUT);
    pinMode(PS2_CLK_1, INPUT);

    pinMode(PS2_GND_2, OUTPUT);
    pinMode(PS2_VCC_2, OUTPUT);
    pinMode(PS2_DAT_2, INPUT);
    pinMode(PS2_CMD_2, OUTPUT);
    pinMode(PS2_SEL_2, OUTPUT);
    pinMode(PS2_CLK_2, INPUT);

    pinMode(PS2_BUTTON_PIN, INPUT_PULLUP);

    digitalWrite(PS2_GND_1, LOW);
    digitalWrite(PS2_VCC_1, LOW);
    digitalWrite(PS2_GND_2, LOW);
    digitalWrite(PS2_VCC_2, LOW);

    ClickButton button1(PS2_BUTTON_PIN, LOW, CLICKBTN_PULLUP);
    button1.longClickTime = 10;
    int start_controller_state = 0;
    bool controller_initial_flag = 0;
    while (true)
    {
        //Serial.print(start_controller_state);
        button1.Update();
        switch (start_controller_state)
        {
        case 0: // waiting
            if (button1.changed)
            {
                start_controller_state = 1;
                digitalWrite(PS2_VCC_1, HIGH);
                Serial.println("waiting for connecting controller [1]...");
            }
            break;
        case 1: // waiting for controller 1 to config
            if (button1.changed)
            {
                start_controller_state = 2;
                this->init_1(PS2_CLK_1, PS2_CMD_1, PS2_SEL_1, PS2_DAT_1);
                digitalWrite(PS2_VCC_2, HIGH);
                Serial.println("waiting for connecting controller [2]...");
            }
            break;
        case 2: // waiting for controller 1 to config
            if (button1.changed)
            {
                controller_initial_flag = 1;
                start_controller_state = 3;
                this->init_2(PS2_CLK_2, PS2_CMD_2, PS2_SEL_2, PS2_DAT_2);
            }
            break;
        default:
            controller_initial_flag = 1;
            break;
        }
        if (controller_initial_flag)
            break;
    }
}

void Controller::init_1(int PS2_CLK_1, int PS2_CMD_1, int PS2_SEL_1, int PS2_DAT_1)
{
    this->error_1 = this->ps2x_1.config_gamepad(PS2_CLK_1, PS2_CMD_1, PS2_SEL_1, PS2_DAT_1, this->pressures, this->rumble);
#ifdef DEBUG
    if (this->error_1 == 0)
    {
        Serial.println("[#1] Found Controller, configured successful!");
    }
    else
    {
        Serial.println("[#1] Controller Error!");
    }
#endif
}

void Controller::init_2(int PS2_CLK_2, int PS2_CMD_2, int PS2_SEL_2, int PS2_DAT_2)
{
    this->error_2 = this->ps2x_2.config_gamepad(PS2_CLK_2, PS2_CMD_2, PS2_SEL_2, PS2_DAT_2, this->pressures, this->rumble);
#ifdef DEBUG
    if (this->error_2 == 0)
    {
        Serial.println("[#2] Found Controller, configured successful!");
    }
    else
    {
        Serial.println("[#2] Controller Error!");
    }
#endif
}
