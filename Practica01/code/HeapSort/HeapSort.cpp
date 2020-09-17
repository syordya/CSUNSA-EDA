#include <iostream> 

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


int main(){ 
	int A[]={2,7,4,1,5,3};
	int n = 6; 

	heapSort(A, n); 

	cout << "Arreglo Ordenado \n"; 
    for (int i = 0; i < n; i++) {
        cout << A[i] << "\t";
    }
} 
