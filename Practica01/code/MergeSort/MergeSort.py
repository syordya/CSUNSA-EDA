def merge(L, R):
    i = 0
    j = 0
    ret = []
    while i < len(L) and j < len(R):
        if(L[i]<R[j]):
          ret.append(L[i])
          i=i+1
        else:
          ret.append(R[j])
          j=j+1

    ret += L[i:]
    ret += R[j:]
    return ret

def mergeSort(A):

    n = len(A)
    if n <= 1:
        return A
    L = mergeSort(A[:n // 2])
    R = mergeSort(A[n // 2:n])
    return merge(L,R)