import java.io.*;

public class SelectionSort 
{ 
	void sort(int A[],int n) 
	{ 
		for (int i = 0; i < n-1; i++) 
		{ 
			int menor = i; 
			for (int j = i+1; j < n; j++) 
				if (A[j] < A[menor]) 
                    //Encontrar el N°menor
					menor = j;  
            //intercambiamos con la posicion i el N°menor
			int temp = A[menor]; 
			A[menor] = A[i]; 
			A[i] = temp; 
		} 
	} 

	public static void main(String args[]) 
	{ 
		SelectionSort ob = new SelectionSort(); 
		int A[]={2,7,4,1,5,3};
		int tam =6;
		ob.sort(A,tam); 
		System.out.println("Arreglo Ordenado : "); 
		for (int i=0; i<tam; ++i) 
			System.out.print(A[i]+" ");
		System.out.println();	
	} 
} 
