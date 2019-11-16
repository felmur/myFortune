#include "timer.h"

/*
 * myFortune
 * A "Fortune" server written in pure c++
 * (c) 2019 by Felice Murolo, all rigths reserved
 * Licensed under LGPL V 3.0
 * Location: Salerno, Italia
 * email: linuxboy@giove.tk
 */


Timer::Timer(){

}

void Timer::setTimeout(int delay) {
    this->clear = false;
    std::thread t([=]() {
        if(this->clear) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if(this->clear) return;
        raise(SIG_TIMEOUT);
    });
    t.detach();
}

void Timer::setInterval(int interval) {
    this->clear = false;
    std::thread t([=]() {
        while(true) {
            if(this->clear) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if(this->clear) return;
            raise(SIG_INTERVAL);
        }
    });
    t.detach();
}

void Timer::stop() {
    this->clear = true;
}

