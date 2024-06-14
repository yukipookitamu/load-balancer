// LoadBalancer.cpp
#include "LoadBalancer.h"
#include <algorithm>

LoadBalancer::LoadBalancer() : systemTime(0) {}

void LoadBalancer::loadBalance() {
    // Distribute requests to webServers using round-robin
    while (!requestQueue.isEmpty()) {
        // Find the next available server
        for (int i = 0; i < webServers.size(); ++i) {
            int index = (this->roundRobinIndex + i) % webServers.size();
            if (webServers[index].isFree()) {
                Request request = requestQueue.dequeue();
                webServers[index].processRequest(request);
                this->roundRobinIndex = (index + 1) % webServers.size(); // Update for the next round
                break;
            }
        }
        // If no webServers are available, exit the loop
        break;
    }
}

RequestQueue& LoadBalancer::getRequestQueue() {
    return this->requestQueue;
}

int LoadBalancer::getSystemTime() {
    return this->systemTime;
}

void LoadBalancer::incrementTime() {
    this->systemTime++;
}
