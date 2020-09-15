import java.io.*;

class BubbleSort
{
    static void sort(int[] a,int b)
    {
        int temp,tamanho;
        tamanho = b;
        boolean swapped;
        for (int i = 0; i < tamanho - 1; i++)
        {
            swapped = false;
            for (int j = 0; j < tamanho - i - 1; j++)
            {
                if (a[j] > a[j + 1])
                {
                    temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                    swapped = true;
                }
            }
            if (swapped == false)
                break;
        }
    }
}