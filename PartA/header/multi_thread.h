#include <pthread.h>
#include <vector>
using namespace std;
int threads =400;
int N;
int *matA;
int *matB;
int cr = 0;

struct Thread{
	int threadid;
	int* a;
};
// Create other necessary functions here
void* execution(void* pass)
{
	int core = cr++;
	int B_Size=64;
	struct Thread *f = (struct Thread*) pass;
	(f->a) = (int*)malloc((2*N-1)*sizeof(int)); 
	for(int i = 0; i < N; i+=B_Size) {
        // Iterate over diagonal elements
       		 for(int j = 0; j <= i ; j+=B_Size) {
			//Assigning each thread a core 
		       	if((i+j)%(cr++*(N/threads))==f->threadid){
               			 for(int i1 = i; i1 < i + B_Size; i1++){
                       			 for(int j1 = j; j1 < j + B_Size; j1++){
                                		 int rowA = N-(j1+1);
                                		 int colA = i1;
                                		 int rowB = i1;
                                		 int colB = j1;
           					 (f->a)[rowA + colA] += matA[rowA * N + colA] * matB[rowB * N + colB];
					}
       				 }
   			 }
 		 }

	}
     // Iterate over second half of output elements
     for(int i = 0; i < N; i+=B_Size) {
        // Iterate over diagonal elements
        for(int j = i+B_Size; j < N; j+=B_Size) {
		//Assigning each thread a core
		if((i+j)%(cr++*(N/threads))==f->threadid){
               		 for(int i1=i; i1<i+B_Size;i1++){
                       		 for(int j1=j; j1<j+B_Size; j1++)
                                   {
                                	 int rowA = N-(j1+1);
                                	 int colA = i1;
                                	 int rowB = i1;
                                	 int colB = j1;
           				 (f->a)[rowA + colA] += matA[rowA * N + colA] * matB[rowB * N + colB];
                                   }
       			 }
     		 }
   	 }
   }
 pthread_exit(0);

}
 
		

// Fill in this function
void multiThread(int N, int *matA, int *matB, int *output)
{
	::N = N;
	::matA = matA;
	::matB = matB;
	struct Thread u[threads];
	//declaring the threads
	pthread_t tno[threads]; 
	//creating the threads,and each performing its part
	for(int i = 0; i < threads; i++){
		u[i].threadid = i;
		pthread_create(&tno[i],NULL,execution,&u[i]);
        }  
	//joining and aiting for other threads to complete
	for(int i = 0; i<threads; i++){
		pthread_join(tno[i],NULL);
	//displaying the result of output array
	for(int k = 0; k<2*N-1;k++){
		output[k] += u[i].a[k];
        }
        }
}
