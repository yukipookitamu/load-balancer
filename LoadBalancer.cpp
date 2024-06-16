// LoadBalancer.cpp
#include "LoadBalancer.h"
#include <algorithm>

LoadBalancer::LoadBalancer() : systemTime(0), roundRobinIndex(0) {}

void LoadBalancer::addServer(WebServer &server) {
    webServers.push_back(server);
}

void LoadBalancer::removeServer(int serverId) {
    webServers.erase(std::remove_if(webServers.begin(), webServers.end(),
                  [serverId](const WebServer &server) { return server.getId() == serverId; }), webServers.end());
}

void LoadBalancer::loadBalance() {
    // Distribute requests to webServers using round-robin
    while (!requestQueue.isEmpty()) {
        // Find the next available server
        for (std::vector<WebServer>::size_type i = 0; i < webServers.size(); ++i) {
            std::vector<WebServer>::size_type index = (this->roundRobinIndex + i) % webServers.size();
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

void LoadBalancer::simulate(int duration) {
    // Simulate for the given duration
    for (int i = 0; i < duration; ++i) {
        loadBalance();
        // Add new requests at random times
        if (rand() % 10 == 0) {
            std::string ipIn = "192.168." + std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);
            std::string ipOut = "10.0." + std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);
            Request request(rand(), ipIn, ipOut, i, rand() % 10 + 1);
            requestQueue.enqueue(request);
        }
        incrementTime();
    }
}
