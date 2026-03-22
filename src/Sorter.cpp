#include "../include/Sorter.h"

#include "Avl.h"

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
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo: " << filePath << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Eliminar caracteres nulos
        line.erase(std::remove(line.begin(), line.end(), '\0'), line.end());

        // Limpiar caracteres de residuo iniciales
        if (line.size() >= 2 &&
            (unsigned char)line[0] == 0xFF &&
            (unsigned char)line[1] == 0xFE) {
            line.erase(0, 2);
            }

        // Limpiar espacios al inicio
        size_t start = line.find_first_not_of(" \t\r\n");
        line.erase(0, start);

        // Limpiar espacios al final
        size_t end = line.find_last_not_of(" \t\r\n");
        line.erase(end + 1);

        if (!line.empty()) {
            data.push_back(line);
        }
    }

    file.close();

    return data;
}

std::string Sorter::saveFileData(const std::vector<std::string> sortedData, const std::string algorithm) const {
    std::string outputFilePath;

    std::string timestamp = std::to_string(
    std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
            ).count()
    );

    std::string fileName = algorithm + "_" + timestamp + ".txt";
    outputFilePath = "output/" + fileName;

    std::ofstream outFile(outputFilePath, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo: " << outputFilePath << std::endl;
    }

    for (const std::string& line : sortedData) {
         outFile << line << "\r\n";
    }

    outFile.close();

    return fileName;
}

SortResponseDto Sorter::quickSort(const std::string filePath, std::vector<std::string> unsortedData) const {

    // Falta el codigo que ordene el archivo

    std::string outputPath = saveFileData(unsortedData, quickSortName);

    // Mensaje a enviar al frontend
    SortResponseDto sort_response_dto;
    sort_response_dto.success        = true;
    sort_response_dto.message        = "quickSort";
    sort_response_dto.algorithm      = quickSortName;
    sort_response_dto.outputFilePath = outputPath;
    sort_response_dto.durationMs     = 0;
    sort_response_dto.totalWords     = unsortedData.size();

    return sort_response_dto;
}

SortResponseDto Sorter::heapSort(const std::string filePath, std::vector<std::string> unsortedData) const {

    // Falta el codigo que ordene el archivo
    std::string outputPath = saveFileData(unsortedData, heapSortName);

    // Mensaje a enviar al frontend
    SortResponseDto sort_response_dto;
    sort_response_dto.success        = true;
    sort_response_dto.message        = "heapSort";
    sort_response_dto.algorithm      = heapSortName;
    sort_response_dto.outputFilePath = outputPath;
    sort_response_dto.durationMs     = 0;
    sort_response_dto.totalWords     = unsortedData.size();

    return sort_response_dto;
}

SortResponseDto Sorter::balancedTree(const std::string filePath, const std::vector<std::string> unsortedData) const {

    auto start = std::chrono::high_resolution_clock::now();

    Avl avl;
    std::vector<std::string> sortedData = avl.sort(unsortedData);

    auto end = std::chrono::high_resolution_clock::now();
    double durationMs = std::chrono::duration<double, std::milli>(end - start).count();

    std::string outputPath = saveFileData(sortedData, balancedTreeName);

    // Mensaje a enviar al frontend
    SortResponseDto sort_response_dto;
    sort_response_dto.success        = true;
    sort_response_dto.message        = "Ordenamiento completado exitosamente con AVL. El archivo fue organizado alfabéticamente y el tiempo de ejecución fue registrado para el análisis comparativo.";
    sort_response_dto.algorithm      = balancedTreeName;
    sort_response_dto.outputFilePath = outputPath;
    sort_response_dto.durationMs     = durationMs;
    sort_response_dto.totalWords     = unsortedData.size();

    return sort_response_dto;
}
