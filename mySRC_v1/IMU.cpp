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
    /* Use the code below to change accel/gyro offset values. Use MPU6050_Zero to obtain the recommended offsets */ 
    Serial.println("Updating internal sensor offsets...\n");
    setOffsets({0,0,0,0,0,0});
}

void IMU::Update() {
    mpu_->getMotion6(
        &accel_.x, &accel_.y, &accel_.z,
        &gyro_.x, &gyro_.y, &gyro_.z
    );
    Serial.print("a/g:\t");
    Serial.print(accel_.x); Serial.print("\t");
    Serial.print(accel_.y); Serial.print("\t");
    Serial.print(accel_.z); Serial.print("\t");
    Serial.print(gyro_.x); Serial.print("\t");
    Serial.print(gyro_.y); Serial.print("\t");
    Serial.println(gyro_.z);
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
