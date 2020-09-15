import java.io.*;

class InsertionSort
{
    void sort(int a[],int b)
    {
        int n = b;
        for (int i = 1; i < n; ++i)
        {
            int key = a[i];
            int j = i - 1;
            while (j >= 0 && a[j] > key)
            {
                a[j + 1] = a[j];
                j = j - 1;
            }
            a[j + 1] = key;
        }
    }
}