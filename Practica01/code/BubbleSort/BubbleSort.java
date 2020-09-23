import java.util.Scanner;

class BubbleSort {
  static void sort(int[] a) {
    int n = a.length;
    for (int i = 0; i < n; ++i) {
      boolean swapped = false;
      for (int j = 0; j < n - i - 1; ++j) {
        if (a[j] > a[j + 1]) {
          int temp = a[j];
          a[j] = a[j + 1];
          a[j + 1] = temp;
          swapped = true;
        }
      }
      if (!swapped) {
        break;
      }
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
      sort(arr);
      long end = System.nanoTime();
      // print(arr);
      System.out.print((end - start) / 1000000000.0 + " ");
    }
    System.out.println();
    sc.close();
  }
}