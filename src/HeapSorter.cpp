#include "HeapSorter.h"
#include <vector>
#include <string>

using namespace std;

// Método principal
void HeapSorter::ordenar(vector<string>& arreglo) {
    int tamano = arreglo.size();

    // Construir heap
    construirHeap(arreglo, tamano);

    // Extraer elementos
    for (int i = tamano - 1; i > 0; i--) {
        string temp = arreglo[0];
        arreglo[0] = arreglo[i];
        arreglo[i] = temp;

        heapify(arreglo, i, 0);
    }
}

// Construir heap máximo
void HeapSorter::construirHeap(vector<string>& arreglo, int tamano) {
    for (int i = tamano / 2 - 1; i >= 0; i--) {
        heapify(arreglo, tamano, i);
    }
}

// Mantener propiedad del heap
void HeapSorter::heapify(vector<string>& arreglo, int tamano, int indice) {
    int mayor = indice;
    int hijoIzquierdo = 2 * indice + 1;
    int hijoDerecho = 2 * indice + 2;

    if (hijoIzquierdo < tamano && arreglo[hijoIzquierdo] > arreglo[mayor]) {
        mayor = hijoIzquierdo;
    }

    if (hijoDerecho < tamano && arreglo[hijoDerecho] > arreglo[mayor]) {
        mayor = hijoDerecho;
    }

    if (mayor != indice) {
        string temp = arreglo[indice];
        arreglo[indice] = arreglo[mayor];
        arreglo[mayor] = temp;

        heapify(arreglo, tamano, mayor);
    }
}