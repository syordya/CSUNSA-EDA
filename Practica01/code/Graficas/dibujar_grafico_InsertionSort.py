import numpy as np
import cv2
from matplotlib import pyplot as plt

t,a = np.loadtxt('InsertionSort/valores_c++.txt',delimiter = ',',unpack = True)
x,y = np.loadtxt('InsertionSort/valores_python.txt',delimiter = ',',unpack = True)
m,n = np.loadtxt('InsertionSort/valores_java.txt',delimiter = ',',unpack = True)
plt.plot(t,a, color = "blue",label = "C++")
plt.plot(x,y, color = "red",label = "Python")
plt.plot(m,n, color = "green",label = "Java")
plt.title('InsertionSort')
plt.xlabel('# elementos')
plt.ylabel('tiempo-segundos')
plt.legend()
plt.show();