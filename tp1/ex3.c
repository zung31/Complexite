#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

// fonction crible
int sieve(int N) {
    // Allouer un tableau de booléens pour marquer les nombres
    bool *isMarked = malloc((N + 1) * sizeof(bool));
    if (isMarked == NULL) {
        printf("Erreur d'allocation mémoire pour N = %d\n", N);
        return -1;
    }
    // false = "non marqué" (potentiellement premier)
    for (int i = 0; i <= N; i++) {
        isMarked[i] = false;
    }
    // 1 n'est pas un nombre premier
    if (N >= 1)
        isMarked[1] = true;
    // Criblage: pour chaque nombre p de 2 à sqrt(N)
    int sqrtN = (int) sqrt(N);
    for (int p = 2; p <= sqrtN; p++) {
        if (!isMarked[p]) { // Si p n'est pas marqué, alors p est premier.
            // On marque tous les multiples de p à partir de p*p
            // car les multiples de p plus petits que p*p ont déjà été marqués 
            // par les premiers plus petits que p.
            for (int i = p * p; i <= N; i += p) {
                isMarked[i] = true;
            }
        }
    }
    // Compter le nombre de nombres premiers (non marqués == false) de 2 à N
    int count = 0;
    for (int i = 2; i <= N; i++) {
        if (!isMarked[i]) {
            count++;
        }
    }
    free(isMarked);
    return count;
}

int main(void) {
    // Tester pour N de 100 000 à 1 000 000 par pas de 1000
    // j'ai pas utilisé boucle faisant plusieurs itérations pour chaque N
    // car j'ai deja utilisé un N plus grand
    for (int N = 100000; N <= 1000000; N += 10000) {
        clock_t start = clock();
        int primeCount = sieve(N);
        clock_t end = clock();
        double elapsed_ms = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
        printf("N = %d, nombre de premiers = %d, temps d'exécution = %.6f ms\n", N, primeCount, elapsed_ms);
    }
    return 0;
}
