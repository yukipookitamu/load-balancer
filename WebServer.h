#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <condition_variable>
#include <atomic>

class WebServer {
private:
    int id;
    std::atomic<bool> busy;
    std::condition_variable* cv;  /**< Condition variable to notify the LoadBalancer */

public:
    WebServer(int id, std::condition_variable* cv);
    WebServer(const WebServer& other);
    WebServer& operator=(const WebServer& other);
    void processRequest(Request &request);
    bool isFree() const;
    int getId() const;
};


#endif 