#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <queue>
#include "Request.h"

class RequestQueue {
private:
    std::queue<Request> queue;
public:
    void enqueue(Request &request);
    Request dequeue();
    bool isEmpty();
};

#endif