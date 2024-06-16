#include "WebServer.h"
#include <thread>
#include <chrono>
#include <iostream>

WebServer::WebServer(int id) : id(id) {};

WebServer::WebServer(const WebServer& other) : id(other.id), busy(other.busy.load()) {}

WebServer& WebServer::operator=(const WebServer& other) {
    if (this != &other) {
        id = other.id;
        busy.store(other.busy.load());
    }
    return *this;
}

void WebServer::processRequest(Request &request) {
    this->busy = true;
    
    // Log start of processing
    std::cout << "WebServer " << this->id << " is processing request " << request.getId()
              << " from " << request.getIpIn() << " to " << request.getIpOut() << std::endl;
    
    // Simulate processing time
    std::this_thread::sleep_for(std::chrono::milliseconds(request.getProcessingTime()));

    // Log end of processing
    std::cout << "WebServer " << this->id << " finished processing request " << request.getId() << std::endl;

    this->busy = false;
}

bool WebServer::isFree() {
    return !this->busy;
}

int WebServer::getId() const {
    return this->id;
}