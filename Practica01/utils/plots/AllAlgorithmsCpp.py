import numpy as np
from matplotlib import pyplot as plt

a, b = np.loadtxt('../../data/BubbleSort/valores_cpp.txt',
                  delimiter=',',
                  unpack=True)
c, d = np.loadtxt('../../data/CountingSort/valores_cpp.txt',
                  delimiter=',',
                  unpack=True)
e, f = np.loadtxt('../../data/HeapSort/valores_cpp.txt',
                  delimiter=',',
                  unpack=True)
g, h = np.loadtxt('../../data/InsertionSort/valores_cpp.txt',
                  delimiter=',',
                  unpack=True)
i, j = np.loadtxt('../../data/MergeSort/valores_cpp.txt',
                  delimiter=',',
                  unpack=True)
k, l = np.loadtxt('../../data/QuickSort/valores_cpp.txt',
                  delimiter=',',
                  unpack=True)
m, n = np.loadtxt('../../data/SelectionSort/valores_cpp.txt',
                  delimiter=',',
                  unpack=True)
plt.plot(a, b, color="blue", label="BubbleSort")
plt.plot(c, d, color="red", label="CountingSort")
plt.plot(e, f, color="green", label="HeapSort")
plt.plot(g, h, color="cyan", label="InsertionSort")
plt.plot(i, j, color="yellow", label="MergeSort")
plt.plot(k, l, color="black", label="QuickSort")
plt.plot(m, n, color="magenta", label="SelectionSort")
plt.title('Algoritmos Ordenamiento C++')
plt.xlabel('# elementos')
plt.ylabel('tiempo-segundos')
plt.legend()
plt.show()