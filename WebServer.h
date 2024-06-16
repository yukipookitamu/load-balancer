#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
#include <atomic>

class WebServer {
    int id;
    std::atomic<bool> busy {false};
public:
    WebServer(int id);
    WebServer(const WebServer& other); // Copy constructor
    WebServer& operator=(const WebServer& other); // Copy assignment operator

    int getId() const;
    void processRequest(Request &request);
    bool isFree();
};

#endif 