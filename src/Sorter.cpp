#include "../include/Sorter.h"

SortResponseDto Sorter::sort(const std::string filePath, const std::string algorithm) {
    SortResponseDto sort_response_dto;
    sort_response_dto.success        = false;
    sort_response_dto.message        = "prueba";
    sort_response_dto.algorithm      = algorithm;
    sort_response_dto.outputFilePath = filePath;
    sort_response_dto.durationMs     = 0.0;
    sort_response_dto.totalWords     = 0;

    return sort_response_dto;
}
