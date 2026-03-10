#include "../include/Server.h"

void Server::run(int port) {
    setUpRoutes();
    app.port(port).multithreaded().run();
}

void Server::setUpRoutes() {

    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
    });


}
