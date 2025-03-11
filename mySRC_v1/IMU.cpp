#include "IMU.h"

IMU::IMU(MPU6050& mpu) : mpu_(&mpu) {};

IMU::~IMU() {

}

void IMU::Init() {
    Wire.begin();
    /*Initialize device and check connection*/ 
    Serial.println("Initializing mpu_->->..");
    mpu_->initialize();
    Serial.println("Testing MPU6050 connection...");
    if(mpu_->testConnection() ==  false){
        Serial.println("MPU6050 connection failed");
        while(true);
    }
    else{
        Serial.println("MPU6050 connection successful");
    }
    Serial.println("Applying offsets...");
    setOffsets(offsets_);
}

void IMU::Update(char* imu_str) {
    mpu_->getMotion6(
        &accel_.x, &accel_.y, &accel_.z,
        &gyro_.x, &gyro_.y, &gyro_.z
    );
    snprintf(
        imu_str, 50, "IMU:%d,%d,%d,%d,%d,%d%%",
        accel_.x, accel_.y, accel_.z,
        gyro_.x, gyro_.y, gyro_.z
    );
}

void IMU::setOffsets(const std::array<int16_t, 6>& offsets) {
    mpu_->setXAccelOffset(offsets[0]); //Set your accelerometer offset for axis X
    mpu_->setYAccelOffset(offsets[1]); //Set your accelerometer offset for axis Y
    mpu_->setZAccelOffset(offsets[2]); //Set your accelerometer offset for axis Z
    mpu_->setXGyroOffset(offsets[3]);  //Set your gyro offset for axis X
    mpu_->setYGyroOffset(offsets[4]);  //Set your gyro offset for axis Y
    mpu_->setZGyroOffset(offsets[5]);  //Set your gyro offset for axis Z
}

std::array<int16_t, 6> IMU::getOffsets() {
    std::array<int16_t, 6> offsets;
    offsets[0] = mpu_->getXAccelOffset();
    offsets[1] = mpu_->getYAccelOffset();
    offsets[2] = mpu_->getZAccelOffset();
    offsets[3] = mpu_->getXGyroOffset();
    offsets[4] = mpu_->getYGyroOffset();
    offsets[5] = mpu_->getZGyroOffset();
    return offsets;
}
