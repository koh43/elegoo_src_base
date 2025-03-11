#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <ArduinoSTL.h>
#include <array>
#include "I2Cdev.h"
#include "MPU6050.h"

class IMU {
public:
    IMU(MPU6050& mpu);
    ~IMU();
    void Init();
    void Update(char* imu_str);
    void setOffsets(const std::array<int16_t, 6>& offsets);
    std::array<int16_t, 6> getOffsets();
private:
    /*---MPU6050 Calibration Variables---*/
    MPU6050* mpu_;
    VectorInt16 accel_;
    VectorInt16 gyro_;
    std::array<int16_t, 6> offsets_ = {-3965, -3717, 1169, 68, 42, -19};
};

#endif // IMU_H