#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // numero aleatoire entre 0 et 9999
    }
}

// selectionSort function
void selectionSort(int arr[], int n) {
    int i, j, minIndex, temp;
    for (i = 0; i < n-1; i++) {
        minIndex = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

// triInsertion function
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

// triBulles function
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

// triFusion function
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

// mesurer le temps d'execution => modifier pour chaque tri
double measureExecutionTime(void (*sortFunc)(int[], int), int arr[], int n) {
    clock_t start, end;
    start = clock();
    //mergeSort(arr, 0, n - 1);
    sortFunc(arr, n);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

int main(){
    srand(time(NULL)); // Seed the random number generator

    // array size from 1000 to 50 000
    int sizeArray = 1000;
    int numSizes = 51;
    int sizes[numSizes];
    for (int i = 0; i <= numSizes; i++) {
        sizes[i] = sizeArray;
        sizeArray += 1000;
    }
    // array store results
    double results[numSizes]; // store times d'un seul type tri

    // mesure pour chaque type
    for (int i = 0; i < numSizes; i++) {
        int size = sizes[i];
        int *arr = (int*) malloc(size * sizeof(int));
        if (!arr) {
            printf("Memory allocation failed\n");
            return 1;
        }

        // Measure execution time for selectionSort
        generateRandomArray(arr, size);
        results[i] = measureExecutionTime(selectionSort, arr, size);

        // Measure execution time for insertionSort
        // generateRandomArray(arr, size);
        // results[i] = measureExecutionTime(insertionSort, arr, size);

        // Measure execution time for bubbleSort
        // generateRandomArray(arr, size);
        // results[i] = measureExecutionTime(bubbleSort, arr, size);

        // Measure execution time for mergeSort
        // generateRandomArray(arr, size);
        // results[i] = measureExecutionTime(mergeSort, arr, size);

        free(arr);
    }

    // print results
    for(int i=0; i< numSizes; i++){
        printf("%f ",results[i]);
    }
}