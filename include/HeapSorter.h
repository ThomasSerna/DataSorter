#ifndef HEAPSORTER_H
#define HEAPSORTER_H

#include <vector>
#include <string>

using namespace std;

class HeapSorter {
public:
    void ordenar(vector<string>& arreglo);

private:
    void construirHeap(vector<string>& arreglo, int tamano);
    void heapify(vector<string>& arreglo, int tamano, int indice);
};

#endif

