#ifndef IR_RECEIVER_H
#define IR_RECEIVER_H

// Please use IRremote versions 2.x.x or lower
#include <IRremote.h>
#include <ArduinoSTL.h>
#include <map>

// IR remote controller
constexpr uint8_t IR_RECEIVER_PIN = 9;

// Choose your remote controller type
#define IR_RM_CTRL_A
// #define IR_RM_CTRL_B

#ifdef IR_RM_CTRL_A
constexpr unsigned long RECV_up    = 16736925;
constexpr unsigned long RECV_down  = 16754775;
constexpr unsigned long RECV_left  = 16720605;
constexpr unsigned long RECV_right = 16761405;
constexpr unsigned long RECV_ok    = 16712445;
constexpr unsigned long RECV_1     = 16738455;
constexpr unsigned long RECV_2     = 16750695;
constexpr unsigned long RECV_3     = 16756815;
constexpr unsigned long RECV_4     = 16724175;
constexpr unsigned long RECV_5     = 16718055;
constexpr unsigned long RECV_6     = 16743045;
constexpr unsigned long RECV_7     = 16716015;
constexpr unsigned long RECV_8     = 16726215;
constexpr unsigned long RECV_9     = 16734885;
constexpr unsigned long RECV_0     = 16730805;
constexpr unsigned long RECV_star  = 16728765;
constexpr unsigned long RECV_sharp = 16732845;
#endif

#ifdef IR_RM_CTRL_B
constexpr unsigned long RECV_up    = 5316027   ;
constexpr unsigned long RECV_down  = 2747854299;
constexpr unsigned long RECV_left  = 1386468383;
constexpr unsigned long RECV_right = 553536955 ;
constexpr unsigned long RECV_ok    = 3622325019;
constexpr unsigned long RECV_1     = 3238126971;
constexpr unsigned long RECV_2     = 2538093563;
constexpr unsigned long RECV_3     = 4039382595;
constexpr unsigned long RECV_4     = 2534850111;
constexpr unsigned long RECV_5     = 1033561079;
constexpr unsigned long RECV_6     = 1635910171;
constexpr unsigned long RECV_7     = 2351064443;
constexpr unsigned long RECV_8     = 1217346747;
constexpr unsigned long RECV_9     = 71952287  ;
#endif

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