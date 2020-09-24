import numpy as np
from matplotlib import pyplot as plt

a,b = np.loadtxt('BubbleSort/valores_c++.txt',delimiter = ',',unpack = True)
c,d = np.loadtxt('CountingSort/valores_c++.txt',delimiter = ',',unpack = True)
e,f = np.loadtxt('HeapSort/valores_c++.txt',delimiter = ',',unpack = True)
g,h = np.loadtxt('InsertionSort/valores_c++.txt',delimiter = ',',unpack = True)
i,j = np.loadtxt('MergeSort/valores_c++.txt',delimiter = ',',unpack = True)
k,l = np.loadtxt('QuickSort/valores_c++.txt',delimiter = ',',unpack = True)
m,n = np.loadtxt('SelectionSort/valores_c++.txt',delimiter = ',',unpack = True)
plt.plot(a,b, color = "blue",label = "BubbleSort")
plt.plot(c,d, color = "red",label = "CountingSort")
plt.plot(e,f, color = "green",label = "HeapSort")
plt.plot(g,h, color = "cyan",label = "InsertionSort")
plt.plot(i,j, color = "yellow",label = "MergeSort")
plt.plot(k,l, color = "black",label = "QuickSort")
plt.plot(m,n, color = "magenta",label = "SelectionSort")
plt.title('Algoritmos Ordenamiento C++')
plt.xlabel('# elementos')
plt.ylabel('tiempo-segundos')
plt.legend()
plt.show();