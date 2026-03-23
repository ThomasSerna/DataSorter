# Data Sorter — Comparador de Algoritmos de Ordenamiento

**ST0245 · SI001 — Estructuras de Datos y Algoritmos**  
Universidad EAFIT · Práctica I  
Docente: Alexander Narváez Berrío

**Autores:** Thomas Serna Saldarriaga · David Alzate Monroy

---

## Descripción general

Este proyecto implementa un sistema web en **C++** capaz de ordenar grandes conjuntos de palabras usando tres estrategias algorítmicas distintas, cada una basada en una estructura de datos diferente:

- **QuickSort** sobre un arreglo dinámico (`std::vector<string>`)
- **HeapSort** con un montículo binario (*Binary Heap*)
- **Árbol AVL** con recorrido *inorder* para obtener el orden final

El sistema expone una **API REST** (servidor HTTP construido con Crow y un frontend web, que permite subir un archivo `.txt` con palabras, seleccionar uno o todos los algoritmos y visualizar métricas comparativas de tiempo de ejecución y consumo de memoria.

---

## Arquitectura del proyecto


El servidor recibe el archivo del usuario, lo guarda en `uploads/`, invoca el algoritmo correspondiente y guarda el resultado en `output/`. Las métricas (tiempo, palabras, memoria) se devuelven como JSON al frontend.

## API REST

| Método | Endpoint | Descripción |
|--------|----------|-------------|
| `GET` | `/` | Sirve la interfaz web (Mustache → `index.html`) |
| `GET` | `/api/health` | Comprobación de estado del servidor (`"ok"`) |
| `POST` | `/api/sort?algorithm=<n>` | Ordena el archivo recibido con el algoritmo indicado |
| `GET` | `/api/download?file=<filename>` | Descarga el archivo de salida generado |
| `POST` | `/api/compare` | Ejecuta los tres algoritmos y devuelve métricas de cada uno |

### Valores válidos para `algorithm`

| Valor | Algoritmo |
|-------|-----------|
| `quicksort` | QuickSort |
| `heapsort` | HeapSort |
| `avl` | Árbol AVL |

### Ejemplo de respuesta (`SortResponseDto`)

```json
{
  "success": true,
  "message": "Ordenamiento completado exitosamente con Quick Sort...",
  "algorithm": "quicksort",
  "outputFilePath": "quicksort_1714000000000.txt",
  "durationMs": 142.57,
  "totalWords": 100000,
  "memoryBytes": 7340032
}
```


---

## Análisis de rendimiento

### Medición de tiempo

El tiempo de ejecución se mide exclusivamente sobre la operación de ordenamiento, usando `std::chrono::high_resolution_clock`:

```cpp
auto start = std::chrono::high_resolution_clock::now();
// ... ordenamiento ...
auto end = std::chrono::high_resolution_clock::now();
double durationMs = std::chrono::duration<double, std::milli>(end - start).count();
```

### Complejidad Big-O

| Algoritmo | Tiempo promedio | Tiempo peor caso | Espacio extra |
|-----------|----------------|-----------------|---------------|
| QuickSort | O(n log n) | O(n²) | O(log n) |
| HeapSort | O(n log n) | O(n log n) | O(1) |
| AVL Tree | O(n log n) | O(n log n) | O(n) |

---

## Estructura del repositorio

```
data-sorter/
├── external/
│   ├── asio/
│   │   └── asio.hpp           ← Biblioteca Asio (requerida por Crow)
│   └── crow_all.h             ← Framework HTTP Crow (header-only)
├── include/
│   ├── dto/
│   │   └── SortResultDto.h    ← DTO de respuesta del API
│   ├── Avl.h
│   ├── HeapSorter.h
│   ├── Node.h                 ← Nodo del Árbol AVL
│   ├── QuickSorter.h
│   ├── Server.h
│   └── Sorter.h
├── src/
│   ├── Avl.cpp                ← Implementación del Árbol AVL
│   ├── HeapSorter.cpp         ← Implementación del HeapSort
│   ├── Main.cpp               ← Punto de entrada del programa
│   ├── QuickSorter.cpp        ← Implementación del QuickSort
│   ├── Server.cpp             ← Servidor HTTP Crow + definición de rutas
│   └── Sorter.cpp             ← Coordinador de algoritmos + I/O de archivos
├── templates/
│   └── index.html             ← Interfaz web (Mustache)
├── uploads/                   ← Archivos subidos (generado en tiempo de ejecución)
├── output/                    ← Archivos ordenados (generado en tiempo de ejecución)
├── .gitignore
├── CMakeLists.txt
└── README.md
```

