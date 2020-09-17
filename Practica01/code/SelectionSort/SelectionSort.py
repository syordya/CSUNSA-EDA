def SelectionSort(A,n):
    for i in range(0,n-1):
        menor = i
        for j in range(i+1, n):
            if A[j] < A[menor]:
                menor = j
        temp = A[i]
        A[i] = A[menor]
        A[menor] = temp

A = [2,7,4,1,5,3]
n = 6
print ("Arreglo Ordenado")
SelectionSort(A,n)
print (A)  
