#include "WebServer.h"

WebServer::WebServer(int id) : id(id) {};

void WebServer::processRequest(Request &request) {
    this->busy = true;

    // TODO: Figure out processing time

    this->busy = false;
}

bool WebServer::isFree() {
    return !this->busy;
}

int WebServer::getId() {
    return this->id;
}