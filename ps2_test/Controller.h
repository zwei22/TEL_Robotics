#include "PS2X_lib.h" //for v1.6
#include "ServoMotion.h"

class Controller
{
public:
    Controller(){};
    void init(int PS2_BUTTON_PIN, int PS2_GND_1, int PS2_VCC_1, int PS2_CLK_1, int PS2_CMD_1, int PS2_SEL_1, int PS2_DAT_1,
              int PS2_GND_2, int PS2_VCC_2, int PS2_CLK_2, int PS2_CMD_2, int PS2_SEL_2, int PS2_DAT_2);
    void init_1(int PS2_CLK_1, int PS2_CMD_1, int PS2_SEL_1, int PS2_DAT_1);
    void init_2(int PS2_CLK_2, int PS2_CMD_2, int PS2_SEL_2, int PS2_DAT_2);
    void print()
    {
        readControllerTest(ps2x_1, error_1);
        readControllerTest(ps2x_2, error_2);
    }
    void readControllerTest(PS2X &ps2x, int &error);
    void readControllerCommand();
    void checkPlayer_1();
    void checkPlayer_2();
    void move_all(int motor_value[])
    {
        Serial.print("MOVE_ALL: ");
        Serial.print(motor_value[0]);
        Serial.print(", ");
        Serial.print(motor_value[0]);
        Serial.print(", ");
        Serial.print(motor_value[0]);
        Serial.print(", ");
        Serial.println(motor_value[0]);
        for (int i = 0; i < 4; ++i)
        {
            if (motor_value[i] > 100)
                motor_value[i] = 100;
            if (motor_value[i] < -100)
                motor_value[i] = -100;

            if (motor_value[i] >= 0)
            {
                int motort_output = map(motor_value[i], 0, 100, 0, 255);
                analogWrite(body_pins[i * 2], motort_output);
                analogWrite(body_pins[i * 2 + 1], 0);
            }
            else
            {
                int motort_output = map(-1 * motor_value[i], 0, 100, 0, 255);
                analogWrite(body_pins[i * 2 + 1], motort_output);
                analogWrite(body_pins[i * 2], 0);
            }
        }
    }
    void brake()
    {
        for (int i = 0; i < 8; ++i)
        {
            digitalWrite(body_pins[i], HIGH);
        }
        Serial.println("BRAKE!");
    }

private:
    PS2X ps2x_1; // create PS2 Controller Class
    PS2X ps2x_2; // create PS2 Controller Class

    int error_1 = 0;
    byte type_1 = 0;
    int error_2 = 0;
    byte type_2 = 0;
    byte vibrate = 0;
    bool pressures = false;
    bool rumble = false;
    uint8_t body_pins[8] = {4, 5, 6, 7, 8, 9, 10, 11};
    uint8_t armIds[3] = {0, 1, 2};
    Arm arm;
    uint8_t shovelIds[3] = {3, 4, 5};
    Shovel shovel;
    uint8_t bucketIds[2] = {6, 7};
    Bucket bucket;

    int controller_state = 0;
    int controller_state_1 = 0;
    int controller_state_2 = 1;
    int controller_arm_state = 0;
    int controller_shovel_state = 0;
    int controller_bucket_state = 0;
    int controller_door_state = 0;
};
