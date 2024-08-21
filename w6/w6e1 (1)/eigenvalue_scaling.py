import numpy as np
import scipy.linalg
import time
from os import environ
environ['OMP_NUM_THREADS'] = '1' # Set number of threads to 1 for scipy

# Generate logarithmically distributed matrix sizes from N=30 to N=1000
matrix_sizes = np.unique(np.logspace(np.log10(30), np.log10(1000), num=20).astype(int))

cpu_times = []
for N in matrix_sizes:
    times = []
    for _ in range(5): # Repeat each size 5 times for statistics
        A = np.random.rand(N, N)
        start_time = time.process_time()
        scipy.linalg.eig(A)
        end_time = time.process_time()
        times.append(end_time - start_time)
    avg_time = np.mean(times)
    cpu_times.append(avg_time)

# Plot CPU time as a function of matrix size
import matplotlib.pyplot as plt

plt.figure(figsize=(10, 6))
plt.plot(matrix_sizes, cpu_times, marker='o')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Matrix Size N')
plt.ylabel('Average CPU Time (s)')
plt.title('CPU Time for Computing Eigenvalues as a Function of Matrix Size')
plt.grid(True, which="both", ls="--")
plt.show()

