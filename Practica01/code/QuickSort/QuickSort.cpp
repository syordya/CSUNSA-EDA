#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

void swap(int &a,int &b)
{
    int temp = b;
    b = a;
    a = temp;
}

int partition (int a[], int low, int high)
{
    int pivot = a[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return (i + 1);
}

void quickSort(int a[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
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
    quickSort(arr, 0, n - 1);
    auto end = std::chrono::steady_clock::now();
    // printf("Sorted array: \n");
    // printArray(arr, n);
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << ' ';
  }
  std::cout << '\n';

  return 0;
}