#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int getMax(int a[],int b)
{
   int max = a[0];
   for(int i = 1; i<b; i++)
   {
      if(a[i] > max) max = a[i];
   }
   return max;
}

void countSort(int a[],int b)
{
    int size = b;
    int output[size];
    int max = getMax(a,size);
    int count[max+1];

    for(int i = 0; i<max+1; i++) count[i] = 0;
    for(int i = 0; i <size; i++) count[a[i]]++;
    for(int i = 1; i<max+1; i++) count[i] += count[i-1];

    for(int i = size-1; i>=0; i--)
    {
        output[count[a[i]]-1] = a[i];
        count[a[i]] -= 1;
    }

    for(int i = 0; i<size; i++)
    {
        a[i] = output[i];
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
    countSort(arr, n);
    auto end = std::chrono::steady_clock::now();
    // printf("Sorted array: \n");
    // printArray(arr, n);
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << ' ';
  }
  std::cout << '\n';

  return 0;
}
