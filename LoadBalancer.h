#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include "WebServer.h"
#include "RequestQueue.h"

// will implement round robin
class LoadBalancer {
private:
    RequestQueue requestQueue;
    std::vector<WebServer> webServers;
    int systemTime;
    int roundRobinIndex;
public:
    LoadBalancer();
    void incrementTime();
    int getSystemTime();
    RequestQueue& getRequestQueue();
    void loadBalance();
};

#endif