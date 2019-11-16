/*
 * myFortune
 * A "Fortune" server written in pure c++
 * (c) 2019 by Felice Murolo, all rigths reserved
 * Licensed under LGPL V 3.0
 * Location: Salerno, Italia
 * email: linuxboy@giove.tk
 */

#include "application.h"
#include "quotes.h"

void sighandler(int);
[[ noreturn ]] void ctrl_c_handler(int s);

Application *my = nullptr;

Application::Application(uint16_t port)
{
    PORT = port;
    my = this;

}

int Application::start()
{
    int r=0;
    int opt = 1;
    struct sockaddr_in address;
    static int new_socket;


    // redirect CTRL-C
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = ctrl_c_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, nullptr);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd==0) {
        cout << "Error socket" << endl;
        return(EXIT_FAILURE);
    }
    r = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if (r!=0) {
        cout << "Error " << r << " setsockopt" << endl;
        return(r);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    uint addrlen = sizeof(address);
    r = bind(sockfd, reinterpret_cast<struct sockaddr *>(&address), addrlen);
    if (r<0) {
        cout << "Error " << r << " bind" << endl;
        return(EXIT_FAILURE);
    }

    r = listen(sockfd, 3);
    if (r<0) {
        cout << "Error " << r << " listen" << endl;
        return(EXIT_FAILURE);
    }

    cout << "Server myFortune ready on port " << PORT << endl;

    r = 0;

    timer1 = new Timer();
    timer1->setInterval(1000);
    signal(SIG_INTERVAL,sighandler);

    while(true) {
        new_socket = accept(sockfd, reinterpret_cast<struct sockaddr *>(&address),static_cast<socklen_t*>(&addrlen));
        if (new_socket<0) {
            cout << "Error accept" << endl;
            r = EXIT_FAILURE;
            break;
        }
        list<quote>::iterator it = quotes.begin();
        advance(it,current);
        send(new_socket, it->value, strlen(it->value),0);
        send(new_socket, "\r\n",2,0);
        send(new_socket, it->author, strlen(it->author),0);
        send(new_socket, "\r\n",2,0);
        close(new_socket);
    }

    return(r);
}

void Application::timeout()
{
    current++;
    if (current >= quotes.size()) current = 0;
}

// THESE ARE NOT APPLICATION CLASS FUNCTION
// NEED THOSE FOR signal() - CLASS FUNCTION CONTAINS 'this' OBJECT AS HIDDEN FIRST PARAMETER, SO signal() WON'T WORKS
void sighandler(int sig){
    (void) sig;
    my->timeout();
}

[[ noreturn ]] void ctrl_c_handler(int s) {
    (void) s;
    cout << endl << "Press Enter To Exit..." << endl;
    getchar();
    exit(0);
}
