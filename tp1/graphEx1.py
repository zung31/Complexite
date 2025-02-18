import matplotlib.pyplot as plt
import numpy as np

# Actuelle temps d'éxécution (milliséconds) pour n = 1, 2, ..., 25 basé sur les données fournies
actual_times = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.001, 0.001, 0.003, 0.006, 0.011, 0.021, 
                0.046, 0.092, 0.183, 0.380, 0.750, 1.560, 2.870, 5.940, 12.200, 23.600, 47.400, 95.500, 182.700]
# actual_times = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.001, 0.001, 0.003, 0.006, 0.014, 0.024, 0.049, 0.100, 0.190, 0.410, 
#                 0.810, 1.570, 3.130, 6.300, 12.700, 25.100, 51.200, 100.900]
# Values of n 1->25
n_values = list(range(1, 26))
# Calculer le temps théorique basé sur la formule T(n) = C * (2^n - 1)
C = 5.444e-06  # je calcule C pour correspondre au mieux à la série de données en temps réel
theoretical_times = [C * (2**n - 1) for n in n_values]
# Plot the results
plt.plot(n_values, actual_times, label='Actuelle Temps Execution', marker='o')
plt.plot(n_values, theoretical_times, label='Temps Theorique (O(2^n - 1))', linestyle='--')
plt.xlabel('n')
plt.ylabel('Temps (ms)')
plt.title('Comparer Actuelle Temps Execution avec Temps Theorique')
plt.legend()
plt.yscale('log')  # Use logarithmic scale for better visualization
plt.grid(True)
plt.show()