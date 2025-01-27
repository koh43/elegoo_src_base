#include "SerialHandler.h"

void SerialHandler::receiveData(HardwareSerial& serial) {
    static String serialBuffer = "";
    while (serial.available() > 0) {
        char c = serial.read();
        if (c == '\n') { // End of input
            lastData_ = serialBuffer;
            serialBuffer = ""; // Clear the buffer
        } else {
            serialBuffer += c; // Accumulate characters
        }
    }
}

String SerialHandler::getLastData() {
    return lastData_;
}