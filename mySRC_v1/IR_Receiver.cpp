#include "IR_Receiver.h"

// public
IR_receiver::IR_receiver(IRrecv& irrecv, decode_results& dr)
: irrecv_(&irrecv), dr_(&dr) {
    init_buttons_map();
}

IR_receiver::~IR_receiver() {
    // No dynamic resource cleanup required yet
}

void IR_receiver::Init() {
    irrecv_->enableIRIn();
}

bool IR_receiver::CtrlrInput(char* data) {
    if (irrecv_->decode(dr_)) {
        // if (dr.value == 0xFFFFFFFF) {
        //     dr.value = prev_val_;
        // }
        unsigned long res_val = dr_->value;
        Serial.print("Raw Value: ");
        Serial.println(dr_->value);
        auto it = buttons_map_.find(res_val);
        if (it != buttons_map_.end()) {
            *data = it->second;
        }
        else {
            *data = '-'; // default value, just in case
            // Serial.println("No mapping found for value.");
        }
        prev_val_ = res_val;
        irrecv_->resume(); // Prepare for the next signal
        return true;
    }
    else {
        return false;
    }
}

// private
void IR_receiver::init_buttons_map() {
#ifdef USE_IR_RM_CTRL
    buttons_map_ = {
        {RECV_0    , '0'},
        {RECV_1    , '1'},
        {RECV_2    , '2'},
        {RECV_3    , '3'},
        {RECV_4    , '4'},
        {RECV_5    , '5'},
        {RECV_6    , '6'},
        {RECV_7    , '7'},
        {RECV_8    , '8'},
        {RECV_9    , '9'},
        {RECV_star , '*'},
        {RECV_sharp, '#'},
        {RECV_up   , 'U'},
        {RECV_down , 'D'},
        {RECV_left , 'L'},
        {RECV_right, 'R'},
        {RECV_ok   , 'K'},
    };
#endif
}