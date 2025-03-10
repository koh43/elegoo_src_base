#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include <Arduino.h>

constexpr size_t DATA_BUFFER_SIZE = 256;

class SerialHandler {
public:
    void receiveData(HardwareSerial& serial);
    const uint8_t* getLastData() const;
    size_t getLastDataSize() const;

private:
    uint8_t lastData_[DATA_BUFFER_SIZE];
    size_t lastDataSize_;
};
    
#endif // SERIAL_HANDLER_H


// class SerialHandler {
// public:
//     void receiveData(HardwareSerial& serial);
//     String getLastData();

// private:
//     String lastData_;
// };

// #endif // SERIAL_HANDLER_H