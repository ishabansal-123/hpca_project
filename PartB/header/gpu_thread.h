#include<stdio.h>
#include<stdlib.h>
#include<cuda.h>
#include<cuda_runtime.h>
using namespace std;

int N;
int *matA;
int *matB;
int *output;

//macro for the length of the vector
#define n 1

//Create other necessary functions here

__global__ void DMM(int N, int *matA, int *matB, int *output){
        int bid1 = blockIdx.x;
        int bid2 = blockIdx.y;
        if(bid1 < n){
    // Iterate over first half of output elements
                 for(int bid1 = 0; bid1 < N; bid1+=16) {
                  // Iterate over diagonal elements
                        if(bid2 < n){
                                 for(int bid2 = 0; bid2 <= bid1 ; bid2+=16) {
                                         for(int i1 = bid1; i1 < bid1 + 16; i1++){
                                                 for(int j1 = bid2; j1 < bid2 + 16; j1++){
                                                         int rowA = N-(j1+1);
                                                         int colA = i1;
                                                         int rowB = i1;
                                                         int colB = j1;
                                                         output[rowA + colA] += matA[rowA * N + colA] * matB[rowB * N + colB];
                        }
                }
          }
       }
    }
  }

        if(bid1 < n){
                //Iterate over second half of the output elements
                 for(int bid1 = 0; bid1 < N; bid1+=16) {
                        //Iterate over diagonal elements
                         if(bid2 < n){
                                 for(int bid2 = bid1+16; bid2<N; bid2+=16){
                                         for(int i1=bid1; i1<bid1+16; i1++){
                                                 for(int j1=bid2; j1<bid2+16; j1++){
                                                        int rowA = N-(j1+1);
                                                        int colA = i1;
                                                        int rowB = i1;
                                                        int colB = j1;
                                                        output[rowA + colA] += matA[rowA * N + colA] * matB[rowB * N + colB];
                                        }
                                }
                         }
          }
        }

     }

}

//Fill in this function

void gpuThread(int N, int *matA, int *matB, int *output)
{

        int *g_matA;
        int *g_matB;
        int *g_output;

        //Allocate memory to device side
        cudaMalloc((void**) &g_matA, N*N*sizeof(int));
        cudaMalloc((void**) &g_matB, N*N*sizeof(int));
        cudaMalloc((void**) &g_output, (2*N-1)*sizeof(int));


        //Coping the data from host to device
        cudaMemcpy(g_matA, matA, N*N*sizeof(int), cudaMemcpyHostToDevice);
        cudaMemcpy(g_matB, matB, N*N*sizeof(int), cudaMemcpyHostToDevice);
        cudaMemcpy(g_output, output, (2*N-1)*sizeof(int), cudaMemcpyHostToDevice);
        DMM<<<n,1>>>(N, g_matA, g_matB, g_output);

        //Coping the output from device to host
        cudaMemcpy(output, g_output, (2*N-1)*sizeof(int), cudaMemcpyDeviceToHost);

	cudaFree(g_matA); 
        cudaFree(g_matB);
        cudaFree(g_output);

}

                                                                                                                   
