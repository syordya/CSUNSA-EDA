## Algoritmos de ordenamiento

### Bubble sort
Comenzando desde el inicio del arreglo, se compara cada par de elementos adyacentes. Si ambos no están ordenados (el segundo es menor que el primero), se intercambian sus posiciones. En cada iteración, un elemento menos necesita ser evaluados (el último), ya que no hay más elementos a su derecha que necesiten ser comparados, puesto que ya están ordenados.

<p align="center">
  <img  src="https://github.com/syordya/CSUNSA-EDA/blob/master/Practica01/images/burbuja.gif">
</p>

### Counting sort
Este algoritmo es único en comparación con los demás, se debe a que no compara elementos mientras los ordena. Funciona en base a teclas numéricas. Para ello, crea una matriz de conteo y luego la usa para determinar la posición correcta de un elemento.

La idea básica del ordenamiento por conteo es determinar, para cada elemento de entrada x , el número de elementos menores que x . Esta información se puede utilizar para colocar directamente en su posición correcta. Por ejemplo, si hay 17 elementos menos que x , entonces x pertenece a la posición de salida 18.
<p align="center">
  <img  src="https://github.com/syordya/CSUNSA-EDA/blob/master/Practica01/images/counting.gif">
</p>

### Heap sort
<p align="center">
  <img  src="https://github.com/syordya/CSUNSA-EDA/blob/master/Practica01/images/heap.gif">
</p>

### Insertion sort
La idea de este algoritmo de ordenación consiste en ir insertando un elemento de la lista ó un arreglo en la parte ordenada de la misma, asumiendo que el primer elemento es la parte ordenada, el algoritmo ira comparando un elemento de la parte desordenada de la lista con los elementos de la parte ordenada, insertando el elemento en la posición correcta dentro de la parte ordenada, y así sucesivamente hasta obtener la lista ordenada.
<p align="center">
  <img  src="https://github.com/syordya/CSUNSA-EDA/blob/master/Practica01/images/insercion.gif">
</p>

### Merge sort

<p align="center">
  <img  src="https://github.com/syordya/CSUNSA-EDA/blob/master/Practica01/images/merge.gif">
</p>

### Quick sort
<p align="center">
  <img  src="https://github.com/syordya/CSUNSA-EDA/blob/master/Practica01/images/quick.gif">
</p>

### Selection sort
En general : 
 - Busca el mínimo elemento entre una posición i y el final de la lista
 - Intercambia el mínimo con el elemento de la posición i
 
 <p align="center">
  <img  src="https://github.com/syordya/CSUNSA-EDA/blob/master/Practica01/images/selection.gif">
</p>

## Enlaces Interesantes(Videos/Paginas)
* Selection sort - [Youtube](https://www.youtube.com/watch?v=GUDLRan2DWM)
* Heap sort - [Youtube](https://www.youtube.com/watch?v=2DmK_H7IdTo)
