import java.io.*;

class CountingSort
{
    public void sort(int a[],int b)
    {
        int size = b;
        int[] output = new int[size+1];
        int max = getMax(a,b);
        int[] count = new int[max+1];

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

    int getMax(int a[],int b)
    {
       int max = a[0];
       for(int i = 1; i<b; i++)
       {
          if(a[i] > max) max = a[i];
       }
       return max;
    }
    
    public static void main(String args[])
    {
      int[] numeros = new int[1000001];
      CountingSort ob = new CountingSort();
      int valor =0;
      int val = 1000;
      ob.sort(numeros,valor);
    }
}
