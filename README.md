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

El sistema expone una **API REST** (servidor HTTP construido con Crow) y un frontend web, que permite subir un archivo `.txt` con palabras, seleccionar uno o todos los algoritmos y visualizar métricas comparativas de tiempo de ejecución y consumo de memoria.

Además, la interfaz incluye un **modo aleatorio** mediante un switch para indicar si el archivo subido ya está ordenado. Cuando esta opción está activada, el sistema desordena primero los datos antes de ejecutar los algoritmos, evitando pruebas sesgadas y casos desfavorables como el peor caso de QuickSort sobre entradas ya ordenadas.

---

## Arquitectura del proyecto

El servidor recibe el archivo del usuario, lo guarda en `uploads/`, invoca el algoritmo correspondiente y guarda el resultado en `output/`. Las métricas (tiempo, palabras, memoria) se devuelven como JSON al frontend.

## Estructura

```text
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

## API REST

| Método | Endpoint | Descripción |
|--------|----------|-------------|
| `GET` | `/` | Sirve la interfaz web (Mustache → `index.html`) |
| `GET` | `/api/health` | Comprobación de estado del servidor (`"ok"`) |
| `POST` | `/api/sort?algorithm=<n>&sorted=<bool>` | Ordena el archivo recibido con el algoritmo indicado |
| `GET` | `/api/download?file=<filename>` | Descarga el archivo de salida generado |
| `POST` | `/api/compare?sorted=<bool>` | Ejecuta los tres algoritmos y devuelve métricas de cada uno |

### Valores válidos para `algorithm`

| Valor | Algoritmo |
|-------|-----------|
| `quicksort` | QuickSort |
| `heapsort` | HeapSort |
| `avl` | Árbol AVL |

### Parámetro opcional `sorted`

| Valor | Significado |
|-------|-------------|
| `true` | El archivo ya está ordenado y debe desordenarse antes de evaluar |
| `false` | El archivo ya viene desordenado y se puede ordenar directamente |

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

## Iniciar la aplicación

### 1. Requisitos

Antes de ejecutar el proyecto, asegúrate de tener instalado:

- Un compilador compatible con **C++17**
- **CMake**
- Las dependencias incluidas en el proyecto (`Crow` y `Asio` en `external/`)

### 2. Compilar el proyecto

Desde la raíz del repositorio, ejecuta:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### 3. Ejecutar el servidor

Una vez compilado, ejecuta el binario generado:

```bash
./DataSorter
```

> En Windows, el ejecutable puede generarse como `DataSorter.exe`.

### 4. Abrir la interfaz web

Con el servidor encendido, abre en el navegador:

```text
http://localhost:8080
```

### 5. Probar la aplicación

1. Sube un archivo `.txt` con una palabra por línea.
2. Activa el switch si el archivo ya está ordenado y quieres que el sistema lo mezcle antes de probar.
3. Elige un algoritmo o usa la opción de comparar todos.
4. Revisa las métricas en pantalla y descarga el archivo resultante si lo deseas.

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
