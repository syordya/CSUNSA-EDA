#include <iostream>
#include <vector>
using namespace std;

void selectionSort(int a[],int b)
{
    int min_idx;
    int n =  b;
    for (int i = 0; i < n-1; i++)
    {
        min_idx = i;
        for (int j = i+1; j < n; j++)
        {
            if (a[j] < a[min_idx]) min_idx = j;
        }
        int temp = a[min_idx];
        a[min_idx] = a[i];
        a[i] = temp;
    }
}