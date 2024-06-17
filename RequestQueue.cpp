/**
 * @file RequestQueue.cpp
 * @brief Implementation of the RequestQueue class.
 */

#include "RequestQueue.h"

/**
 * @brief Enqueues a request into the request queue.
 * @param request The request to enqueue.
 */
void RequestQueue::enqueue(Request &request) {
    queue.push(request);
}

/**
 * @brief Dequeues a request from the request queue.
 * 
 * If the queue is empty, returns an invalid request with ID -1.
 * 
 * @return Request The dequeued request.
 */
Request RequestQueue::dequeue() {
    if (queue.empty()) {
        return Request(-1, "", "", -1, -1); // invalid request
    }

    Request request = queue.front();
    queue.pop();
    return request;
}

/**
 * @brief Checks if the request queue is empty.
 * @return true If the queue is empty.
 * @return false If the queue is not empty.
 */
bool RequestQueue::isEmpty() {
    return queue.empty();
}
