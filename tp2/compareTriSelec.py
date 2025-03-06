import matplotlib.pyplot as plt

# Data de programme compareTri.c
selection_sort_times = [
    0.001000, 0.005000, 0.011000, 0.020000, 0.030000, 0.043000, 0.061000, 0.086000, 0.100000, 0.122000, 0.153000, 0.181000, 0.218000, 0.239000, 0.288000, 0.326000, 0.351000, 0.411000, 0.446000, 0.512000, 0.576000, 0.622000, 0.649000, 0.737000, 0.775000, 0.839000, 0.940000, 0.961000, 1.087000, 1.186000, 1.251000, 1.290000, 1.405000, 1.474000, 1.558000, 1.667000, 1.777000, 1.840000, 1.969000, 2.358000, 2.196000, 2.370000, 2.756000, 2.898000, 2.996000, 2.890000, 3.546000, 3.443000, 3.593000, 3.784000, 3.929000
]

# X-axis values (array sizes)
array_sizes = [i * 1000 for i in range(1, 52)]

# Calculate theoretical times for Selection Sort (O(n^2))
C = 1.57160000E-9
theoretical_times = [C * size**2 for size in array_sizes]
# plot
plt.figure(figsize=(10, 6))
plt.plot(array_sizes, selection_sort_times, label='Tri selection (Actuel)', marker='o', linestyle='-')
plt.plot(array_sizes, theoretical_times, label='Tri selection (Theorique O(n^2))', linestyle='--', marker='x')
plt.title('Comparaison des temps d\'exécution de Tri selection (Actuel vs Theorique)')
plt.xlabel('Array Size')
plt.ylabel('Exécution Temps (seconds)')
plt.legend()
plt.grid(True)

# Show the plot
plt.show()