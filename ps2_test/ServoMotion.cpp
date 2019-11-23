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

void Arm::readyMode()
{
    claw.Move(POS_CLAW_PARALLEL, 500);
    shoulder.Move(POS_ARM_SHOULDER_V, 500);
    elbow.Move(POS_ARM_ELBOW_MIN, 500);
    delay(500);
    shoulder.Move(POS_ARM_SHOULDER_H, 500);
    delay(500);
    elbow.Move(POS_ARM_ELBOW_MAX, 500);
    delay(500);
    shoulder.Move(POS_ARM_SHOULDER_V, 500);
}

void Arm::foldMode()
{
    claw.Move(POS_CLAW_PARALLEL, 500);
    shoulder.Move(POS_ARM_SHOULDER_H, 500);
    delay(500);
    elbow.Move(POS_ARM_ELBOW_MIN, 500);
    delay(1000);
    shoulder.Move(POS_ARM_SHOULDER_V, 500);
    elbow.Move(POS_ARM_ELBOW_FOLD, 500);
}

void Arm::pick()
{

}

void Arm::switchMode()
{
    
}

void Arm::catchMode()
{
    shoulder.Move(POS_ARM_SHOULDER_H, 500);
    delay(1000);
    elbow.Move(POS_ARM_ELBOW_V, 500);
    claw.Move(POS_CLAW_OPEN, 500);
    _shoulder_pos = POS_ARM_SHOULDER_H;
}

void Arm::put()
{
    claw.Move(POS_CLAW_CLOSE, 500);
    delay(1000);
    shoulder.Move(POS_ARM_SHOULDER_PUT, 1000);
    elbow.Move(POS_ARM_ELBOW_MAX, 1000);
    delay(1000);
    claw.Move(POS_CLAW_OPEN, 500);
    delay(1000);
    catchMode();
}

void Arm::verticalUp() {
    int new_pos = _shoulder_pos + 5;
    uint16_t elbow_pos = POS_ARM_SHOULDER_H + POS_ARM_ELBOW_V - new_pos;
    if (new_pos <= POS_ARM_SHOULDER_MAX && new_pos >= POS_ARM_SHOULDER_V &&
        elbow_pos <= POS_ARM_ELBOW_MAX && elbow_pos >= POS_ARM_ELBOW_MIN)
    {
        _shoulder_pos = new_pos;
        shoulder.Move(_shoulder_pos, 0);
        elbow.Move(elbow_pos, 0);
        
    }
    
}

void Arm::verticalDown() {
    int new_pos = _shoulder_pos - 5;
    uint16_t elbow_pos = POS_ARM_SHOULDER_H + POS_ARM_ELBOW_V - new_pos;
    if (new_pos <= POS_ARM_SHOULDER_MAX && new_pos >= POS_ARM_SHOULDER_V &&
        elbow_pos <= POS_ARM_ELBOW_MAX && elbow_pos >= POS_ARM_ELBOW_MIN)
    {
        _shoulder_pos = new_pos;
        shoulder.Move(_shoulder_pos, 0);
        elbow.Move(elbow_pos, 0);
    }
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
    door.Move(POS_DOOR_CLOSE, 500);
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