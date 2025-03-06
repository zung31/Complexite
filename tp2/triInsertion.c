#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // numero aleatoire entre 0 et 9999
    }
}

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

double measureExecutionTime(int arr[], int n) {
    clock_t start, end;
    start = clock();
    insertionSort(arr, n);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL)); // seed random number generator

    // Petite array
    int petiteSize = 1000;
    int petiteArray[petiteSize];
    generateRandomArray(petiteArray, petiteSize);
    double petiteTime = measureExecutionTime(petiteArray, petiteSize);
    printf("Petite array size: %d, Execution time: %f seconds\n", petiteSize, petiteTime);

    // Determine Moyenne array size
    int moyenneSize = petiteSize;
    double moyenneTime;
    do {
        moyenneSize = (int)(moyenneSize * 1.3); // augmenter 30% pour chaque test
        int moyenneArray[moyenneSize];
        generateRandomArray(moyenneArray, moyenneSize);
        moyenneTime = measureExecutionTime(moyenneArray, moyenneSize);
    } while (moyenneTime < 10 * petiteTime);
    printf("Moyenne array size: %d, Execution time: %f seconds\n", moyenneSize, moyenneTime);

    // Determine Grande array size
    int grandeSize = moyenneSize;
    double grandeTime;
    do {
        grandeSize = (int)(grandeSize * 1.3); // augmenter 30% pour chaque test
        int grandeArray[grandeSize];
        generateRandomArray(grandeArray, grandeSize);
        grandeTime = measureExecutionTime(grandeArray, grandeSize);
    } while (grandeTime < 100 * moyenneTime);
    printf("Grande array size: %d, Execution time: %f seconds\n", grandeSize, grandeTime);

    return 0;
}