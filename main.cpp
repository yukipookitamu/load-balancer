#include <iostream>
#include <vector>
#include <string>
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
    return 0;
}