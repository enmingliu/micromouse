#pragma once

#include "mbed.h"

// 1ms systick time, probably don't change this :)
const float SYS_TICK_TIME = .001;

void systickFunction();

class Systick {
public:
    Systick();
     
    void start();
    void stop();
    
    void wait(float sec);    
private:
    Ticker m_systicker;
};
