#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
private:
    int id;
    std::string ipIn;
    std::string ipOut;

    int startTime;
    int endTime;

public:
    Request(
        int id,
        std::string ipIn,
        std::string ipOut,
        int startTime,
        int endTime
        );

    int getId();
    std::string getIpIn();
    std::string getIpOut();

    int getStartTime();
    int getEndTime();
    int getProcessingTime();
};

#endif