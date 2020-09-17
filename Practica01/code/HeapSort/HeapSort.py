def heapify(arr, n, i):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2
    if l < n and a[i] < a[l]:
        largest = l

    if r < n and a[largest] < a[r]:
        largest = r

    if largest != i:
        a[i],a[largest] = a[largest],a[i]
        heapify(a, n, largest)

def heapSort(a):
    n = len(a)

    for i in range(n, -1, -1):
        heapify(a, n, i)

    for i in range(n-1, 0, -1):
        a[i], a[0] = a[0], a[i]
        heapify(a, i, 0)

a = [2,7,4,1,5,3]
heapSort(a) 
n = len(a) 
print ("Arreglo Ordenado") 
print (a)
