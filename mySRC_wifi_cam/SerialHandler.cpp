#include "SerialHandler.h"

void SerialHandler::receiveData(HardwareSerial& serial) {
    lastDataSize_ = serial.readBytesUntil('\n', lastData_, DATA_BUFFER_SIZE - 1);
    lastData_[lastDataSize_] = '\0';
}

const char* SerialHandler::getLastData() const {
    return lastData_;
}

size_t SerialHandler::getLastDataSize() const {
    return lastDataSize_;
}
