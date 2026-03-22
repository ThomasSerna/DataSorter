#include "../include/Avl.h"

#include <algorithm>
#include <iostream>

std::vector<std::string> Avl::sort(const std::vector<std::string> unsortedData) {
    std::vector<std::string> sortedData;

    Node* root = nullptr;
    for (std::string data : unsortedData) root = insert(root, data);

    inOrder(root, sortedData);

    return sortedData;
}
int Avl::height(Node *n) const{
    return n ? n->height : 0;
}

// Calcula el factor de equilibrio (balance)
int Avl::getBalance(Node *n) const{
    return n ? height(n->left) - height(n->right) : 0;
}

// Rotación Simple a la Derecha
Node* Avl::rotateRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Realizar rotación
    x->right = y;
    y->left = T2;

    // Actualizar alturas
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    // Retornar nueva raíz del subárbol
    return x;
}

// Rotación Simple a la Izquierda
Node* Avl::rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Realizar rotación
    y->left = x;
    x->right = T2;

    // Actualizar alturas
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    // Retornar nueva raíz del subárbol
    return y;
}

// Método principal para insertar una palabra y balancear el árbol
Node* Avl::insert(Node* node, const std::string &key) {
    // 1. Inserción normal de un árbol binario de búsqueda
    if (!node) return new Node(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else
        return node; // No se permiten llaves duplicadas

    // 2. Actualizar la altura de este nodo ancestro
    node->height = 1 + std::max(height(node->left), height(node->right));

    // 3. Obtener el factor de balance para verificar si se desequilibró
    int balance = getBalance(node);

    // CASO 1: Rotación Simple Derecha (Izquierda-Izquierda)
    if (balance > 1 && key < node->left->data)
        return rotateRight(node);

    // CASO 2: Rotación Simple Izquierda (Derecha-Derecha)
    if (balance < -1 && key > node->right->data)
        return rotateLeft(node);

    // CASO 3: Rotación Doble Izquierda-Derecha
    if (balance > 1 && key > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // CASO 4: Rotación Doble Derecha-Izquierda
    if (balance < -1 && key < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void Avl::inOrder(Node *root, std::vector<std::string> &sortedData) {
    if (!root) return;
    inOrder(root->left, sortedData);
    sortedData.push_back(root->data);
    inOrder(root->right, sortedData);
}
