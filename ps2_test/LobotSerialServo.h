#ifndef LOBOTSERIALSERVO_H
#define LOBOTSERIALSERVO_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#define GET_LOW_BYTE(A) (uint8_t)((A))

#define GET_HIGH_BYTE(A) (uint8_t)((A) >> 8)

#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))

#define LOBOT_SERVO_FRAME_HEADER         0x55
#define LOBOT_SERVO_MOVE_TIME_WRITE      1
#define LOBOT_SERVO_MOVE_TIME_READ       2
#define LOBOT_SERVO_MOVE_TIME_WAIT_WRITE 7
#define LOBOT_SERVO_MOVE_TIME_WAIT_READ  8
#define LOBOT_SERVO_MOVE_START           11
#define LOBOT_SERVO_MOVE_STOP            12
#define LOBOT_SERVO_ID_WRITE             13
#define LOBOT_SERVO_ID_READ              14
#define LOBOT_SERVO_ANGLE_OFFSET_ADJUST  17
#define LOBOT_SERVO_ANGLE_OFFSET_WRITE   18
#define LOBOT_SERVO_ANGLE_OFFSET_READ    19
#define LOBOT_SERVO_ANGLE_LIMIT_WRITE    20
#define LOBOT_SERVO_ANGLE_LIMIT_READ     21
#define LOBOT_SERVO_VIN_LIMIT_WRITE      22
#define LOBOT_SERVO_VIN_LIMIT_READ       23
#define LOBOT_SERVO_TEMP_MAX_LIMIT_WRITE 24
#define LOBOT_SERVO_TEMP_MAX_LIMIT_READ  25
#define LOBOT_SERVO_TEMP_READ            26
#define LOBOT_SERVO_VIN_READ             27
#define LOBOT_SERVO_POS_READ             28
#define LOBOT_SERVO_OR_MOTOR_MODE_WRITE  29
#define LOBOT_SERVO_OR_MOTOR_MODE_READ   30
#define LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE 31
#define LOBOT_SERVO_LOAD_OR_UNLOAD_READ  32
#define LOBOT_SERVO_LED_CTRL_WRITE       33
#define LOBOT_SERVO_LED_CTRL_READ        34
#define LOBOT_SERVO_LED_ERROR_WRITE      35
#define LOBOT_SERVO_LED_ERROR_READ       36

//#define LOBOT_DEBUG 1

class LobotSerialServo{
    public:
        LobotSerialServo() {};
        LobotSerialServo(SoftwareSerial &A, uint8_t) { SerialX = (Stream*)(&A); A.listen(); }
	    LobotSerialServo(HardwareSerial &A, uint8_t) { SerialX = (Stream*)(&A); }

        uint8_t CheckSum(uint8_t buf[]);
        void Init(HardwareSerial &A, uint8_t id) { _id = id; SerialX = (Stream*)(&A);}
        void Move(int16_t position, uint16_t time);
        void StopMove();
        void SetID(uint8_t newID);
        void SetMode(uint8_t Mode, int16_t Speed);
        void Load();
        void Unload();
        int ReceiveHandle(uint8_t *ret);
        int ReadPosition();
        int ReadVin();

    private:
        Stream *SerialX;
        uint8_t _id = 0;
};
#endif