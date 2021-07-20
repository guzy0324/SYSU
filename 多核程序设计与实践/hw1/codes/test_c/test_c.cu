#include "../hw1.h"
#include <iostream>
#include <windows.h>
using namespace std;

#define M 1024
#define N 1024
#define BS1 32
#define BS2 32
#define BS 64
#define EPOCHS 128

int main()
{
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);

    int* A_data, ** A, *B_data, ** B, * C_data, ** C;
    cudaMallocManaged((void**)&A_data, sizeof(int) * N * M);
    cudaMallocManaged((void**)&B_data, sizeof(int) * N * M);
    cudaMallocManaged((void**)&C_data, sizeof(int) * N * M);
    cudaMallocManaged((void**)&A, sizeof(int*) * N);
    cudaMallocManaged((void**)&B, sizeof(int*) * N);
    cudaMallocManaged((void**)&C, sizeof(int*) * N);
    init_matrix <<< divup(N, BS2), BS2 >>> (A, A_data, N, M);
    init_matrix <<< divup(N, BS2), BS2 >>> (B, B_data, N, M);
    init_matrix <<< divup(N, BS2), BS2 >>> (C, C_data, N, M);

    for (int k = 1; k <= 4; k += 1)
    {
        init_data <<< divup(N * M, BS1), BS1 >>> (A_data, N, M);
        init_data <<< divup(N * M, BS1), BS1 >>> (B_data, N, M);
        init_data <<< divup(N * M, BS1), BS1 >>> (C_data, N, M);
        cudaDeviceSynchronize();
        QueryPerformanceCounter(&t1);
        for (int i = 0; i < EPOCHS; ++i)
        {
            matrix_add_4 <<< divup(divup(M * N, k), BS), BS >>> (A_data, B_data, C_data, N, M, k);
            cudaDeviceSynchronize();
        }
        QueryPerformanceCounter(&t2);
        cout << k << " elements:" << endl;
        cout << "Correctness: " << check_matrix(A_data, B_data, C_data, N, M) << endl;
        cout << "Efficiency: " << (t2.QuadPart - t1.QuadPart) * 1.0 / EPOCHS / tc.QuadPart << " us" << endl;
        cout << endl;
    }
}
