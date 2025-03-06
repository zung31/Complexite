import matplotlib.pyplot as plt

# Data de programme compareTri.c
bubble_sort_times = [
    0.002000, 0.012000, 0.030000, 0.060000, 0.152000, 0.119000, 0.156000, 0.183000, 0.223000, 0.282000, 0.330000, 0.437000, 0.535000, 0.630000, 0.720000, 0.799000, 1.724000, 1.102000, 1.258000, 1.456000, 1.594000, 1.837000, 2.317000, 2.438000, 2.424000, 2.602000, 2.837000, 3.151000, 3.443000, 3.714000, 3.905000, 4.283000, 4.698000, 4.936000, 5.147000, 5.556000, 5.758000, 6.058000, 6.476000, 6.764000, 6.929000, 7.396000, 7.841000, 8.491000, 8.525000, 9.367000, 9.716000, 10.083000, 10.322000, 11.364000, 11.281000
]

# X-axis values (array sizes)
array_sizes = [i * 1000 for i in range(1, 52)]

# Calculate theoretical times for Bubble Sort (O(n^2))
C = 4.51240000E-9
theoretical_times = [C * size**2 for size in array_sizes]
# plot
plt.figure(figsize=(10, 6))
plt.plot(array_sizes, bubble_sort_times, label='Tri à bulles (Actuel)', marker='o', linestyle='-')
plt.plot(array_sizes, theoretical_times, label='Tri à bulles (Theorique O(n^2))', linestyle='--', marker='x')
plt.title('Comparaison des temps d\'exécution de Tri à bulles (Actuel vs Theorique)')
plt.xlabel('Array Size')
plt.ylabel('Exécution Temps (seconds)')
plt.legend()
plt.grid(True)

# Show the plot
plt.show()