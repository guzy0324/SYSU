#include "omp.h"
#include <iostream>
#include <windows.h>
using namespace std;

#define M 8192
#define N 8192
#define NUM_THREADS 4
#define NUM_LOOP 4
#define EPOCHS 128

int n[] = {1000, 1024, 8192};
int m[] = {1000, 1024, 8192};

inline int divup(int A, int B)
{
    return A % B ? A / B + 1 : A / B;
}

int main()
{
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);

    int* A_data = (int*)malloc(sizeof(int) * N * M);
    int* B_data = (int*)malloc(sizeof(int) * N * M);
    int* C_data = (int*)malloc(sizeof(int) * N * M);

    int BS = divup(N * M, NUM_LOOP);
    for (int shape_i = 0; shape_i < sizeof(n) / sizeof(int); ++shape_i)
    {
        QueryPerformanceCounter(&t1);
        for (int epoch = 0; epoch < EPOCHS; ++epoch)
        {
            #pragma parallel omp for num_threads(NUM_THREADS)
            for (int i = 0; i < NUM_LOOP; ++i)
            {
                for (long long j = i * BS; j < n[shape_i] * m[shape_i] && j < (i + 1) * BS; ++j)
                {
                    C_data[j] = A_data[j] + B_data[j];
                }
            }
        }
        QueryPerformanceCounter(&t2);
        cout << "Shape: " << n[shape_i] << " x " << m[shape_i] << endl;
        cout << "Efficiency: " << (t2.QuadPart - t1.QuadPart) * 1.0 / EPOCHS / tc.QuadPart << " us" << endl;
        cout << endl;
    }
}
