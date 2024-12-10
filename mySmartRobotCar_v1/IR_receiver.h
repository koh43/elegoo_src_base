#ifndef IR_RECEIVER_H
#define IR_RECEIVER_H

// Please use IRremote versions 2.x.x or lower
#include <IRremote.h>
#include <ArduinoSTL.h>
#include <map>
#include "ConstConfig.h"

class IR_receiver {
public:
    // Constructor
    IR_receiver();

    // Destructor
    ~IR_receiver();

    // Get IR remote controller input
    bool get_sensor_data(IRrecv& irrecv, decode_results& results, uint8_t* data);

private:
    std::map<unsigned long, uint8_t> buttons_map_;
    void init_buttons_map();
    unsigned long prev_val_;
};

#endif // IR_RECEIVER_H