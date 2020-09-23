from sys import stdin
import time

def insertionSort(a):

    for i in range(1, len(a)):
        key = a[i]
        j = i-1
        while j >= 0 and key < a[j]:
            a[j + 1] = a[j]
            j -= 1
        a[j + 1] = key

if __name__ == '__main__':
    n = stdin.readline()
    while (n):
        arr = [int(x) for x in stdin.readline().split()]
        start = time.time()
        insertionSort(arr)
        end = time.time()
        #print(arr)
        print(round(end-start, 4), end=' ')
        n = stdin.readline()
    print()