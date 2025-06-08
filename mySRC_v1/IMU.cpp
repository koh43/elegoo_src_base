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
    Serial.println("Calibrating offsets...");
    PullBracketsOut();
    PullBracketsIn();
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
    mpu_->setXAccelOffset(offsets[iAx]); //Set your accelerometer offset for axis X
    mpu_->setYAccelOffset(offsets[iAy]); //Set your accelerometer offset for axis Y
    mpu_->setZAccelOffset(offsets[iAz]); //Set your accelerometer offset for axis Z
    mpu_->setXGyroOffset(offsets[iGx]);  //Set your gyro offset for axis X
    mpu_->setYGyroOffset(offsets[iGy]);  //Set your gyro offset for axis Y
    mpu_->setZGyroOffset(offsets[iGz]);  //Set your gyro offset for axis Z
}

void IMU::getOffsets(std::array<int16_t, 6>& offsets) {
    offsets[iAx] = mpu_->getXAccelOffset();
    offsets[iAy] = mpu_->getYAccelOffset();
    offsets[iAz] = mpu_->getZAccelOffset();
    offsets[iGx] = mpu_->getXGyroOffset();
    offsets[iGy] = mpu_->getYGyroOffset();
    offsets[iGz] = mpu_->getZGyroOffset();
}

void IMU::ShowProgress() {
    if (linesOut_ >= linesBetweenHeaders_) {
        Serial.println("\tXAccel\t\tYAccel\t\tZAccel\t\tXGyro\t\tYGyro\t\tZGyro");
        linesOut_ = 0;
    }
    Serial.print(' ');
    for (int i = iAx; i <= iGz; i++) {
        Serial.print('[');
        Serial.print(lowOffset_[i]);
        Serial.print(',');
        Serial.print(highOffset_[i]);
        Serial.print("] ");
        if (i == iGz)
            Serial.println();
    }
    linesOut_++;
}

void IMU::GetSmoothed(int N, std::array<int16_t, 6>& smoothed) {
    std::array<int32_t, 6> sums = {0, 0, 0, 0, 0, 0};
    int16_t raw[6];
    for (auto i = 0; i < N; i++) {
        mpu_->getMotion6(
            &raw[iAx],
            &raw[iAy],
            &raw[iAz],
            &raw[iGx],
            &raw[iGy],
            &raw[iGz]
        );
        delayMicroseconds(usDelay);
        for (auto j = iAx; j <= iGz; j++) {
            sums[j] += raw[j];
        } // get sums
    }
    for (auto j = iAx; j <= iGz; j++) {
        smoothed[j] = (sums[j] + N/2) / N;
    }
} // GetSmoothed

void IMU::PullBracketsOut() {
    std::array<int16_t, 6> smoothed;
    bool done = false;
    uint16_t N = NFast;

    while (!done) {
        done = true;
        // get low values
        setOffsets(lowOffset_);
        GetSmoothed(N, smoothed);
        for (uint8_t i = iAx; i <= iGz; i++) {
            if (smoothed[i] >= target[i]) {
                done = false;
                lowOffset_[i] -= 1000;
            }
        }
        // get high values
        setOffsets(highOffset_);
        GetSmoothed(N, smoothed);
        for (uint8_t i = iAx; i <= iGz; i++) {
            if (smoothed[i] <= target[i]) {
                done = false;
                highOffset_[i] += 1000;
            }
        }
        ShowProgress();
    }
} // PullBracketsOut

void IMU::PullBracketsIn() {
    bool AllBracketsNarrow = false, stillWorking = true;
    std::array<int16_t, 6> smoothed;
    std::array<int16_t, 6> newOffset;
    uint16_t N = NFast;
    while (stillWorking) {
        stillWorking = false;
        if (AllBracketsNarrow && (N == NFast)) {
            N = NSlow;
        }
        else {
            AllBracketsNarrow = true; // tentative
        }
        for (uint8_t i = iAx; i <= iGz; i++) {
            if (highOffset_[i] <= (lowOffset_[i] + 1)) {
                newOffset[i] = lowOffset_[i];
            }
            else { // binary search
                stillWorking = true;
                newOffset[i] = (lowOffset_[i] + highOffset_[i]) / 2;
                if (highOffset_[i] > (lowOffset_[i] + 10)) {
                    AllBracketsNarrow = false;
                }
            }
        }
        setOffsets(newOffset);
        GetSmoothed(N, smoothed);
        // closing in
        for (uint8_t i = iAx; i <= iGz; i++) {
            // use lower half
            if (smoothed[i] > target[i]) {
                highOffset_[i] = newOffset[i];
            }
            // use upper half
            else {
                lowOffset_[i] = newOffset[i];
            }
        }
        ShowProgress();
    } // still working
    Serial.println("Applying offsets...");
    setOffsets(newOffset);
} // PullBracketsIn


