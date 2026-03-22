#ifndef DATASORTER_NODE_H
#define DATASORTER_NODE_H
#include <string>

struct Node {
    std::string data;
    Node *left, *right;
    int height;
    explicit Node(const std::string& d) : data(d), left(nullptr), right(nullptr), height(1) {}
};

#endif //DATASORTER_NODE_H