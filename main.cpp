/*
 * myFortune
 * A "Fortune" server written in pure c++
 * (c) 2019 by Felice Murolo, all rigths reserved
 * Licensed under LGPL V 3.0
 * Location: Salerno, Italia
 * email: linuxboy@giove.tk
 */

#include <iostream>
#include "application.h"
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
    int ret = 0;
    uint16_t port = 60060;

    if (argc>1){
        if (strcmp(argv[1],"-h")==0) {
            cout << "MyFortune v 1.0a" << endl;
            cout << "(c) 2019 by Felice Murolo, Salerno, Italia." << endl;
            cout << "Licensed under LGPL V 3.0" << endl;
            cout << "email: linuxboy@giove.tk" << endl << endl;
            cout << "Usage: myFortune [port]" << endl << endl;
            return 0;
        }
        if (atoi(argv[1]) > 1024) port = static_cast<uint16_t>(atoi(argv[1]));
    }

    cout << "Starting..." << endl;
    Application *app = new Application(port);
    ret = app->start();
    cout << "Exiting..." << endl;
    return ret;
}
