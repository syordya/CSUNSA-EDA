#include <iostream>
#include <vector>
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

// Function to print an array
void printArray(int array[], int size) {
  for (int i = 0; i < size; i++)
    cout << array[i] << " ";
  cout << endl;
}

// Driver code
int main() {
  int array[] = {4, 2, 2, 8, 3, 3, 1};
  int n = sizeof(array) / sizeof(array[0]);
  countSort(array, n);
  printArray(array, n);
}