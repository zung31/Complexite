#include <stdio.h>
#include <time.h>

// definir struct pour stocker (F(n), F(n+1)) de Fibonacci
typedef struct {
    int f; // F(n)
    int g; // F(n+1)
} Pair;

// fonction fast doubling calcule (F(n), F(n+1)) avec (F(0)=1, F(1)=1)
Pair fib_fast_doubling(int n) {
    if (n == 0) {
        Pair p = {0, 1};
        return p;
    }
    // recursion pour n/2
    Pair p = fib_fast_doubling(n / 2);
    int a = p.f;
    int b = p.g;
    // calculer F(2k) et F(2k+1)
    int c = a * (2 * b - a);   // F(2k)=F(k)[2F(k+1)-F(k)]
    int d = a * a + b * b;       // F(2k+1)=F(k+1)^2+F(k)^2
    Pair result;
    if (n % 2 == 0) { // n est pair
        result.f = c; // F(n)=F(2k)
        result.g = d; // F(n+1)=F(2k+1)
    } else { // n est impair
        result.f = d; // F(n)=F(2k+1)
        result.g = c + d; // F(n+1)=F(2k)+F(2k+1)
    }
    return result;
}

// F(0)=1, F(1)=1, F(n)=F(n-1)+F(n-2) avec n>=2.
// F_new(n)=F_std(n+1) car F(0)=1 (differe de la definition standard F(0)=0)
// => on utilise résultat de fib_fast_doubling(n+1).f pour F(n) (n+1 est suivant de n)
int fibonacci(int n) {
    return fib_fast_doubling(n + 1).f;
}

int main(void) {
    // n de 0 à 25
    for (int n = 0; n <= 45; n++) {
        clock_t start = clock();
        int Fn = fibonacci(n);
        clock_t end = clock();
        double elapsed_ms = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
        printf("n = %d, F(n) = %d, execution time = %.6f ms\n", n, Fn, elapsed_ms);
    }
    return 0;
}
