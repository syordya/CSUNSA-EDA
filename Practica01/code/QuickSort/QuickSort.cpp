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

void printArray(int a[], int size) 
{ 
	int i; 
	for (i = 0; i < size; i++) 
		printf("%d ", a[i]); 
	printf("\n"); 
} 


int main() 
{ 
	int arr[] = { 5, 9, 8, 2, 6 }; 
	int n = sizeof(arr) / sizeof(arr[0]); 
	quickSort(arr, 0, n - 1); 
	printf("Sorted array: \n"); 
	printArray(arr, n); 
    
	return 0; 
} 