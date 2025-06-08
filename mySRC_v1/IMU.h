#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <ArduinoSTL.h>
#include <array>
#include "I2Cdev.h"
#include "MPU6050.h"

constexpr uint16_t usDelay = 3150; // empirical, to hold sampling to 200 Hz
constexpr uint16_t NFast = 1000;   // the bigger, the better (but slower)
constexpr uint16_t NSlow = 10000;  // ..

constexpr uint8_t iAx = 0;
constexpr uint8_t iAy = 1;
constexpr uint8_t iAz = 2;
constexpr uint8_t iGx = 3;
constexpr uint8_t iGy = 4;
constexpr uint8_t iGz = 5;

constexpr int16_t target[6] = {0, 0, 16384, 0, 0, 0};

class IMU {
public:
    IMU(MPU6050& mpu);
    ~IMU();
    void Init();
    void Update(char* imu_str);
    void setOffsets(const std::array<int16_t, 6>& offsets);
    void getOffsets(std::array<int16_t, 6>& offsets);
private:
    /*---MPU6050 Calibration Variables---*/
    MPU6050* mpu_;
    VectorInt16 accel_;
    VectorInt16 gyro_;
    std::array<int16_t, 6> lowOffset_ = {0, 0, 0, 0, 0, 0};
    std::array<int16_t, 6> highOffset_ = {0, 0, 0, 0, 0, 0};
    void PullBracketsOut();
    void PullBracketsIn();
    void GetSmoothed(int N, std::array<int16_t, 6>& smoothed);
    uint8_t linesOut_ = 0;
    static constexpr uint8_t linesBetweenHeaders_ = 5;
    void ShowProgress();
    // std::array<int16_t, 6> offsets_ = {-3965, -3717, 1169, 68, 42, -19};
};

#endif // IMU_H