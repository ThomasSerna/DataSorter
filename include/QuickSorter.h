

#ifndef QUICKSORTER_H
#define QUICKSORTER_H

#include <vector>
#include <string>

using namespace std;

class QuickSorter {
public:
    void ordenar(vector<string>& arreglo);

private:
    void quickSort(vector<string>& arreglo, int izquierda, int derecha);
    int particion(vector<string>& arreglo, int izquierda, int derecha);

};

#endif