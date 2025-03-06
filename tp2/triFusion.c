#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // numero aleatoire entre 0 et 9999
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int*) malloc(n1 * sizeof(int));
    int *R = (int*) malloc(n2 * sizeof(int));
    
    if (!L || !R) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

double measureExecutionTime(int arr[], int n) {
    clock_t start, end;
    start = clock();
    mergeSort(arr, 0, n - 1);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    // Petite array
    int petiteSize = 1000;
    int *petiteArray = (int*) malloc(petiteSize * sizeof(int));
    if (!petiteArray) {
        printf("Memory allocation failed\n");
        return 1;
    }
    generateRandomArray(petiteArray, petiteSize);
    double petiteTime = measureExecutionTime(petiteArray, petiteSize);
    printf("Petite array size: %d, Execution time: %f seconds\n", petiteSize, petiteTime);
    free(petiteArray);

    // Determine Moyenne array size
    int moyenneSize = petiteSize;
    double moyenneTime;
    int *moyenneArray = NULL;
    do {
        free(moyenneArray);
        moyenneSize = (int)(moyenneSize * 1.3);
        moyenneArray = (int*) malloc(moyenneSize * sizeof(int));
        if (!moyenneArray) break;
        generateRandomArray(moyenneArray, moyenneSize);
        moyenneTime = measureExecutionTime(moyenneArray, moyenneSize);
    } while (moyenneTime < 10 * petiteTime);
    printf("Moyenne array size: %d, Execution time: %f seconds\n", moyenneSize, moyenneTime);
    free(moyenneArray);

    // Determine Grande array size
    int grandeSize = moyenneSize;
    double grandeTime;
    int *grandeArray = NULL;
    do {
        free(grandeArray);
        grandeSize = (int)(grandeSize * 1.3);
        grandeArray = (int*) malloc(grandeSize * sizeof(int));
        if (!grandeArray) break;
        generateRandomArray(grandeArray, grandeSize);
        grandeTime = measureExecutionTime(grandeArray, grandeSize);
    } while (grandeTime < 100 * moyenneTime);
    printf("Grande array size: %d, Execution time: %f seconds\n", grandeSize, grandeTime);
    free(grandeArray);

    return 0;
}