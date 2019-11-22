#include "PS2X_lib.h" //for v1.6

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
};
