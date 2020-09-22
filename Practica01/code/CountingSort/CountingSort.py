from sys import stdin
import time

def countSort(a):
    size = len(a)
    output = (size+1) *[0]
    maximo1 = max(a)
    count = (maximo1+1)*[0]

    for i in range(0,maximo1+1):
        count[i] = 0

    for i in range(0,size):
        count[a[i]]= count[a[i]] + 1

    for i in range(1,maximo1+1):
        count[i] += count[i-1]

    for i in range(size-1,-1,-1):
        output[count[a[i]]-1] = a[i]
        count[a[i]] -= 1

    for i in range(0,size):
        a[i] = output[i]

if __name__ == '__main__':
    n = stdin.readline()
    while (n):
        arr = [int(x) for x in stdin.readline().split()]
        start = time.time()
        countSort(arr)
        end = time.time()
        #print(arr)
        print(round(end-start, 4), end=' ')
        n = stdin.readline()
    print()
