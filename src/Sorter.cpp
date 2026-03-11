#include "../include/Sorter.h"

SortResponseDto Sorter::sort(const std::string filePath, const std::string algorithm) {
    SortResponseDto sort_response_dto;
    sort_response_dto.success        = true;
    sort_response_dto.message        = "test";
    sort_response_dto.algorithm      = algorithm;
    sort_response_dto.outputFilePath = filePath;
    sort_response_dto.durationMs     = 69.0;
    sort_response_dto.totalWords     = 10000;

    return sort_response_dto;
}
