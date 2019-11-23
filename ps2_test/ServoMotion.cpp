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
    _claw_pos = POS_CLAW_OPEN;
}

void Arm::clawClose()
{
    claw.Move(POS_CLAW_CLOSE, 200);
    _claw_pos = POS_CLAW_CLOSE;
}

void Arm::clawOpenDx()
{
    int new_pos = _claw_pos + DX_CLAW;
    if (new_pos <= POS_CLAW_OPEN && new_pos >= POS_CLAW_CLOSE)
    {
        _claw_pos = new_pos;
        claw.Move(_claw_pos, 0);
    }
}

void Arm::clawCloseDx()
{
    int new_pos = _claw_pos - DX_CLAW;
    if (new_pos <= POS_CLAW_OPEN && new_pos >= POS_CLAW_CLOSE)
    {
        _claw_pos = new_pos;
        claw.Move(_claw_pos, 0);
    }
}

void Arm::readyMode(int from_fold)
{
    if (from_fold)
    {
        claw.Move(POS_CLAW_PARALLEL, 500);
        shoulder.Move(POS_ARM_SHOULDER_V, 500);
        elbow.Move(POS_ARM_ELBOW_MIN, 500);
        delay(500);
    }
    shoulder.Move(POS_ARM_SHOULDER_H, 500);
    delay(500);
    elbow.Move(POS_ARM_ELBOW_MAX, 500);
    delay(500);
    shoulder.Move(POS_ARM_SHOULDER_V, 500);
    claw.Move(POS_CLAW_PARALLEL, 500);
    _shoulder_pos = POS_ARM_SHOULDER_V;
    _claw_pos = POS_CLAW_PARALLEL;
}

void Arm::foldMode()
{
    claw.Move(POS_CLAW_PARALLEL, 500);
    shoulder.Move(POS_ARM_SHOULDER_H, 500);
    delay(500);
    elbow.Move(POS_ARM_ELBOW_MIN, 500);
    delay(1000);
    shoulder.Move(POS_ARM_SHOULDER_MIN, 500);
    elbow.Move(POS_ARM_ELBOW_FOLD, 500);

    _shoulder_pos = POS_ARM_SHOULDER_MIN;
    delay(1000);
    shoulder.Unload();
    elbow.Unload();
}

void Arm::pick()
{
}

void Arm::switchMode()
{
}

void Arm::catchMode(int from_fold)
{
    if (from_fold)
    {
        claw.Move(POS_CLAW_PARALLEL, 500);
        shoulder.Move(POS_ARM_SHOULDER_V, 500);
        elbow.Move(POS_ARM_ELBOW_MIN, 500);
        delay(500);
    }
    shoulder.Move(POS_ARM_SHOULDER_H, 500);
    delay(1000);
    elbow.Move(POS_ARM_ELBOW_V, 500);
    claw.Move(POS_CLAW_OPEN, 500);
    _shoulder_pos = POS_ARM_SHOULDER_H;
    _claw_pos = POS_CLAW_OPEN;
}

void Arm::put()
{
    claw.Move(POS_CLAW_CLOSE, 500);
    delay(1000);
    shoulder.Move(POS_ARM_SHOULDER_PUT, 2000);
    elbow.Move(POS_ARM_ELBOW_MAX, 2000);
    delay(1000);
    claw.Move(POS_CLAW_OPEN, 500);
    delay(1000);
}

void Arm::verticalUp()
{
    int new_pos = _shoulder_pos + DX_ARM;
    uint16_t elbow_pos = POS_ARM_SHOULDER_H + POS_ARM_ELBOW_V - new_pos;
    if (new_pos <= POS_ARM_SHOULDER_MAX && new_pos >= POS_ARM_SHOULDER_MIN &&
        elbow_pos <= POS_ARM_ELBOW_MAX && elbow_pos >= POS_ARM_ELBOW_MIN)
    {
        _shoulder_pos = new_pos;
        shoulder.Move(_shoulder_pos, 0);
        elbow.Move(elbow_pos, 0);
    }
}

void Arm::verticalDown()
{
    int new_pos = _shoulder_pos - DX_ARM;
    uint16_t elbow_pos = POS_ARM_SHOULDER_H + POS_ARM_ELBOW_V - new_pos;
    if (new_pos <= POS_ARM_SHOULDER_MAX && new_pos >= POS_ARM_SHOULDER_MIN &&
        elbow_pos <= POS_ARM_ELBOW_MAX && elbow_pos >= POS_ARM_ELBOW_MIN)
    {
        _shoulder_pos = new_pos;
        shoulder.Move(_shoulder_pos, 0);
        elbow.Move(elbow_pos, 0);
    }
}

void Arm::horizontalUp()
{
    int new_pos = _shoulder_pos + DX_ARM;
    uint16_t elbow_pos = POS_ARM_SHOULDER_V + POS_ARM_ELBOW_H - new_pos;
    if (new_pos <= POS_ARM_SHOULDER_MAX && new_pos >= POS_ARM_SHOULDER_MIN &&
        elbow_pos <= POS_ARM_ELBOW_MAX && elbow_pos >= POS_ARM_ELBOW_MIN)
    {
        _shoulder_pos = new_pos;
        shoulder.Move(_shoulder_pos, 0);
        elbow.Move(elbow_pos, 0);
    }
}

