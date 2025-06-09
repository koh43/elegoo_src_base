#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include <Arduino.h>

constexpr size_t DATA_BUFFER_SIZE = 96;

class SerialHandler {
public:
    void receiveData(HardwareSerial& serial);
    const char* getLastData() const;
    size_t getLastDataSize() const;

private:
    char lastData_[DATA_BUFFER_SIZE];
    size_t lastDataSize_;
};
    
#endif // SERIAL_HANDLER_H
