#include "RequestQueue.h"

void RequestQueue::enqueue(Request &request) {
    queue.push(request);
}

Request RequestQueue::dequeue() {
    if (queue.empty()) {
        return Request(-1);
    }

    Request request = queue.front();
    queue.pop();
    return request;
}

bool RequestQueue::isEmpty() {
    return queue.empty();
}