void Arm::horizontalDown()
{
    int new_pos = _shoulder_pos - DX_ARM;
    uint16_t elbow_pos = POS_ARM_SHOULDER_V + POS_ARM_ELBOW_H - new_pos;
    if (new_pos <= POS_ARM_SHOULDER_MAX && new_pos >= POS_ARM_SHOULDER_MIN &&
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
    if (_shovel_pos <= POS_SHOVEL_DOWN)
        _shovel_pos = POS_SHOVEL_DOWN;
    if (_shovel_pos >= POS_SHOVEL_UP)
        _shovel_pos = POS_SHOVEL_UP;
    shovel.Move(_shovel_pos, 0);
}

void Shovel::readyMode()
{
    shovelDown();
    delay(1000);
    shoulder.Move(POS_SHOVEL_SHOULDER_H, 500);
    delay(500);
    elbow.Move(POS_SHOVEL_ELBOW_READY, 500);
    _shoulder_pos = POS_SHOVEL_SHOULDER_H;
    _elbow_pos = POS_SHOVEL_ELBOW_READY;
}

void Shovel::foldMode()
{
    elbow.Move(POS_SHOVEL_ELBOW_MAX, 1000);
    delay(500);
    shoulder.Move(POS_SHOVEL_SHOULDER_MIN, 1000);
    delay(1000);
    shovelUp();
    elbow.Unload();
    shoulder.Unload();
}

void Shovel::shoulderUp()
{
    int new_pos = _shoulder_pos - DX_SHOULDER;
    if (new_pos > POS_SHOVEL_SHOULDER_MAX || new_pos < POS_SHOVEL_SHOULDER_MIN)
        return;
    _shoulder_pos = new_pos;
    shoulder.Move(_shoulder_pos,0);
}

void Shovel::shoulderDown()
{
    int new_pos = _shoulder_pos + DX_SHOULDER;
    if (new_pos > POS_SHOVEL_SHOULDER_MAX || new_pos < POS_SHOVEL_SHOULDER_MIN)
        return;
    _shoulder_pos = new_pos;
    shoulder.Move(_shoulder_pos,0);
}

void Shovel::elbowUp()
{
    int new_pos = _elbow_pos + DX_ELBOW;
    if (new_pos > POS_SHOVEL_ELBOW_MAX || new_pos < POS_SHOVEL_ELBOW_MIN)
        return;
    _elbow_pos = new_pos;
    elbow.Move(_elbow_pos,0);
}

void Shovel::elbowDown()
{
    int new_pos = _elbow_pos - DX_ELBOW;
    if (new_pos > POS_SHOVEL_ELBOW_MAX || new_pos < POS_SHOVEL_ELBOW_MIN)
        return;
    _elbow_pos = new_pos;
    elbow.Move(_elbow_pos,0);
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
    pinMode(52, INPUT_PULLUP);
}

void Bucket::doorOpen()
{
    door.Move(POS_DOOR_OPEN, 500);
}

void Bucket::doorClose()
{
    door.Move(POS_DOOR_CLOSE, 500);
}

void Bucket::baseUp(PS2X &ps2x)
{
    //if (_base_pos == 5) return;
    int empty_count = 0;
    base.SetMode(1, -500);
    while (true)
    {
        if (digitalRead(52) == 0)
            break;
        if (!ps2x.read_gamepad(false, 0))
            continue;
        int LX_1 = int(ps2x.Analog(PSS_LX));
        int LY_1 = int(ps2x.Analog(PSS_LY));
        int RX_1 = int(ps2x.Analog(PSS_RX));
        int RY_1 = int(ps2x.Analog(PSS_RY));
        if (LX_1 == 0 && LY_1 == 0 && RX_1 == 0 && RY_1 == 0)
            continue;

        if (!ps2x.Button(PSB_PAD_UP))
            empty_count++;
        if (empty_count >= 3)
            break;
        delay(10);
    }
    base.SetMode(1, 0);
    //_base_pos++;
}

void Bucket::baseDown(PS2X &ps2x)
{
    //if (_base_pos == 0) return;
    int empty_count = 0;
    base.SetMode(1, 500);
    while (true)
    {
        if (!ps2x.read_gamepad(false, 0))
            continue;
        int LX_1 = int(ps2x.Analog(PSS_LX));
        int LY_1 = int(ps2x.Analog(PSS_LY));
        int RX_1 = int(ps2x.Analog(PSS_RX));
        int RY_1 = int(ps2x.Analog(PSS_RY));
        if (LX_1 == 0 && LY_1 == 0 && RX_1 == 0 && RY_1 == 0)
            continue;

        if (!ps2x.Button(PSB_PAD_DOWN))
            empty_count++;
        if (empty_count >= 3)
            break;
        delay(10);
    }
    base.SetMode(1, 0);
    //_base_pos--;
}

void Bucket::open()
{
    doorOpen();
}

void Bucket::close()
{
    doorClose();
}
