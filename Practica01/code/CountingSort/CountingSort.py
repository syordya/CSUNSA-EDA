def countSort(a):
    size = len(a)
    output = (size+1) *[0]
    maximo1 = max(a)
    count = (maximo1+1)*[0];

    for i in range(0,maximo1+1):
        count[i] = 0

    for i in range(0,size):
        count[a[i]]= count[a[i]] + 1

    for i in range(1,maximo1+1):
        count[i] += count[i-1]

    for i in range(size-1,-1,-1):
        output[count[a[i]]] = a[i]
        count[a[i]] -= 1

    for i in range(0,size):
        a[i] = output[i];

a = []
intervalo = 1000
for k in range(1000,10000,intervalo):
    lectura(a,k)
    start_time = time()
    countSort(a)
    elapsed_time = time() - start_time
    set_data(len(a),round(float(elapsed_time),4))
    del a[:]
    intervalo *= 2

intervalo = 10000
for k in range(10000,100001,intervalo):
    lectura(a,k)
    start_time = time()
    countSort(a)
    elapsed_time = time() - start_time
    set_data(len(a),round(float(elapsed_time),4))
    del a[:]
