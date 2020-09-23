import java.util.Scanner;

class QuickSort {
  static int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
      if (a[j] < pivot) {
        i++;
        // swap
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
      }
    }
    // swap
    int temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;

    return i + 1;
  }

  static void sort(int a[], int low, int high) {
    if (low < high) {
      int pi = partition(a, low, high);
      sort(a, low, pi - 1);
      sort(a, pi + 1, high);
    }
  }

  static void print(int[] a) {
    for (int i = 0; i < a.length; ++i) {
      System.out.print(a[i] + " ");
    }
    System.out.println();
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    while (sc.hasNextInt()) {
      int n = sc.nextInt();
      int[] arr = new int[n];
      for (int i = 0; i < n; ++i) {
        int x = sc.nextInt();
        arr[i] = x;
      }
      long start = System.nanoTime();
      sort(arr, 0, n - 1);
      long end = System.nanoTime();
      // print(arr);
      System.out.print((end - start) / 1000000000.0 + " ");
    }
    System.out.println();
    sc.close();
  }
}