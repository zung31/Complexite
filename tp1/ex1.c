#include <stdio.h>
#include <time.h>

void hanoi(int n, char a, char b, char c) {
    if (n == 1) {
        return;
    }
    hanoi(n - 1, a, c, b);
    hanoi(n - 1, b, a, c);
}

int main() {
    // loop n de 1 à 25
    // pour chaque n, je vais executer la fonction hanoi plusieurs fois 
    // et calculer le temps moyen pour avoir une meilleure précision
    for (int n = 1; n <= 25; n++) {
        int iterations = 1000;
        // pour les n plus grand, je vais reduire le nombre d'itérations pour gagner du temps
        if (n > 20) {
            iterations = 10; 
        } else if (n > 15) {
            iterations = 100; 
        }
        // Mesurer le temps d'exécution en millisecondes
        clock_t start = clock();
        for (int i = 0; i < iterations; i++) {
            hanoi(n, 'A', 'B', 'C');
        }
        clock_t end = clock();
        double elapsed_ms = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC / iterations;
        // Afficher le temps d'exécution
        printf("n = %d, temps execution = %.3f ms\n", n, elapsed_ms);
    }
    return 0;
}
