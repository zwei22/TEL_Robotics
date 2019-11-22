#include <Arduino.h>
#include "LobotSerialServo.h"

#define POS_CLAW_OPEN 700
#define POS_CLAW_CLOSE 400
#define POS_CLAW_PARALLEL 570

#define POS_SHOVEL_DOWN 780
#define POS_SHOVEL_UP 290
#define POS_SHOVEL_ELBOW_MIN 310
#define POS_SHOVEL_ELBOW_MAX 1000
#define POS_SHOVEL_SHOULDER_MIN 310
#define POS_SHOVEL_SHOULDER_MAX 1000

#define POS_DOOR_OPEN 600
#define POS_DOOR_CLOSE 1000
#define POS_BASE_UP 600
#define POS_BASE_DOWN 1000

class Body
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
};

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
    void init(HardwareSerial &A, uint8_t ids[])
    {
        shoulder.Init(A, ids[0]);
        elbow.Init(A, ids[1]);
        claw.Init(A, ids[2]);
    }
    void clawOpen()
    {
        claw.Move(POS_CLAW_OPEN, 200);
    }
    void clawClose()
    {
        claw.Move(POS_CLAW_CLOSE, 200);
    }
    void ready()
    {
        claw.Move(POS_CLAW_PARALLEL, 500);
        elbow.Move(0, 500);
        shoulder.Move(100, 500);
        delay(500);
        shoulder.Move(500, 500);
        delay(500);
        elbow.Move(960, 500);
        delay(500);
        shoulder.Move(100, 500);
    }

    void fold()
    {
        claw.Move(POS_CLAW_PARALLEL, 500);
        shoulder.Move(500, 500);
        delay(500);
        elbow.Move(0, 500);
        delay(1000);
        shoulder.Move(100, 500);
    }
    void touchSwitch()
    {
    }
    void pick()
    {
    }

private:
    LobotSerialServo claw;
    LobotSerialServo elbow;
    LobotSerialServo shoulder;
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
    void init(HardwareSerial &A, uint8_t ids[])
    {
        shoulder.Init(A, ids[0]);
        elbow.Init(A, ids[1]);
        shovel.Init(A, ids[2]);
    }
    void shovelUp()
    {
        shovel.Move(POS_SHOVEL_UP, 500);
    }
    void shovelDown()
    {
        shovel.Move(POS_SHOVEL_DOWN, 200);
    }
    void ready()
    {
        shovelDown();
        delay(1000);
        shoulder.Move(POS_SHOVEL_SHOULDER_MAX, 200);
        delay(500);
        elbow.Move(POS_SHOVEL_ELBOW_MAX, 200);
    }
    void idle()
    {
        elbow.Move(POS_SHOVEL_ELBOW_MIN, 500);
        delay(500);
        shoulder.Move(POS_SHOVEL_SHOULDER_MIN, 500);
        delay(1000);
        shovelUp();
    }
    void pick(){

    }
    void move_up()
    {

    }
    void move_down()
    {
        
    }
private:
    LobotSerialServo shovel;
    LobotSerialServo elbow;
    LobotSerialServo shoulder;
};

class Bucket
{
public:
    Bucket(HardwareSerial &A, uint8_t ids[])
    {
        base.Init(A, ids[0]);
        door.Init(A, ids[1]);
    }
    Bucket() {}
    void init(HardwareSerial &A, uint8_t ids[])
    {
        base.Init(A, ids[0]);
        door.Init(A, ids[1]);
    }
    void doorOpen()
    {
        door.Move(POS_DOOR_OPEN, 500);
    }
    void doorClose()
    {
        door.Move(POS_DOOR_CLOSE, 200);
    }
    void baseUp()
    {
        base.Move(POS_BASE_UP, 1000);
    }
    void baseDown()
    {
        base.Move(POS_BASE_DOWN, 1000);
    }
    void open(){

    }
    void close(){
        
    }
private:
    LobotSerialServo base;
    LobotSerialServo door;
};
