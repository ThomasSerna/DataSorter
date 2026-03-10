#include "crow_all.h"

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([]() {
        return "test 1";
    });

    app.port(8080).multithreaded().run();
}