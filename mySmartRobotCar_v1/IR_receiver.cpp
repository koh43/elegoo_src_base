#include "IR_receiver.h"

// public
IR_receiver::IR_receiver() {
    init_buttons_map();
}

IR_receiver::~IR_receiver() {
    // No dynamic resource cleanup required yet
}

bool IR_receiver::get_sensor_data(IRrecv& irrecv, decode_results& results, uint8_t* data) {
    if (irrecv.decode(&results)) {
        if (results.value == 0xFFFFFFFF) {
            results.value = prev_val_;
        }
        unsigned long res_val = results.value;
        auto it = buttons_map_.find(res_val);
        if (it != buttons_map_.end()) {
            *data = it->second;
        }
        else {
            *data = 0; // default value, just in case
            Serial.println("No mapping found for value.");
        }
        prev_val_ = res_val;
        irrecv.resume(); // Prepare for the next signal
        return true;
    }
    else {
        return false;
    }
}

// private
void IR_receiver::init_buttons_map() {
    buttons_map_ = {
        {RECV_0    ,  0},
        {RECV_1    ,  1},
        {RECV_2    ,  2},
        {RECV_3    ,  3},
        {RECV_4    ,  4},
        {RECV_5    ,  5},
        {RECV_6    ,  6},
        {RECV_7    ,  7},
        {RECV_8    ,  8},
        {RECV_9    ,  9},
        {RECV_star , 10},
        {RECV_sharp, 11},
        {RECV_up   , 12},
        {RECV_down , 13},
        {RECV_left , 14},
        {RECV_right, 15},
        {RECV_ok   , 16},
    };
}