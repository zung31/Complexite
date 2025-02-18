#include <stdio.h>
#include <time.h>

// Function to calculate the nth Fibonacci number recursively
int fibonacci(int n) {
    if (n <= 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    // Loop to test Fibonacci function for n from 0 to 25
    for (int n = 0; n <= 25; n++) {
        int iterations = 1000;
        // pour les n plus grand, je vais reduire le nombre d'itérations pour gagner du temps
        if (n > 20) {
            iterations = 10; 
        } else if (n > 15) {
            iterations = 100; 
        }

        // Mesurer le temps d'exécution en millisecondes
        clock_t start = clock();
        int result = 0;
        for (int i = 0; i < iterations; i++) {
            result = fibonacci(n);
        }
        clock_t end = clock();
        double elapsed_ms = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC / iterations;
        // Afficher le temps d'exécution
        printf("Fibonacci(%d) = %d ; temps execution = %.7f ms\n", n, result, elapsed_ms);
    }
    return 0;
}