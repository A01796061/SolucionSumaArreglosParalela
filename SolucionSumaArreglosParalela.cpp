//Author Daniel Olivares
#include <cstdlib>
#include <ctime>
#include <iostream> 
#include <random> 

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0 
#endif

void assignRandomValuesToArrays(int arraySize, int* arrayA, int* arrayB) {
    // Asignar valores aleatorios al arreglo usando OpenMP
    #pragma omp parallel for 
    for (int i = 0; i < arraySize; ++i) {
        int threadId = omp_get_thread_num(); // Obtener el número de thread 
        //Se obtiene un numero random utilizando el hardware y sumandole el 
        // numero del thread esto va a garantizar que cada numero generado sea aleatorio 
        // a travez de todos los threads
        std::random_device rd;
        std::mt19937 gen(rd() + threadId);
        std::uniform_int_distribution<> distrib(1, arraySize);

        arrayA[i] = distrib(gen);//Se generae un numero random para el arreglo A
        arrayB[i] = distrib(gen);//Se generae un numero random para el arreglo B
    }
}

void sumArrays(int arraySize, int* arrayA, int* arrayB, int* arrayC) {
    // Sumar los valores de los arreglos A y B en el arreglo arrayC
    #pragma omp parallel for
    for (int i = 0; i < arraySize; ++i) {
        arrayC[i] = arrayA[i] + arrayB[i];
    }
}

void showArrayValues(int arraySize, int* arrayA, int* arrayB, int* arrayC) {
    for (int i = 0; i < arraySize; ++i) {
        std::cout << "ArrayA[" <<  i << "] = " << arrayA[i] << " + ArrayB[" <<  i << "] = " << arrayB[i] << " = ArrayC[" <<  i << "] " << arrayC[i] << std::endl;
    }
}

int main() {
    const int arraySize = 1000;  // Tamaño del arreglo
    int arrayA[arraySize];
    int arrayB[arraySize];
    int arrayC[arraySize];

    assignRandomValuesToArrays(arraySize, arrayA, arrayB);
    sumArrays(arraySize, arrayA, arrayB, arrayC);
    showArrayValues(arraySize, arrayA, arrayB, arrayC);

    return 0;
}