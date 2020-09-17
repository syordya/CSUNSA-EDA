#include <iostream>
using namespace std;


void SelectionSort(int A[],int tam){
    for (int i = 0; i < tam; i++) {
        int menor = i;
        for (int j = i + 1; j < tam; j++) {
            if (A[j] < A[menor]) {
            	//Encontrar el N°menor
                menor = j;     
            }
        }
        //intercambiamos con la posicion i el N°menor
        int temp = A[i];
        A[i] = A[menor];
        A[menor] = temp;
    }	
}
int main() {
    int A[]={2,7,4,1,5,3};
    int tam=6;
    SelectionSort(A,tam);
    cout << "\nArreglo Ordenado : ";
    for (int i = 0; i < 6; i++) {
        cout << A[i] << "\t";
    }
}
