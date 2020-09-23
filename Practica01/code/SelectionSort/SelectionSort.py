from sys import stdin
import time

def SelectionSort(A,n):
    for i in range(0,n-1):
        menor = i
        for j in range(i+1, n):
            if A[j] < A[menor]:
                menor = j
        temp = A[i]
        A[i] = A[menor]
        A[menor] = temp

if __name__ == '__main__':
    n = stdin.readline()
    while (n):
        arr = [int(x) for x in stdin.readline().split()]
        start = time.time()
        SelectionSort(arr, len(arr))
        end = time.time()
        #print(arr)
        print(round(end-start, 4), end=' ')
        n = stdin.readline()
    print()
