import matplotlib.pyplot as plt
import numpy as np
import math

# temps d'exécution en réalité (milliseconds)
actual_times = [
    1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 2.0,
    1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 2.0, 2.0, 1.0, 2.0,
    2.0, 3.0, 2.0, 2.0, 2.0, 3.0, 2.0, 2.0, 3.0, 2.0,
    3.0, 2.0, 3.0, 3.0, 2.0, 3.0, 3.0, 3.0, 4.0, 3.0,
    3.0, 3.0, 4.0, 3.0, 3.0, 4.0, 3.0, 4.0, 4.0, 3.0,
    4.0, 4.0, 5.0, 4.0, 6.0, 6.0, 11.0, 5.0, 5.0, 7.0,
    5.0, 5.0, 6.0, 7.0, 6.0, 5.0, 6.0, 5.0, 4.0, 5.0,
    5.0, 5.0, 5.0, 5.0, 5.0, 6.0, 5.0, 5.0, 6.0, 6.0,
    5.0
]

# n de 100000 à 1000000 par pas de 10000
n_values = list(range(100000, 1000000, 10000))
X = np.array([n * math.log(math.log(n)) for n in n_values])
Y = np.array(actual_times)
C_optimal = np.sum(X * Y) / np.sum(X * X)

theoretical_times = [C_optimal * n* math.log(math.log(n)) for n in n_values]

# Plot the results
plt.plot(n_values, actual_times, label='Temps actuel', marker='o')
plt.plot(n_values, theoretical_times, label='Temps theorique (O(log(log(n)))', linestyle='--')
plt.xlabel('n')
plt.ylabel('Temps (ms)')
plt.title('Comparaison entre temps actuel et temps theorique')
plt.legend()
plt.yscale('log')  
plt.grid(True)
plt.show()