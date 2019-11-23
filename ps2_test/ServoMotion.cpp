#include "ServoMotion.h"


/****************************************************************************************/
void Arm::init(HardwareSerial &A, uint8_t ids[])
{
    shoulder.Init(A, ids[0]);
    elbow.Init(A, ids[1]);
    claw.Init(A, ids[2]);
}

void Arm::clawOpen()
{
    claw.Move(POS_CLAW_OPEN, 200);
}

void Arm::clawClose()
{
    claw.Move(POS_CLAW_CLOSE, 200);
}

void Arm::ready()
{
    claw.Move(POS_CLAW_PARALLEL, 500);
    elbow.Move(150, 500);
    shoulder.Move(POS_ARM_SOULDER_V, 500);
    delay(500);
    shoulder.Move(POS_ARM_SOULDER_H, 500);
    delay(500);
    elbow.Move(1000, 500);
    delay(500);
    shoulder.Move(POS_ARM_SOULDER_V, 500);
}

void Arm::fold()
{
    claw.Move(POS_CLAW_PARALLEL, 500);
    shoulder.Move(POS_ARM_SOULDER_H, 500);
    delay(500);
    elbow.Move(150, 500);
    delay(1000);
    shoulder.Move(POS_ARM_SOULDER_V, 500);
}

void Arm::pick()
{

}

void Arm::touchSwitch()
{

}
/****************************************************************************************/
void Shovel::init(HardwareSerial &A, uint8_t ids[])
{
    shoulder.Init(A, ids[0]);
    elbow.Init(A, ids[1]);
    shovel.Init(A, ids[2]);
    _shovel_pos = POS_SHOVEL_UP;
}

void Shovel::shovelUp()
{
    shovel.Move(POS_SHOVEL_UP, 500);
    _shovel_pos = POS_SHOVEL_UP;
}

void Shovel::shovelDown()
{
    shovel.Move(POS_SHOVEL_DOWN, 200);
    _shovel_pos = POS_SHOVEL_DOWN;
}

void Shovel::shovelUpdate(int dx)
{
    _shovel_pos += dx;
    if (_shovel_pos <= POS_SHOVEL_DOWN) _shovel_pos = POS_SHOVEL_DOWN;
    if (_shovel_pos >= POS_SHOVEL_UP) _shovel_pos = POS_SHOVEL_UP;
    shovel.Move(_shovel_pos, 0);
}

void Shovel::ready()
{
    shovelDown();
    delay(1000);
    shoulder.Move(POS_SHOVEL_SHOULDER_MAX, 200);
    delay(500);
    elbow.Move(POS_SHOVEL_ELBOW_MAX, 200);
}

void Shovel::fold()
{
    elbow.Move(POS_SHOVEL_ELBOW_MIN, 500);
    delay(500);
    shoulder.Move(POS_SHOVEL_SHOULDER_MIN, 500);
    delay(1000);
    shovelUp();
}

void Shovel::move_up()
{
    shovelUpdate(10);
}

void Shovel::move_down()
{
    shovelUpdate(-10);
}

void Shovel::pick()
{

}
/****************************************************************************************/
void Bucket::init(HardwareSerial &A, uint8_t ids[])
{
    door.Init(A, ids[0]);
    base.Init(A, ids[1]);
}

void Bucket::doorOpen()
{
    door.Move(POS_DOOR_OPEN, 500);
}

void Bucket::doorClose()
{
    door.Move(POS_DOOR_CLOSE, 200);
}

void Bucket::baseUp()
{
    base.Move(POS_BASE_UP, 1000);
}

void Bucket::baseDown()
{
    base.Move(POS_BASE_DOWN, 1000);
}

void Bucket::open(){
    this->doorOpen();
}

void Bucket::close(){
    this->doorClose();
}