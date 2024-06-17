/**
 * @file WebServer.cpp
 * @brief Implementation of the WebServer class.
 */

#include "WebServer.h"
#include "Request.h"
#include <fstream>

/**
 * @brief Constructs a WebServer with a given ID and condition variable.
 * @param id The ID of the web server.
 * @param cv A pointer to the condition variable for notifying the LoadBalancer.
 */
WebServer::WebServer(int id, std::condition_variable* cv) : id(id), busy(false), cv(cv) {}

/**
 * @brief Copy constructor for WebServer.
 * @param other The WebServer object to copy from.
 */
WebServer::WebServer(const WebServer& other) : id(other.id), busy(other.busy.load()), cv(other.cv) {}

/**
 * @brief Assignment operator for WebServer.
 * @param other The WebServer object to assign from.
 * @return A reference to this WebServer object.
 */
WebServer& WebServer::operator=(const WebServer& other) {
    if (this != &other) {
        id = other.id;
        busy.store(other.busy.load());
        cv = other.cv;
    }
    return *this;
}

/**
 * @brief Processes a request.
 * 
 * Logs the start and end of processing, simulates processing time, 
 * and notifies the LoadBalancer when processing is complete.
 * 
 * @param request The request to process.
 */
void WebServer::processRequest(Request &request) {
    this->busy = true;

    // Open a log file in append mode
    std::ofstream logfile("server.log", std::ios_base::app);
    if (!logfile.is_open()) {
        std::cerr << "Error opening log file." << std::endl;
        return;
    }

    // Log start of processing to the file
    logfile << "WebServer " << this->id << " is processing request " << request.getId()
              << " from " << request.getIpIn() << " to " << request.getIpOut() << std::endl;

    // Simulate processing time
    std::this_thread::sleep_for(std::chrono::milliseconds(request.getProcessingTime()));

    // Log end of processing to the file
    logfile << "WebServer " << this->id << " finished processing request " << request.getId() << " in " << request.getProcessingTime() << std::endl;

    this->busy = false;

    // Close the log file
    logfile.close();

    // Notify LoadBalancer that this server is free
    cv->notify_one();
}

/**
 * @brief Checks if the web server is free.
 * @return true If the web server is not busy.
 * @return false If the web server is busy.
 */
bool WebServer::isFree() const {
    return !busy;
}

/**
 * @brief Gets the ID of the web server.
 * @return The ID of the web server.
 */
int WebServer::getId() const {
    return this->id;
}
