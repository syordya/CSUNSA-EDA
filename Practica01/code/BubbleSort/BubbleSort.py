from sys import stdin
import time


def bubbleSort(a):
    n = len(a)
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            if a[j] > a[j + 1]:
                temp = a[j]
                a[j] = a[j + 1]
                a[j + 1] = temp
                swapped = True
        if not swapped:
            break


if __name__ == '__main__':
    n = stdin.readline()
    while (n):
        arr = [int(x) for x in stdin.readline().split()]
        start = time.time()
        bubbleSort(arr)
        end = time.time()
        #print(arr)
        print(round(end - start, 4), end=' ')
        n = stdin.readline()
    print()
