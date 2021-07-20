#include <chrono>
#include <iostream>
#include <thread>
using namespace std;
using namespace std::chrono;
#define row 4
#define row_col 10000000
#define col 1
float A[row][row_col];
float B[row_col][col];
float C[row][col];
float tp[4][row_col];
void mul(float *t, int i, int k, int step)
{
    for (int j = k; j < k + step; j++)
    {
        t[j] = A[i][j] * B[j][0];
    }
}
void sum(float *t, int i, int k, int step)
{
    for (int j = k; j < k + step; j++)
    {
        C[i][0] += t[j];
    }
}
void mat_mul(int num, int stt, int step0, int step1)
{
    float *t = tp[num];
    for (int i = stt, k; i < stt + step0; i++)
    {
        mul(t, i, 0, step1);
        for (k = step1; k < row_col; k += step1)
        {
            thread t1(mul, t, i, k, step1);
            sum(t, i, k - step1, step1);
            t1.join();
        }
        sum(t, i, k - step1, step1);
    }
}
bool verify()
{
    for (int i = 0; i < row; i++)
    {
        if (C[i][0] - row_col >= 1 || C[i][0] - row_col <= -1)
        {
            return false;
        }
    }
    return true;
}
int main()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < row_col; j++)
        {
            A[i][j] = 1;
        }
    }
    for (int j = 0; j < row_col; j++)
    {
        B[j][0] = 1;
    }
    int step0 = row / 4;
    int stt2 = 2 * step0;
    int stt3 = 3 * step0;
    int step1 = row_col / 10;
    auto start = steady_clock::now();
    thread t1(mat_mul, 1, step0, step0, step1);
    thread t2(mat_mul, 2, stt2, step0, step1);
    thread t3(mat_mul, 3, stt3, step0, step1);
    mat_mul(0, 0, step0, step1);
    t1.join();
    t2.join();
    t3.join();
    auto end = steady_clock::now();
    float tm = (float)duration_cast<nanoseconds>(end - start).count();
    printf("verify:\t%d\n", verify() ? 1 : 0);
    printf("time:\t%f\n\n", tm);

    for (int i = 0; i < row; i++)
    {
        C[i][0] = 0;
    }
    start = steady_clock::now();
    t1 = thread(mat_mul, 1, step0, step0, row_col);
    t2 = thread(mat_mul, 2, stt2, step0, row_col);
    t3 = thread(mat_mul, 3, stt3, step0, row_col);
    mat_mul(0, 0, step0, row_col);
    t1.join();
    t2.join();
    t3.join();
    end = steady_clock::now();
    tm = (float)duration_cast<nanoseconds>(end - start).count();
    printf("verify:\t%d\n", verify() ? 1 : 0);
    printf("time:\t%f\n\n", tm);
    
    for (int i = 0; i < row; i++)
    {
        C[i][0] = 0;
    }
    start = steady_clock::now();
    mat_mul(0, 0, row, step1);
    end = steady_clock::now();
    tm = (float)duration_cast<nanoseconds>(end - start).count();
    printf("verify:\t%d\n", verify() ? 1 : 0);
    printf("time:\t%f\n\n", tm);

    for (int i = 0; i < row; i++)
    {
        C[i][0] = 0;
    }
    start = steady_clock::now();
    mat_mul(0, 0, row, row_col);
    end = steady_clock::now();
    tm = (float)duration_cast<nanoseconds>(end - start).count();
    printf("verify:\t%d\n", verify() ? 1 : 0);
    printf("time:\t%f\n\n", tm);
}