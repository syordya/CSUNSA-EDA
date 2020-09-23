import java.util.Scanner;

public class SelectionSort {
	static void sort(int A[]) {
		int n = A.length;
		for (int i = 0; i < n - 1; i++) {
			int menor = i;
			for (int j = i + 1; j < n; j++)
				if (A[j] < A[menor])
					// Encontrar el N°menor
					menor = j;
			// intercambiamos con la posicion i el N°menor
			int temp = A[menor];
			A[menor] = A[i];
			A[i] = temp;
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
