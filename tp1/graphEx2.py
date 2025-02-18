import matplotlib.pyplot as plt
import numpy as np

# temps d'exécution en réalité (milliseconds)
actual_times = [
    0.0000000, 0.0000000, 0.0000000, 0.0000000, 0.0000000, 0.0000000, 0.0000000, 0.0000000, 
    0.0000000, 0.0000000, 0.0000000, 0.0010000, 0.0010000, 0.0020000, 0.0040000, 0.0060000, 
    0.0100000, 0.0200000, 0.0200000, 0.0400000, 0.0600000, 0.1000000, 0.1000000, 0.3000000, 
    0.4000000, 0.7000000
]

# n de 0 à 25
n_values = list(range(0, 26))

# Fibonacci: T(n) = T(n-1) + T(n-2) + O(1) => n^2 = n + 1 (diviser par n-2)
# => Complexité approximite O(phi) où phi = 1.618 ((1+sqrt(5))/2)
# 0.7 = C * 1.618^25 => constant C est approximite de 4.17479455e-06
C = 4.17479455e-06
theoretical_times = [C * (1.618**n) for n in n_values]

# Plot the results
plt.plot(n_values, actual_times, label='Temps actuel', marker='o')
plt.plot(n_values, theoretical_times, label='Temps theorique (O(1.618^n))', linestyle='--')
plt.xlabel('n')
plt.ylabel('Temps (ms)')
plt.title('Comparaison entre temps actuel et temps theorique')
plt.legend()
plt.yscale('log')  
plt.grid(True)
plt.show()