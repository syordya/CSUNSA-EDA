#include <iostream>
#include <chrono>

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
    SelectionSort(arr, n);
    auto end = std::chrono::steady_clock::now();
    // printf("Sorted array: \n");
    // printArray(arr, n);
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << ' ';
  }
  std::cout << '\n';

  return 0;
}
