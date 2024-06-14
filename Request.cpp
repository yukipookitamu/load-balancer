#include "Request.h"

Request::Request(int id, std::string ipIn, std::string ipOut, int startTime, int endTime)
    : id(id), ipIn(ipIn), ipOut(ipOut), startTime(startTime), endTime(endTime) {}

int Request::getId() {
    return id;
}

std::string Request::getIpIn() {
    return ipIn;
}

std::string Request::getIpOut() {
    return ipOut;
}

int Request::getStartTime() {
    return startTime;
}

int Request::getEndTime() {
    return endTime;
}