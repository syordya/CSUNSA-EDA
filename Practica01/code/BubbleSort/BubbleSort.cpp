#include <iostream>
#include <vector>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort(int a[],int b)
{
    int tamanho = b;
  	bool swapped;
    for (int i = 0; i < tamanho-1; i++)
    {
    	swapped = false;
    	for (int j = 0; j < tamanho-i-1; j++)
    	{
    		if (a[j] > a[j+1])
    		{
    			swap(a[j], a[j+1]);
    			swapped = true;
    		}
    	}
    	if(!swapped) break;
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
	bubbleSort(arr, n); 
	printf("Sorted array: \n"); 
	printArray(arr, n); 
    
	return 0; 
} 
