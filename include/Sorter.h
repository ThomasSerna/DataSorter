//
// Created by User on 10/03/2026.
//

#ifndef DATASORTER_SORTER_H
#define DATASORTER_SORTER_H
#include "dto/SortResultDto.h"


class Sorter {
public:
    SortResponseDto sort(const std::string filePath, const std::string algorithm);
};


#endif //DATASORTER_SORTER_H