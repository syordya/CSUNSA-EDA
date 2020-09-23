import java.util.Scanner;

class InsertionSort {
  static void sort(int a[]) {
    int n = a.length;
    for (int i = 1; i < n; ++i) {
      int key = a[i];
      int j = i - 1;
      while (j >= 0 && a[j] > key) {
        a[j + 1] = a[j];
        j = j - 1;
      }
      a[j + 1] = key;
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