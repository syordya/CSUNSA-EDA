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
