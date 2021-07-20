#include "../hw1.h"
#include <iostream>
#include <windows.h>
using namespace std;

#define M 1024
#define N 1024
#define BS1 32
#define BS2 32
#define W 8
#define H 8
#define EPOCHS 128

int main()
{
    dim3 block_2d(W, H, 1);
    dim3 grid_2d(divup(M, W), divup(N, H), 1);
    dim3 block_1d(W * H, 1);
    dim3 grid_1d(divup(M * N, W * H), 1, 1);

	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);

    int* A_data, ** A, *B_data, ** B, * C_data, ** C;
    cudaMalloc((void**)&A_data, sizeof(int) * N * M);
    cudaMalloc((void**)&B_data, sizeof(int) * N * M);
    cudaMalloc((void**)&C_data, sizeof(int) * N * M);
    cudaMalloc((void**)&A, sizeof(int*) * N);
    cudaMalloc((void**)&B, sizeof(int*) * N);
    cudaMalloc((void**)&C, sizeof(int*) * N);
    init_matrix <<< divup(N, BS2), BS2 >>> (A, A_data, N, M);
    init_matrix <<< divup(N, BS2), BS2 >>> (B, B_data, N, M);
    init_matrix <<< divup(N, BS2), BS2 >>> (C, C_data, N, M);

    init_data <<< divup(N * M, BS1), BS1 >>> (A_data, N, M);
    init_data <<< divup(N * M, BS1), BS1 >>> (B_data, N, M);
    init_data <<< divup(N * M, BS1), BS1 >>> (C_data, N, M);
    cudaDeviceSynchronize();
	QueryPerformanceCounter(&t1);
    for (int i = 0; i < EPOCHS; ++i)
    {
		matrix_add_1 <<< grid_2d, block_2d >>> (A, B, C, N, M);
        cudaDeviceSynchronize();
    }
	QueryPerformanceCounter(&t2);
    cout << "2D array with 2D grid and block:" << endl;
    cout << "Correctness: " << check_matrix(A_data, B_data, C_data, N, M) << endl;
    cout << "Efficiency: " << (t2.QuadPart - t1.QuadPart) * 1.0 / EPOCHS / tc.QuadPart << " us" << endl;
    cout << endl;

    init_data <<< divup(N * M, BS1), BS1 >>> (A_data, N, M);
    init_data <<< divup(N * M, BS1), BS1 >>> (B_data, N, M);
    init_data <<< divup(N * M, BS1), BS1 >>> (C_data, N, M);
    cudaDeviceSynchronize();
	QueryPerformanceCounter(&t1);
    for (int i = 0; i < EPOCHS; ++i)
    {
        matrix_add_2 <<< grid_2d, block_2d >>> (A_data, B_data, C_data, N, M);
        cudaDeviceSynchronize();
    }
	QueryPerformanceCounter(&t2);
    cout << "1D array with 2D grid and block:" << endl;
    cout << "Correctness: " << check_matrix(A_data, B_data, C_data, N, M) << endl;
    cout << "Efficiency: " << (t2.QuadPart - t1.QuadPart) * 1.0 / EPOCHS / tc.QuadPart << " us" << endl;
    cout << endl;

    init_data <<< divup(N * M, BS1), BS1 >>> (A_data, N, M);
    init_data <<< divup(N * M, BS1), BS1 >>> (B_data, N, M);
    init_data <<< divup(N * M, BS1), BS1 >>> (C_data, N, M);
    cudaDeviceSynchronize();
	QueryPerformanceCounter(&t1);
    for (int i = 0; i < EPOCHS; ++i)
    {
        matrix_add_3 <<< grid_1d, block_1d >>> (A_data, B_data, C_data, N, M);
        cudaDeviceSynchronize();
    }
	QueryPerformanceCounter(&t2);
    cout << "1D array with 1D grid and block:" << endl;
    cout << "Correctness: " << check_matrix(A_data, B_data, C_data, N, M) << endl;
    cout << "Efficiency: " << (t2.QuadPart - t1.QuadPart) * 1.0 / EPOCHS / tc.QuadPart << " us" << endl;
    cout << endl;
}
