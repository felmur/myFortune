#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <thread>
#include "csignal"
/*
 * myFortune
 * A "Fortune" server written in pure c++
 * (c) 2019 by Felice Murolo, all rigths reserved
 * Licensed under LGPL V 3.0
 * Location: Salerno, Italia
 * email: linuxboy@giove.tk
 */

#include "timer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <list>
#include <iterator>

using namespace std;

class Application
{
public:
    Application(uint16_t port=60060); // default port is 60060
    int start();
    void timeout();

private:
    uint16_t PORT;
    size_t current = 0;
    Timer *timer1 = nullptr;
};

extern Application *my;

#endif // APPLICATION_H
