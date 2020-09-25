import numpy as np
from matplotlib import pyplot as plt

t, a = np.loadtxt('../../data/BubbleSort/valores_cpp.txt',
                  delimiter=',',
                  unpack=True)
x, y = np.loadtxt('../../data/BubbleSort/valores_python.txt',
                  delimiter=',',
                  unpack=True)
m, n = np.loadtxt('../../data/BubbleSort/valores_java.txt',
                  delimiter=',',
                  unpack=True)
plt.plot(t, a, color="blue", label="C++")
plt.plot(x, y, color="red", label="Python")
plt.plot(m, n, color="green", label="Java")
plt.title('BubbleSort')
plt.xlabel('# elementos')
plt.ylabel('tiempo-segundos')
plt.legend()
plt.show()