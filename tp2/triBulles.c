#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // numero aleatoire entre 0 et 9999
    }
}

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

double measureExecutionTime(int arr[], int n) {
    clock_t start, end;
    start = clock();
    bubbleSort(arr, n);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL)); // Seed the random number generator

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
        moyenneSize = (int)(moyenneSize * 1.3); // Increase size by 30% for each test
        int moyenneArray[moyenneSize];
        generateRandomArray(moyenneArray, moyenneSize);
        moyenneTime = measureExecutionTime(moyenneArray, moyenneSize);
    } while (moyenneTime < 10 * petiteTime);
    printf("Moyenne array size: %d, Execution time: %f seconds\n", moyenneSize, moyenneTime);

    // Determine Grande array size
    int grandeSize = moyenneSize;
    double grandeTime;
    do {
        grandeSize = (int)(grandeSize * 1.3); // Increase size by 30% for each test
        int grandeArray[grandeSize];
        generateRandomArray(grandeArray, grandeSize);
        grandeTime = measureExecutionTime(grandeArray, grandeSize);
    } while (grandeTime < 100 * moyenneTime);
    printf("Grande array size: %d, Execution time: %f seconds\n", grandeSize, grandeTime);

    return 0;
}