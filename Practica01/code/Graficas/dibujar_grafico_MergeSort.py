import numpy as np
import cv2
from matplotlib import pyplot as plt

t,a = np.loadtxt('MergeSort/valores_c++.txt',delimiter = ',',unpack = True)
x,y = np.loadtxt('MergeSort/valores_python.txt',delimiter = ',',unpack = True)
m,n = np.loadtxt('MergeSort/valores_java.txt',delimiter = ',',unpack = True)
plt.plot(t,a, color = "blue",label = "C++")
plt.plot(x,y, color = "red",label = "Python")
plt.plot(m,n, color = "green",label = "Java")
plt.title('MergeSort')
plt.xlabel('# elementos')
plt.ylabel('tiempo-segundos')
plt.legend()
plt.show();