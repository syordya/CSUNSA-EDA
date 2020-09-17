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
        output[count[a[i]]] = a[i];
        count[a[i]] -= 1;
    }

    for(int i = 0; i<size; i++)
    {
        a[i] = output[i];
    }
}

int main()
{
  int valores[1000000];
  int val = 10;
  float t0,t1;
  for(int i= 10; i < 1000000;i += val)
  {
    agregar_valor(valores,i);
    t0 = clock();
	  countSort(valores,i);
    t1 = clock();
    float tiempo = ((t1-t0)/CLOCKS_PER_SEC);
    set_data(i,tiempo);
    val *= 2;
  }
  agregar_valor(valores,1000000);
  t0 = clock();
  countSort(valores,1000000);
  t1 = clock();
  float tiempo = ((t1-t0)/CLOCKS_PER_SEC);
  set_data(1000000,tiempo);
}
