#include "pid_controller.h"
#include "globals.h"

PIDController::PIDController() {
    this->reset();
}

/***
 * Assignment 3
 * 
 * Implement PID!
 ***/

void PIDController::reset() volatile {    
    /**
     * You'll have a lot to keep track of. Make sure to reset all 
     * those variables here.
     **/

    m_goalW = 0;
    m_goalX = 0;

    m_pwmW = 0;
    m_pwmX = 0;

    m_errorW = 0;
    m_errorX = 0;
    m_errorW_old = 0;
    m_errorX_old = 0;

    m_countsW = 0;
    m_countsX = 0;
}

void PIDController::update() volatile {
    /**
     * Update your PID controller. This is what should be called
     * every systick, so you should call all your important
     * functions here.
     **/
    getSensorFeedback();
    x_controller();
    w_controller();
    updateMotorPwm();
    
}

void PIDController::setXGoal(int counts) {
    /**
     * Set goal for X controller.
     **/
     m_goalX = counts;
}

void PIDController::setWGoal(int counts) {
    /**
     * Set goal for W controller. Make sure to associate a turning
     * direction with a sign, e.g., positive is clockwise, negative
     * is counter-clockwise.
     **/
     m_goalW = counts;
}

bool PIDController::isDone() volatile {
    /**
     * When is the PID done? Well, probably when you've reached
     * your goals...
     **/
     return false;
}

char* PIDController::getData() {
    /**
     * Use this function to print data about your PID,
     * because you can't print directly in systick!
     **/
    sprintf(buf, "goalx: %d\tgoalw: %d\tpwmx: %.3f\tpwmw: %.3f\terrorx: %d\terrorw: %d\n",
        m_goalX,
        m_goalW,
        m_pwmX,
        m_pwmW,
        m_errorX,
        m_errorW);
    return buf;
}

/**
 * Private functions to do the internal work for PID.
 **/
void PIDController::getSensorFeedback() volatile {
    /**
     * Update sensor values, from encoders
     **/
     m_countsW = encoders.getPulsesL() - encoders.getPulsesR();
}

void PIDController::x_controller() volatile {
    /**
     * Your X PID controller, sets m_pwmX
     **/
     //m_pwmX = m_goalX;
     m_pwmX = 0.15;
     //m_pwmX = 0;
}

void PIDController::w_controller() volatile {
    /**
     * Your W PID controller, sets m_pwmW
     **/
     
    m_errorW = m_goalW - m_countsW;
    m_pwmW = KpW * m_errorW + KdW * (m_errorW - m_errorW_old) * SYS_TICK_TIME;

    m_errorW_old = m_errorW;

    
    //m_pwmW = m_goalW;
}

void PIDController::updateMotorPwm() volatile {
    /**
     * Takes m_pwmX, m_pwmW, and adjusts the motors based on those values.
     **/
    /*
    m_pwmX = x_controller();
    m_pwmW = w_controller();
     
    if ( (m_pwmX + m_pwmW) < motors.MIN_SPEED && (m_pwmX - m_pwmW) < motors.MIN_SPEED ) {
       counter++;
    } 
    */
    motors.setRightPwm(m_pwmX + m_pwmW);
    motors.setLeftPwm(m_pwmX - m_pwmW);
}

