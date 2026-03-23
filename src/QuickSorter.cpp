#include "QuickSorter.h"

// Método público
void QuickSorter::ordenar(vector<string>& arreglo) {
    if (arreglo.size() > 0) {
        quickSort(arreglo, 0, arreglo.size() - 1);
    }
}

// QuickSort recursivo
void QuickSorter::quickSort(vector<string>& arreglo, int izquierda, int derecha) {
    if (izquierda < derecha) {
        int indicePivote = particion(arreglo, izquierda, derecha);

        quickSort(arreglo, izquierda, indicePivote - 1);
        quickSort(arreglo, indicePivote + 1, derecha);
    }
}

// Partición
int QuickSorter::particion(vector<string>& arreglo, int izquierda, int derecha) {
    string pivote = arreglo[derecha];
    int i = izquierda - 1;

    for (int j = izquierda; j < derecha; j++) {
        if (arreglo[j] <= pivote) {
            i++;

            string temp = arreglo[i];
            arreglo[i] = arreglo[j];
            arreglo[j] = temp;
        }
    }

    string temp = arreglo[i + 1];
    arreglo[i + 1] = arreglo[derecha];
    arreglo[derecha] = temp;

    return i + 1;
}