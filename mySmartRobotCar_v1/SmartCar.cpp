#include "SmartCar.h"

// Constructor
SmartCar::SmartCar() {

}

// Destructor
SmartCar::~SmartCar() {
    
}

// Initialization
void SmartCar::SmartCarInit() {
    us_.initialize();
}

// Sensor Setting Functions
float SmartCar::get_us_dist() {
    return us_.get_sensor_data();
}