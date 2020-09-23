from sys import stdin
import time

def partition(a,low,high):
    i = ( low-1 )
    pivot = a[high]

    for j in range(low , high):
        if a[j] < pivot:
            i = i+1
            a[i],a[j] = a[j],a[i]

    a[i+1],a[high] = a[high],a[i+1]
    return ( i+1 )

def quickSort(a,low,high):
    if low < high:
        pi = partition(a,low,high)
        quickSort(a, low, pi-1)
        quickSort(a, pi+1, high)

if __name__ == '__main__':
    n = stdin.readline()
    while (n):
        arr = [int(x) for x in stdin.readline().split()]
        start = time.time()
        quickSort(arr, 0, len(arr) - 1)
        end = time.time()
        #print(arr)
        print(round(end-start, 4), end=' ')
        n = stdin.readline()
    print()