#include "assignment2.h"
#include "globals.h"


void read_encoders() {
    while (true) {
        encoders.printValues();
        wait(0.5);
    }
}

void basic_motor_movement() {
    // TODO: Move forwards
    motors.setRightPwm(0.15); 
    motors.setLeftPwm(0.15);

    wait(3);

    // TODO: Move backwards
    motors.setRightPwm(-0.15);
    motors.setLeftPwm(-0.15);
    
    wait(3);

    // TODO: Turn
    motors.setRightPwm(0.15);
    motors.setLeftPwm(-0.15);
    
    wait(3);
    
    motors.setRightPwm(-0.15);
    motors.setLeftPwm(0.15);
    
    wait(3);
    
    motors.stop();
}
