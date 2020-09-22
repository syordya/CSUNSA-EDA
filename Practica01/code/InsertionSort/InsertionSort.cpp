#include <chrono>
#include <iostream>
#include <vector>

using namespace std;
//HOLA PRUEBA
void insertionSort(int a[],int b)
{
    int n = b;
    for (int i = 1; i < n; i++)
    {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
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
    insertionSort(arr, n);
    auto end = std::chrono::steady_clock::now();
    // printf("Sorted array: \n");
    // printArray(arr, n);
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << ' ';
  }
  std::cout << '\n';

  return 0;
}
