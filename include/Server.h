//
// Created by User on 10/03/2026.
//

#ifndef DATASORTER_SERVER_H
#define DATASORTER_SERVER_H

#include "crow_all.h"
#include "dto/SortResultDto.h"
#include "Sorter.h"

#include <filesystem>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <chrono>

class Server {
public:
    void run(int port = 8080);

private:
    crow::SimpleApp app;
    void setUpRoutes();
};

#endif //DATASORTER_SERVER_H