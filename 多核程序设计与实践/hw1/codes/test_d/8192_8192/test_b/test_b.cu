#include "../../../hw1.h"
#include <iostream>
#include <windows.h>
using namespace std;

#define M 8192
#define N 8192
#define BS1 32
#define BS2 32
#define EPOCHS 128

int BS[] = {16, 32, 63, 64, 65, 128};

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

    for (int BS_i = 0; BS_i < sizeof(BS) / sizeof(int); ++BS_i)
    {
        init_data <<< divup(N * M, BS1), BS1 >>> (A_data, N, M);
        init_data <<< divup(N * M, BS1), BS1 >>> (B_data, N, M);
        init_data <<< divup(N * M, BS1), BS1 >>> (C_data, N, M);
        cudaDeviceSynchronize();
        QueryPerformanceCounter(&t1);
        for (int i = 0; i < EPOCHS; ++i)
        {
            matrix_add_3 <<< divup(M * N, BS[BS_i]), BS[BS_i] >>> (A_data, B_data, C_data, N, M);
            cudaDeviceSynchronize();
        }
        QueryPerformanceCounter(&t2);
        cout << "Block size: " << BS[BS_i] << endl;
        cout << "Correctness: " << check_matrix(A_data, B_data, C_data, N, M) << endl;
        cout << "Efficiency: " << (t2.QuadPart - t1.QuadPart) * 1.0 / EPOCHS / tc.QuadPart << " us" << endl;
        cout << endl;
    }
}
