#include <vector>
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include "WebServer.h"
#include "RequestQueue.h"

class LoadBalancer {
private:
    std::vector<WebServer> webServers;
    RequestQueue requestQueue;
    int systemTime;
    size_t roundRobinIndex;
    std::unordered_set<std::string> blockedIPRanges; /**< Set of blocked IP ranges */
    std::mutex mtx; /**< Mutex for synchronizing access to webServers */
    std::condition_variable cv; /**< Condition variable to wait for available web servers */

public:
    LoadBalancer();
    void addServer(WebServer &server);
    void removeServer(int serverId);
    void loadBalance();
    RequestQueue& getRequestQueue();
    int getSystemTime();
    void incrementTime();
    void simulate(int duration);
    void blockIPRange(const std::string& ipRange); /**< Blocks a specific IP range */
    void unblockIPRange(const std::string& ipRange); /**< Unblocks a specific IP range */
    std::condition_variable& getCv() {return cv; }
    bool isIPBlocked(const std::string& ip); /**< Checks if the given IP is blocked */
};
