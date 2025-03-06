import matplotlib.pyplot as plt
import math

# Data de programme compareTri.c
merge_sort_times = [
    0.000000, 0.001000, 0.002000, 0.003000, 0.002000, 0.003000, 0.004000, 0.004000, 0.004000, 0.004000, 0.004000, 0.006000, 0.006000, 0.006000, 0.007000, 0.007000, 0.009000, 0.008000, 0.011000, 0.010000, 0.009000, 0.011000, 0.015000, 0.013000, 0.012000, 0.011000, 0.011000, 0.018000, 0.013000, 0.013000, 0.014000, 0.015000, 0.015000, 0.015000, 0.014000, 0.016000, 0.018000, 0.016000, 0.017000, 0.017000, 0.018000, 0.018000, 0.019000, 0.021000, 0.020000, 0.020000, 0.022000, 0.021000, 0.026000, 0.022000, 0.023000
]

# X-axis values (array sizes)
array_sizes = [i * 1000 for i in range(1, 52)]

# Calculate theoretical times for Merge Sort (O(n log n))
C = 4.25E-8
theoretical_times = [C * size * math.log(size) for size in array_sizes]
# plot
plt.figure(figsize=(10, 6))
plt.plot(array_sizes, merge_sort_times, label='Tri fusion (Actuel)', marker='o', linestyle='-')
plt.plot(array_sizes, theoretical_times, label='Tri fusion (Theorique O(nlogn))', linestyle='--', marker='x')
plt.title('Comparaison des temps d\'exécution de Tri fusion (Actuel vs Theorique)')
plt.xlabel('Array Size')
plt.ylabel('Exécution Temps (seconds)')
plt.legend()
plt.grid(True)

# Show the plot
plt.show()