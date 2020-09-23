import java.util.Scanner;

class CountingSort {
  static void sort(int a[]) {
    int n = a.length;
    int max = getMax(a);
    int[] output = new int[n + 1];
    int[] count = new int[max + 1];

    for (int i = 0; i < max + 1; i++)
      count[i] = 0;
    for (int i = 0; i < n; i++)
      count[a[i]]++;
    for (int i = 1; i < max + 1; i++)
      count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
      output[count[a[i]] - 1] = a[i];
      count[a[i]] -= 1;
    }

    for (int i = 0; i < n; i++) {
      a[i] = output[i];
    }
  }

  static void print(int[] a) {
    for (int i = 1; i < a.length; ++i) {
      System.out.print(a[i] + " ");
    }
    System.out.println();
  }

  static int getMax(int a[]) {
    int n = a.length;
    int max = a[0];
    for (int i = 1; i < n; i++) {
      if (a[i] > max)
        max = a[i];
    }
    return max;
  }

  public static void main(String args[]) {
    Scanner sc = new Scanner(System.in);
    while (sc.hasNextInt()) {
      int n = sc.nextInt();
      int[] arr = new int[n + 1];
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
