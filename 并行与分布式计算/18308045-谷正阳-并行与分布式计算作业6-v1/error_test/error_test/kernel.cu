#include "error_checks.h" // Macros CUDA_CHECK and CHECK_ERROR_MSG
#include <cmath>
#include <cstdio>
#include <dos.h>

__global__ void vector_add(double *C, const double *A, const double *B, int N)
{
    // Add the kernel code
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    /*if (idx == N - 1)
    {
		for (int i = 0; i < 1000; i++);
    }*/
    // Do not try to access past the allocated memory
    if (idx < N)
    {
        C[idx] = A[idx] + B[idx];
    }
}

int main(void)
{
    const int N = 20;
    const int ThreadsInBlock = 128;
    //const int ThreadsInBlock = 1024;
    //const int ThreadsInBlock = 1025;
    double *dA, *dB, *dC;
    double hA[N], hB[N], hC[N];

    for (int i = 0; i < N; ++i)
    {
        hA[i] = (double)i;
        hB[i] = (double)i * i;
    }

    /* 
    Add memory allocations and copies. Wrap your runtime function
    calls with CUDA_CHECK( ) macro
    */
    CUDA_CHECK(cudaMalloc((void **)&dA, sizeof(double) * N));
    CUDA_CHECK(cudaMalloc((void **)&dB, sizeof(double) * N));
    CUDA_CHECK(cudaMalloc((void **)&dC, sizeof(double) * N));
    CUDA_CHECK(cudaMemcpy((void *)dA, (void *)hA, N * sizeof(double), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy((void *)dB, (void *)hB, N * sizeof(double), cudaMemcpyHostToDevice));
    /*cudaMalloc((void **)&dA, sizeof(double) * N);
    cudaMalloc((void **)&dB, sizeof(double) * N);
    cudaMalloc((void **)&dC, sizeof(double) * N);
    cudaMemcpy((void *)dA, (void *)hA, N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy((void *)dB, (void *)hB, N * sizeof(double), cudaMemcpyHostToDevice);*/
    //printf("%f", *dA);

    // Note the maximum size of threads in a block
    dim3 grid, threads;

    //// Add the kernel call here
    vector_add<<<N / ThreadsInBlock + 1, ThreadsInBlock>>>(dC, dA, dB, N);
    //vector_add<<<N / ThreadsInBlock + 1, ThreadsInBlock>>>(hC, hA, hB, N);

    // Here we add an explicit synchronization so that we catch errors
    // as early as possible. Don't do this in production code!
    cudaDeviceSynchronize();
    CHECK_ERROR_MSG("vector_add kernel");

    //// Copy back the results and free the device memory
    CUDA_CHECK(cudaMemcpy((void *)hC, (void *)dC, N * sizeof(double), cudaMemcpyDeviceToHost));
    CUDA_CHECK(cudaFree((void *)dA));
    CUDA_CHECK(cudaFree((void *)dB));
    CUDA_CHECK(cudaFree((void *)dC));
    /*cudaMemcpy((void *)hC, (void *)dC, N * sizeof(double), cudaMemcpyDeviceToHost);
    cudaFree((void *)dA);
    cudaFree((void *)dB);
    cudaFree((void *)dC);*/

    for (int i = 0; i < N; i++)
        printf("%5.1f\n", hC[i]);

    return 0;
}