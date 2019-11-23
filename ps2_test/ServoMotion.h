#include <Arduino.h>
#include "LobotSerialServo.h"
#include "PS2X_lib.h" //for v1.6

/****************************************************************************************/
// Arm
#define POS_CLAW_OPEN 700
#define POS_CLAW_CLOSE 380
#define POS_CLAW_PARALLEL 570

#define POS_ARM_ELBOW_MIN 50
#define POS_ARM_ELBOW_MAX 1000
#define POS_ARM_ELBOW_H 1000
#define POS_ARM_ELBOW_FOLD 150
#define POS_ARM_ELBOW_V 250

#define POS_ARM_SHOULDER_H 500
#define POS_ARM_SHOULDER_V 150
#define POS_ARM_SHOULDER_PUT 900
#define POS_ARM_SHOULDER_MAX 1000
#define POS_ARM_SHOULDER_MIN 100

#define DX_ARM 4
#define DX_CLAW 3
/****************************************************************************************/
// Shovel
#define POS_SHOVEL_DOWN 300
#define POS_SHOVEL_UP 800
#define POS_SHOVEL_H 400 //horizental

#define POS_SHOVEL_ELBOW_MIN 50
#define POS_SHOVEL_ELBOW_MAX 1000

#define POS_SHOVEL_SHOULDER_MIN 100
#define POS_SHOVEL_SHOULDER_MAX 1000
/****************************************************************************************/
// Bucket
#define POS_DOOR_OPEN 590
#define POS_DOOR_CLOSE 190
#define POS_BASE_UP 600
#define POS_BASE_DOWN 1000

// shovel parameterd
#define LEN_SHOVEL_L1 198
#define LEN_SHOVEL_L2 229

/*class Body
{
public:
    Body(uint8_t pins[])
    {
        for (int i = 0; i < 8; ++i)
            _pins[i] = pins[i];
        for (int i = 0; i < 8; ++i)
            pinMode(_pins[i], OUTPUT);
    }
    void forward()
    {
        bool dir[8] = {1, 0, 1, 0, 1, 0, 1, 0};
        for (int i = 0; i < 8; ++i)
            digitalWrite(_pins[i], dir[i]);
    }
    void backward()
    {
        bool dir[8] = {0, 1, 0, 1, 0, 1, 0, 1};
        for (int i = 0; i < 8; ++i)
            digitalWrite(_pins[i], dir[i]);
    }
    void moveRight()
    {
        bool dir[8] = {1, 0, 0, 1, 1, 0, 0, 1};
        for (int i = 0; i < 8; ++i)
            digitalWrite(_pins[i], dir[i]);
    }
    void moveLeft()
    {
        bool dir[8] = {0, 1, 1, 0, 0, 1, 1, 0};
        for (int i = 0; i < 8; ++i)
            digitalWrite(_pins[i], dir[i]);
    }
    void turnRight()
    {
        bool dir[8] = {1, 0, 0, 1, 0, 1, 1, 0};
        for (int i = 0; i < 8; ++i)
            digitalWrite(_pins[i], dir[i]);
    }
    void turnLeft()
    {
        bool dir[8] = {0, 1, 1, 0, 1, 0, 0, 1};
        for (int i = 0; i < 8; ++i)
            digitalWrite(_pins[i], dir[i]);
    }
    void stop()
    {
        bool dir[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        for (int i = 0; i < 8; ++i)
            digitalWrite(_pins[i], dir[i]);
    }

private:
    uint8_t _pins[8];
};*/

class Arm
{
public:
    Arm(HardwareSerial &A, uint8_t ids[])
    {
        shoulder.Init(A, ids[0]);
        elbow.Init(A, ids[1]);
        claw.Init(A, ids[2]);
    }
    Arm() {}

    void init(HardwareSerial &A, uint8_t ids[]);

    void clawOpen();
    void clawClose();
    void clawOpenDx();
    void clawCloseDx();
    void readyMode(int from_fold = 0);
    void foldMode();
    void switchMode();
    void put();
    void pick();
    void catchMode(int from_fold = 0);
    void verticalUp();
    void verticalDown();
    void horizontalUp();
    void horizontalDown();

private:
    LobotSerialServo claw;
    LobotSerialServo elbow;
    LobotSerialServo shoulder;
    uint16_t _shoulder_pos;
    uint16_t _claw_pos;
};

class Shovel
{
public:
    Shovel(HardwareSerial &A, uint8_t ids[])
    {
        shoulder.Init(A, ids[0]);
        elbow.Init(A, ids[1]);
        shovel.Init(A, ids[2]);
    }
    Shovel() {}
    
    void init(HardwareSerial &A, uint8_t ids[]);
    
    void shovelUp();
    void shovelDown();
    void shovelUpdate(int dx);
    void ready();

    void fold();
    void pick();
    void move_up();
    void move_down();
private:
    LobotSerialServo shovel;
    LobotSerialServo elbow;
    LobotSerialServo shoulder;
    uint16_t _shovel_pos;
};

class Bucket
{
public:
    Bucket(HardwareSerial &A, uint8_t ids[])
    {
        door.Init(A, ids[0]);
        base.Init(A, ids[1]);
    }
    Bucket() {}

    void init(HardwareSerial &A, uint8_t ids[]);
    void doorOpen();
    void doorClose();
    void baseUp(PS2X &ps2x);
    void baseDown(PS2X &ps2x);
    void open();
    void close();

private:
    LobotSerialServo base;
    LobotSerialServo door;
    int _base_pos = 0;
};
