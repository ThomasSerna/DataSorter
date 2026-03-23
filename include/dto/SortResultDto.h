#ifndef DATASORTER_SORTRESULTDTO_H
#define DATASORTER_SORTRESULTDTO_H

#include <string>
#include "crow_all.h"

struct SortResponseDto {
    bool success;
    std::string message;
    std::string algorithm;
    std::string outputFilePath;
    double durationMs;
    int totalWords;
    std::size_t memoryBytes;

    crow::json::wvalue toJson() {
        crow::json::wvalue json;
        json["success"]        = success;
        json["message"]        = message;
        json["algorithm"]      = algorithm;
        json["outputFilePath"] = outputFilePath;
        json["durationMs"]     = durationMs;
        json["totalWords"]     = totalWords;
        json["memoryBytes"]    = memoryBytes;
        return json;
    }
};

#endif //DATASORTER_SORTRESULTDTO_H