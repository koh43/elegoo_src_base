#ifndef IR_RECEIVER_H
#define IR_RECEIVER_H

// Please use IRremote versions 2.x.x or lower
#include <IRremote.h>
#include <ArduinoSTL.h>
#include <map>
#include "ConstConfig.h"

class IR_receiver {
public:
    IR_receiver(IRrecv& irrecv, decode_results& dr);
    ~IR_receiver();
    void Init();
    // Get IR remote controller input
    bool CtrlrInput(char* data);

private:
    IRrecv* irrecv_;
    decode_results* dr_;
    std::map<unsigned long, char> buttons_map_;
    void init_buttons_map();
    unsigned long prev_val_;
};

#endif // IR_RECEIVER_H