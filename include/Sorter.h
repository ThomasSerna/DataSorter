
#ifndef DATASORTER_SORTER_H
#define DATASORTER_SORTER_H
#include "dto/SortResultDto.h"
#include <fstream>


class Sorter {
public:
    SortResponseDto sort(const std::string filePath, const std::string algorithm) const;
private:
    std::vector<std::string> extractFileData(const std::string filePath) const;
    SortResponseDto quickSort(const std::string filePath, std::vector<std::string> unsortedData) const;
    SortResponseDto heapSort(const std::string filePath, std::vector<std::string> unsortedData) const;
    SortResponseDto balancedTree(const std::string filePath, std::vector<std::string> unsortedData) const;

    std::string quickSortName = "quicksort";
    std::string heapSortName = "heapsort";
    std::string balancedTreeName = "avl";
};


#endif //DATASORTER_SORTER_H