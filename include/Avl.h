//
// Created by User on 21/03/2026.
//

#ifndef DATASORTER_AVL_H
#define DATASORTER_AVL_H
#include <string>
#include <vector>
#include "Node.h"


class Avl {
public:
    std::vector<std::string> sort(const std::vector<std::string> unsortedData);
private:
    int height(Node* n) const;
    int getBalance(Node* n) const;

    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* insert(Node* node, const std::string& key);

    void inOrder(Node *root, std::vector<std::string> &sortedData);
};


#endif //DATASORTER_AVL_H