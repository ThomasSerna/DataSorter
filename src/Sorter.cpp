#include "../include/Sorter.h"

SortResponseDto Sorter::sort(const std::string filePath, const std::string algorithm) const {

    std::vector<std::string> unsortedData = extractFileData(filePath);

    if (algorithm == quickSortName) {
        return quickSort(filePath, unsortedData);
    } else if (algorithm == heapSortName) {
        return heapSort(filePath, unsortedData);
    } else if (algorithm == balancedTreeName) {
        return balancedTree(filePath, unsortedData);
    } else {
        SortResponseDto sort_response_dto;
        sort_response_dto.success        = false;
        sort_response_dto.message        = "Nombre de algoritmo incorrecto";
        sort_response_dto.algorithm      = algorithm;
        sort_response_dto.outputFilePath = filePath;
        sort_response_dto.durationMs     = 0;
        sort_response_dto.totalWords     = 0;

        return sort_response_dto;
    }
}

std::vector<std::string> Sorter::extractFileData(const std::string filePath) const {
    std::vector<std::string> data;

    // Falta sacar la información del archivo

    return data;
}

SortResponseDto Sorter::quickSort(const std::string filePath, std::vector<std::string> unsortedData) const {

    // Falta el codigo que ordene el archivo

    // Mensaje a enviar al frontend
    SortResponseDto sort_response_dto;
    sort_response_dto.success        = true;
    sort_response_dto.message        = "quickSort";
    sort_response_dto.algorithm      = quickSortName;
    sort_response_dto.outputFilePath = filePath;
    sort_response_dto.durationMs     = 0;
    sort_response_dto.totalWords     = unsortedData.size();

    return sort_response_dto;
}

SortResponseDto Sorter::heapSort(const std::string filePath, std::vector<std::string> unsortedData) const {

    // Falta el codigo que ordene el archivo

    // Mensaje a enviar al frontend
    SortResponseDto sort_response_dto;
    sort_response_dto.success        = true;
    sort_response_dto.message        = "heapSort";
    sort_response_dto.algorithm      = heapSortName;
    sort_response_dto.outputFilePath = filePath;
    sort_response_dto.durationMs     = 0;
    sort_response_dto.totalWords     = unsortedData.size();

    return sort_response_dto;
}

SortResponseDto Sorter::balancedTree(const std::string filePath, std::vector<std::string> unsortedData) const {

    // Falta el codigo que ordene el archivo

    // Mensaje a enviar al frontend
    SortResponseDto sort_response_dto;
    sort_response_dto.success        = true;
    sort_response_dto.message        = "balancedTree";
    sort_response_dto.algorithm      = balancedTreeName;
    sort_response_dto.outputFilePath = filePath;
    sort_response_dto.durationMs     = 0;
    sort_response_dto.totalWords     = unsortedData.size();

    return sort_response_dto;
}
