#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "WebServer.h"
#include "Request.h"
#include "RequestQueue.h"
#include "LoadBalancer.h"

int main(int argc, char* argv[]) {
    int numServers = 0;
    int runDuration = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-s" && i + 1 < argc) {
            numServers = std::stoi(argv[++i]);
        } else if (arg == "-d" && i + 1 < argc) {
            runDuration = std::stoi(argv[++i]);
        } else {
            std::cout << "Usage: ./loadbalancer -s <number_of_servers> -d <run_duration>" << std::endl;
            return 1;
        }
    }
   
    // Seed random number generator
    std::srand(std::time(0));

    // Initialize load balancer
    LoadBalancer loadBalancer;
    for (int i = 0; i < numServers; ++i) {
        WebServer server(i);
        loadBalancer.addServer(server);
    }

    // Generate initial request queue
    for (int i = 0; i < numServers * 100; ++i) {
        std::string ipIn = "192.168." + std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);
        std::string ipOut = "10.0." + std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);
        Request request(i, ipIn, ipOut, 0, std::rand() % 10 + 1);
        loadBalancer.getRequestQueue().enqueue(request);
    }

    // Run the load balancer
    loadBalancer.simulate(runDuration);

    return 0;
}