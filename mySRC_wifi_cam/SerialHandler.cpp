#include "SerialHandler.h"

void SerialHandler::receiveData(HardwareSerial& serial) {
    lastDataSize_ = serial.readBytesUntil('\n', lastData_, DATA_BUFFER_SIZE - 1);
    lastData_[lastDataSize_] = '\0';
    // size_t index = 0;
    // while (serial.available() > 0 && index < DATA_BUFFER_SIZE) {
    //     char c = serial.read();
    //     if (c == '\n') { // End of input
    //         lastDataSize_ = index;
    //         break;
    //     } else {
    //         lastData_[index++] = static_cast<uint8_t>(c);
    //     }
    // }
}

const char* SerialHandler::getLastData() const {
    return lastData_;
}

size_t SerialHandler::getLastDataSize() const {
    return lastDataSize_;
}
