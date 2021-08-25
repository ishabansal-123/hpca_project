// Optimize this function
/*void singleThread(int N, int *matA, int *matB, int *output)
{
    // Iterate over first half of output elements
    for(int i = 0; i < N; ++i) {
        int temp = 0;
        // Iterate over diagonal elements
        for(int j = 0; j < i + 1; ++j) {
            int rowA = j;
            int colA = i - j;
            int rowB = i - j;
            int colB = N - j - 1;
            temp += matA[rowA * N + colA] * matB[rowB * N + colB];
        }
        output[i] = temp;
    }
    
    // Iterate over second half of output elements
    for(int i = N; i < 2 * N - 1; ++i) {
        int temp = 0;
        // Iterate over diagonal elements
        for(int j = 0; j < 2 * N - (i + 1); ++j) {
            int rowA = i + 1 + j - N;
            int colA = N - j - 1;
            int rowB = N - j - 1;
            int colB = 2 * N - j - 2 - i;
            temp += matA[rowA * N + colA] * matB[rowB * N + colB];
        }
        output[i] = temp;
    }
}*/
   
void singleThread(int N, int *matA, int *matB, int *output)
{   int B_Size = 64;
    // Iterate over first half of output elements
    for(int i = 0; i < N; i+=B_Size) {
        // Iterate over diagonal elements
        for(int j = 0; j <= i ; j+=B_Size) {
		for(int i1 = i; i1 < i + B_Size; i1++){
			for(int j1 = j; j1 < j + B_Size; j1++){			
           			 int rowA = N-(j1+1);
           			 int colA = i1;
           			 int rowB = i1;
           			 int colB = j1;
   			         output[rowA + colA] += matA[rowA * N + colA] * matB[rowB * N + colB];
    		        }
   		 }
 	 }
   
    }
  // Iterate over second half of output elements
    for(int i = 0; i < N; i+=B_Size) {
        // Iterate over diagonal elements
        for(int j = i+B_Size; j < N; j+=B_Size) {
		for(int i1=i; i1<i+B_Size;i1++){
			for(int j1=j; j1<j+B_Size; j1++){
 				 int rowA = N-(j1+1);;
           			 int colA = i1;
           			 int rowB = i1;
           			 int colB = j1;
        		         output[rowA + rowB] += matA[rowA * N + colA] * matB[rowB * N + colB];
       			 }
     		 }
   	 }
    }
} 
