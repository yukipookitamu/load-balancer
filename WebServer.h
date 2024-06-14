#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

class WebServer {
    int id;
    bool busy = false;
public:
    WebServer(int id);
    int getId();
    void processRequest(Request &request);
    bool isFree();
};

#endif 