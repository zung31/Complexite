import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# Data de temps réel pour n = 1, 2, ..., 25
actual_times = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.001, 0.001, 0.003, 0.006, 0.011, 0.021, 0.046, 0.092, 0.183, 0.380, 0.750, 
                1.560, 2.870, 5.940, 12.200, 23.600, 47.400, 95.500, 182.700]
# actual_times = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.001, 0.001, 0.003, 0.006, 0.014, 0.024, 0.049, 0.100, 0.190, 0.410, 
#                 0.810, 1.570, 3.130, 6.300, 12.700, 25.100, 51.200, 100.900]
n = np.arange(1, 26)  # n de 1 à 25

# Fonctions exponentielles sont utilisées pour modéliser des données qui croissent de manière exponentielle.
# x: variable indépendante = n; a: facteur de proportion; b: coefficient exponentiel, détermine le taux d'augmentation de la fonction.
def exponential_func(x, a, b):
    return a * np.exp(b * x)

# chercher les paramètres a et b (params) qui minimisent l'erreur quadratique moyenne entre les valeurs réelles et les valeurs prédites
# en utilisant la fonction curve_fit de scipy.optimize
params, _ = curve_fit(exponential_func, n, actual_times)
# Calculer les valeurs prédites (courbe tendance) pour les temps en utilisant les paramètres trouvés
trendline = exponential_func(n, *params)

# graph
plt.scatter(n, actual_times, label='Reel data')
plt.plot(n, actual_times, linestyle='-', color='blue', label='Courbe résultante')  # Đường nối các điểm thực tế
plt.plot(n, trendline, color='red', label='Courbe tendance')
plt.xlabel('n')
plt.ylabel('Temps (ms)')
plt.title('Comparaison entre les données réelles et la courbe tendance')
plt.legend()
plt.grid(True)
plt.show()