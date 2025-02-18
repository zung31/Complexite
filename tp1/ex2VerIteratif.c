#include <stdio.h>
#include <time.h>

// fonction Fibonacci itérative
int fibonacci(int n) {
    if (n <= 1) {
        return 1;
    }
    int a = 1, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    // Test n de 0 à 25
    for (int n = 0; n <= 25; n++) {
        int iterations = 1000;
        clock_t start = clock();
        int result = 0;
        for (int i = 0; i < iterations; i++) {
            result = fibonacci(n);
        }
        clock_t end = clock();
        double elapsed_ms = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC / iterations;
        // Afficher le temps d'exécution
        printf("Fibonacci(%d) = %d ; temps execution = %.4f ms\n", n, result, elapsed_ms);
    }
    return 0;
}