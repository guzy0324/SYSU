# include "omp.h"
# include <iostream>
# include <windows.h>

using namespace std;

inline int min(int a, int b)
{
    return a < b ? a : b;
}

# include "utils.h"

# define M (2048)
# define N (2048)
# define SEED (0)
# define EPOCHS (10)

int in[M * N];
float out[M * N];

/*
函数：test

函数描述：完成一次测试，包括计算熵，记录平均时间，检查结果是否正确

参数描述：
num_loops：用于parallel for的循环数量
num_threads：线程数
m：矩阵行数
n：矩阵列数
*/
void test(int num_loops, int num_threads, int m = M, int n = N)
{
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
    int BS = divup(N * M, num_loops);
    QueryPerformanceCounter(&t1);
    for (int i = 0; i < EPOCHS; ++i)
    {
        #pragma parallel omp for num_threads(NUM_THREADS)
        for (int j = 0; j < num_loops; ++j)
        {
            int next = (j + 1) * BS;
            for (int ty2 = j * BS; ty2 < m && ty2 < next; ++ty2)
            {
                int                O2 = ty2 * n;
                int ty1 = ty2 - 1, O1 = O2 - n;
                int ty0 = ty1 - 1, O0 = O1 - n;
                int ty3 = ty2 + 1, O3 = O2 + n;
                int ty4 = ty3 + 1, O4 = O3 + n;
                for (int tx2 = 0; tx2 < n; ++tx2)
                {
                    int tx1 = tx2 - 1;
                    int tx0 = tx1 - 1;
                    int tx3 = tx2 + 1;
                    int tx4 = tx3 + 1;
                    HIST_1D(in, O, tx)
                    out[O2 + tx2] = ENTROPY_LOGT(logt_h, *);
                }
            }
        }
    }
	QueryPerformanceCounter(&t2);
    cout << "Number of loops: " << num_loops << endl;
    cout << "Number of threads: " << num_threads << endl;
    cout << "Correctness: " << check_result(out, in, M, N) << endl;
    cout << "Efficiency: " << (t2.QuadPart - t1.QuadPart) * 1.0 / EPOCHS / tc.QuadPart << " us" << endl;
    cout << endl;
}

int main()
{
    init_data(in, M, N, SEED);
    cout << "M x N: " << M << " x " << N << endl << endl;
    test(4, 4);
    test(8, 8);
    test(16, 16);
    test(32, 32);
    test(64, 64);
}
