# include "entropy.h"
# include <iostream>
# include <windows.h>
using namespace std;

# define M (2048)
# define N (2048)
# define SEED (0)
# define EPOCHS (100)

int in_host[M * N];
float out_host[M * N];

int main()
{
    init_data(in_host, M, N, SEED);
    int** in, * in_data;
    float** out, * out_data;
    cudaMalloc((void**)&in_data, sizeof(in_host));
    cudaMalloc((void**)&in, sizeof(int*) * M);
    cudaMalloc((void**)&out_data, sizeof(out_host));
    cudaMalloc((void**)&out, sizeof(float*) * M);
    init_matrix<int><<<divup(M, 64), 64>>>(in, in_data, M, N);
    init_matrix<float><<<divup(M, 64), 64>>>(out, out_data, M, N);
    cudaMemcpy(in_data, in_host, sizeof(in_host), cudaMemcpyHostToDevice);
    dim3 block(BDIM_X, BDIM_Y, 1);
    dim3 grid(divup(N, BDIM_X), divup(M, BDIM_Y), 1);
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);

    cout << "M x N: " << M << " x " << N << endl;
    cout << "BlockDim = " << BDIM_Y << " x " << BDIM_X << endl << endl;

    QueryPerformanceCounter(&t1);
    for (int i = 0; i < EPOCHS; ++i)
    {
        entropy <<< grid, block >>> (out, in, M, N);
        cudaDeviceSynchronize();
    }
	QueryPerformanceCounter(&t2);
    cudaMemcpy(out_host, out_data, sizeof(out_host), cudaMemcpyDeviceToHost);
    cout << "Baseline:" << endl;
    cout << "Correctness: " << check_result(out_host, in_host, M, N) << endl;
    cout << "Efficiency: " << (t2.QuadPart - t1.QuadPart) * 1.0 / EPOCHS / tc.QuadPart << " us" << endl;
    cout << endl;

    bind_texture(in_data, M, N);
    QueryPerformanceCounter(&t1);
    for (int i = 0; i < EPOCHS; ++i)
    {
        entropy_texture <<< grid, block >>> (out, M, N);
        cudaDeviceSynchronize();
    }
	QueryPerformanceCounter(&t2);
    cudaMemcpy(out_host, out_data, sizeof(out_host), cudaMemcpyDeviceToHost);
    cudaUnbindTexture(tex);
    cout << "Texture memory:" << endl;
    cout << "Correctness: " << check_result(out_host, in_host, M, N) << endl;
    cout << "Efficiency: " << (t2.QuadPart - t1.QuadPart) * 1.0 / EPOCHS / tc.QuadPart << " us" << endl;
    cout << endl;

    QueryPerformanceCounter(&t1);
    for (int i = 0; i < EPOCHS; ++i)
    {
        entropy_shared <<< grid, block >>> (out, in, M, N);
        cudaDeviceSynchronize();
    }
	QueryPerformanceCounter(&t2);
    cudaMemcpy(out_host, out_data, sizeof(out_host), cudaMemcpyDeviceToHost);
    cout << "Shared memory:" << endl;
    cout << "Correctness: " << check_result(out_host, in_host, M, N) << endl;
    cout << "Efficiency: " << (t2.QuadPart - t1.QuadPart) * 1.0 / EPOCHS / tc.QuadPart << " us" << endl;
    cout << endl;

    QueryPerformanceCounter(&t1);
    for (int i = 0; i < EPOCHS; ++i)
    {
        entropy_shared_log <<< grid, block >>> (out, in, M, N);
        cudaDeviceSynchronize();
    }
	QueryPerformanceCounter(&t2);
    cudaMemcpy(out_host, out_data, sizeof(out_host), cudaMemcpyDeviceToHost);
    cout << "Shared memory with log table:" << endl;
    cout << "Correctness: " << check_result(out_host, in_host, M, N) << endl;
    cout << "Efficiency: " << (t2.QuadPart - t1.QuadPart) * 1.0 / EPOCHS / tc.QuadPart << " us" << endl;
    cout << endl;

    QueryPerformanceCounter(&t1);
    for (int i = 0; i < EPOCHS; ++i)
    {
        entropy_shared_log_ldg <<< grid, block >>> (out, in, M, N);
        cudaDeviceSynchronize();
    }
	QueryPerformanceCounter(&t2);
    cudaMemcpy(out_host, out_data, sizeof(out_host), cudaMemcpyDeviceToHost);
    cout << "Shared memory with log table accessed through read-only memory:" << endl;
    cout << "Correctness: " << check_result(out_host, in_host, M, N) << endl;
    cout << "Efficiency: " << (t2.QuadPart - t1.QuadPart) * 1.0 / EPOCHS / tc.QuadPart << " us" << endl;
    cout << endl;

    QueryPerformanceCounter(&t1);
    for (int i = 0; i < EPOCHS; ++i)
    {
        entropy_shared_log_shared <<< grid, block >>> (out, in, M, N);
        cudaDeviceSynchronize();
    }
	QueryPerformanceCounter(&t2);
    cudaMemcpy(out_host, out_data, sizeof(out_host), cudaMemcpyDeviceToHost);
    cout << "Shared memory with log table accessed through shared memory:" << endl;
    cout << "Correctness: " << check_result(out_host, in_host, M, N) << endl;
    cout << "Efficiency: " << (t2.QuadPart - t1.QuadPart) * 1.0 / EPOCHS / tc.QuadPart << " us" << endl;
    cout << endl;
}
