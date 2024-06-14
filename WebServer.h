#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

class WebServer {
    int id;
    bool busy;
public:
    WebServer(int id);
    int getId();
    void processRequest(Request &request);
    bool isBusy();
};

#endif 