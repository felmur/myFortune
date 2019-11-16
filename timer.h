/*
 * myFortune
 * A "Fortune" server written in pure c++
 * (c) 2019 by Felice Murolo, all rigths reserved
 * Licensed under LGPL V 3.0
 * Location: Salerno, Italia
 * email: linuxboy@giove.tk
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include <iostream>
#include <thread>
#include <csignal>

#define SIG_TIMEOUT 40
#define SIG_INTERVAL 41

using namespace std;


class Timer {

public:
    Timer();
    void setTimeout(int delay);
    void setInterval(int interval);

    void stop();
    bool clear = false;
};


#endif // TIMER_H
