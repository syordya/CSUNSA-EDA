#include <iostream>
#include <chrono>

using namespace std; 


void heapify(int A[], int n, int i){ 
	int mayor = i;  
	int l = 2*i + 1; // IZQ = 2*i + 1 
	int r = 2*i + 2; // DER = 2*i + 2 

	// Si el hijo izquierdo es más grande que la raíz
	if (l < n && A[l] > A[mayor]) 
		mayor = l; 

	// Si el hijo derecho es mayor que el mayor hasta ahora
	if (r < n && A[r] > A[mayor]) 
		mayor = r; 

	if (mayor != i){ 
		swap(A[i], A[mayor]); 
		heapify(A, n, mayor); 
	} 
} 


void heapSort(int A[], int n) { 
	//Debe construirse un montIculo inicial
	for (int i = n / 2 - 1; i >= 0; i--) 
		heapify(A, n, i); 
	// Uno por uno extrae un elemento del montón 
	for (int i=n-1; i>0; i--){ 
		// Mover la raíz actual al final
		swap(A[0], A[i]); 
		// Reconstruir el montículo con los elementos 
		heapify(A, i, 0); 
	} 
} 

void printArray(int a[], int n) {
  for (int i = 0; i < n; ++i) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

int main() {
  int n = 0;
  while (std::cin >> n) {
    int arr[n] = {0};
    for (int i = 0; i < n; ++i) {
      std::cin >> *(arr + i);
    }
    auto start = std::chrono::steady_clock::now();
    heapSort(arr, n);
    auto end = std::chrono::steady_clock::now();
    // printf("Sorted array: \n");
    // printArray(arr, n);
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << ' ';
  }
  std::cout << '\n';

  return 0;
}