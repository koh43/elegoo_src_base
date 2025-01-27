#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include <Arduino.h>

class SerialHandler {
public:
    void receiveData(HardwareSerial& serial);
    String getLastData();

private:
    String lastData_;
};

#endif // SERIAL_HANDLER_H