/**
 * @file Request.cpp
 * @brief Implementation of the Request class.
 */

#include "Request.h"

/**
 * @brief Constructs a Request with the given parameters.
 * 
 * @param id The ID of the request.
 * @param ipIn The incoming IP address.
 * @param ipOut The outgoing IP address.
 * @param startTime The start time of the request.
 * @param endTime The end time of the request.
 */
Request::Request(int id, std::string ipIn, std::string ipOut, int startTime, int endTime)
    : id(id), ipIn(ipIn), ipOut(ipOut), startTime(startTime), endTime(endTime) {}

/**
 * @brief Gets the ID of the request.
 * @return int The ID of the request.
 */
int Request::getId() {
    return this->id;
}

/**
 * @brief Gets the incoming IP address of the request.
 * @return std::string The incoming IP address.
 */
std::string Request::getIpIn() {
    return this->ipIn;
}

/**
 * @brief Gets the outgoing IP address of the request.
 * @return std::string The outgoing IP address.
 */
std::string Request::getIpOut() {
    return this->ipOut;
}

/**
 * @brief Gets the start time of the request.
 * @return int The start time of the request.
 */
int Request::getStartTime() {
    return this->startTime;
}

/**
 * @brief Gets the end time of the request.
 * @return int The end time of the request.
 */
int Request::getEndTime() {
    return this->endTime;
}

/**
 * @brief Gets the processing time of the request.
 * 
 * The processing time is calculated as the difference between the end time and the start time.
 * 
 * @return int The processing time of the request.
 */
int Request::getProcessingTime() {
    return this->endTime - this->startTime;
}
