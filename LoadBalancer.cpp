#include "LoadBalancer.h"
#include <algorithm>

/**
 * @brief Constructs a LoadBalancer with initial system time and round-robin index set to 0.
 */
LoadBalancer::LoadBalancer() : systemTime(0), roundRobinIndex(0) {}

/**
 * @brief Adds a web server to the load balancer.
 * @param server The web server to add.
 */
void LoadBalancer::addServer(WebServer &server) {
    std::unique_lock<std::mutex> lock(mtx);
    webServers.push_back(server);
}

/**
 * @brief Removes a web server from the load balancer by its ID.
 * @param serverId The ID of the web server to remove.
 */
void LoadBalancer::removeServer(int serverId) {
    std::unique_lock<std::mutex> lock(mtx);
    webServers.erase(std::remove_if(webServers.begin(), webServers.end(),
                  [serverId](const WebServer &server) { return server.getId() == serverId; }), webServers.end());
}

/**
 * @brief Distributes requests to web servers using a round-robin algorithm.
 */
void LoadBalancer::loadBalance() {
    std::unique_lock<std::mutex> lock(mtx);
    // Distribute requests to web servers using round-robin
    while (!requestQueue.isEmpty()) {
        // Wait until a server becomes free
        cv.wait(lock, [this] {
            for (const auto& server : webServers) {
                if (server.isFree()) {
                    return true;
                }
            }
            return false;
        });

        // Find the next available server
        std::vector<WebServer>::size_type index = roundRobinIndex;
        for (std::vector<WebServer>::size_type i = 0; i < webServers.size(); ++i) {
            if (webServers[index].isFree()) {
                Request request = requestQueue.dequeue();
                // Check if the request IP is blocked
                if (!isIPBlocked(request.getIpIn())) {
                    webServers[index].processRequest(request);
                }
                break;
            }
            index = (index + 1) % webServers.size(); // Move to the next server
        }
        roundRobinIndex = (index + 1) % webServers.size(); // Update for the next round
    }
}


/**
 * @brief Gets the request queue of the load balancer.
 * @return RequestQueue& A reference to the request queue.
 */
RequestQueue& LoadBalancer::getRequestQueue() {
    return this->requestQueue;
}

/**
 * @brief Gets the current system time of the load balancer.
 * @return int The current system time.
 */
int LoadBalancer::getSystemTime() {
    return this->systemTime;
}

/**
 * @brief Increments the system time by one unit.
 */
void LoadBalancer::incrementTime() {
    this->systemTime++;
}

/**
 * @brief Simulates the load balancer operation for a given duration.
 * 
 * The simulation distributes requests to web servers and generates new requests at random times.
 * 
 * @param duration The duration to run the simulation.
 */
void LoadBalancer::simulate(int duration) {
    // Simulate for the given duration
    for (int i = 0; i < duration; ++i) {
        loadBalance();
        // Add new requests at random times
        if (rand() % 10 == 0) {
            std::string ipIn = "192.168." + std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);
            std::string ipOut = "10.0." + std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);
            Request request(rand(), ipIn, ipOut, i, rand() % 10 + 1);
            // Only enqueue request if IP is not blocked
            if (!isIPBlocked(ipIn)) {
                requestQueue.enqueue(request);
            }
        }
        incrementTime();
    }
}

/**
 * @brief Blocks a specific IP range.
 * @param ipRange The IP range to block.
 */
void LoadBalancer::blockIPRange(const std::string& ipRange) {
    blockedIPRanges.insert(ipRange);
}

/**
 * @brief Unblocks a specific IP range.
 * @param ipRange The IP range to unblock.
 */
void LoadBalancer::unblockIPRange(const std::string& ipRange) {
    blockedIPRanges.erase(ipRange);
}

/**
 * @brief Checks if the given IP is blocked.
 * @param ip The IP to check.
 * @return true If the IP is blocked.
 * @return false If the IP is not blocked.
 */
bool LoadBalancer::isIPBlocked(const std::string& ip) {
    return blockedIPRanges.find(ip) != blockedIPRanges.end();
}
