#include "Request.h"

Request::Request(int id, std::string ipIn, std::string ipOut, int startTime, int endTime)
    : id(id), ipIn(ipIn), ipOut(ipOut), startTime(startTime), endTime(endTime) {}

int Request::getId() {
    return this->id;
}

std::string Request::getIpIn() {
    return this->ipIn;
}

std::string Request::getIpOut() {
    return this->ipOut;
}

int Request::getStartTime() {
    return this->startTime;
}

int Request::getEndTime() {
    return this->endTime;
}

int Request::getProcessingTime() {
    return this->endTime - this->startTime;
}