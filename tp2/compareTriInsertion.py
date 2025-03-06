import matplotlib.pyplot as plt

# Data de programme compareTri.c
insertion_sort_times = [
    0.001000, 0.004000, 0.012000, 0.018000, 0.019000, 0.029000, 0.042000, 0.051000, 0.070000, 0.087000, 0.102000, 0.131000, 0.141000, 0.181000, 0.190000, 0.235000, 0.246000, 0.270000, 0.309000, 0.582000, 0.495000, 0.475000, 0.476000, 0.571000, 0.548000, 0.561000, 0.648000, 0.646000, 0.733000, 0.772000, 0.799000, 1.031000, 1.133000, 1.174000, 1.366000, 1.380000, 1.499000, 1.402000, 1.439000, 1.594000, 1.787000, 1.836000, 1.832000, 1.827000, 1.908000, 2.145000, 2.066000, 2.148000, 2.245000, 2.484000, 2.571000
]

# X-axis values (array sizes)
array_sizes = [i * 1000 for i in range(1, 52)]

# Calculate theoretical times for Insertion Sort (O(n^2))
C = 1.02840000E-9
theoretical_times = [C * size**2 for size in array_sizes]
# plot
plt.figure(figsize=(10, 6))
plt.plot(array_sizes, insertion_sort_times, label='Tri insertion (Actuel)', marker='o', linestyle='-')
plt.plot(array_sizes, theoretical_times, label='Tri insertion (Theorique O(n^2))', linestyle='--', marker='x')
plt.title('Comparaison des temps d\'exécution de Tri insertion (Actuel vs Theorique)')
plt.xlabel('Array Size')
plt.ylabel('Exécution Temps (seconds)')
plt.legend()
plt.grid(True)

# Show the plot
plt.show()