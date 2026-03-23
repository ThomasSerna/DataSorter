
#ifndef DATASORTER_SORTER_H
#define DATASORTER_SORTER_H
#include "dto/SortResultDto.h"
#include <fstream>


class Sorter {
public:
    SortResponseDto sort(const std::string filePath, const std::string algorithm) const;

    const std::string quickSortName = "quicksort";
    const std::string heapSortName = "heapsort";
    const std::string balancedTreeName = "avl";
private:
    std::vector<std::string> extractFileData(const std::string filePath) const;
    std::string saveFileData(const std::vector<std::string> sortedData, const std::string algorithm) const;
    SortResponseDto quickSort(std::vector<std::string> unsortedData) const;
    SortResponseDto heapSort(std::vector<std::string> unsortedData) const;
    SortResponseDto balancedTree(std::vector<std::string> unsortedData) const;
    size_t estimateVectorStringMemory(const std::vector<std::string>& data) const;


};


#endif //DATASORTER_SORTER_H