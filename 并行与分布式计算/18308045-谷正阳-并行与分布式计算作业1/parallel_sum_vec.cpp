#include <chrono>
#include <cstring>
#include <immintrin.h>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;
using namespace std::chrono;
#define SIZE 1000000
#define N 1000
int arr1[SIZE], arr2[SIZE];

void sequential_sum(int *res, const int *arr1, const int *arr2, int size = SIZE)
{
    int i;
    for (i = 0; i < size; i++)
    {
        res[i] = arr1[i] + arr2[i];
    }
}

void AVX_sum(int *res, const int *arr1, const int *arr2, int size = SIZE)
{
    int i;
    __m256i *pnt1 = (__m256i *)(arr1), *pnt2 = (__m256i *)(arr2);
    for (i = 0; i<size>> 3; i++)
    {
        _mm256_storeu_si256((__m256i *)res + i, _mm256_add_epi32(_mm256_loadu_si256(pnt1 + i), _mm256_loadu_si256(pnt2 + i)));
    }

    for (i = i << 3; i < size; i++)
    {
        res[i] = arr1[i] + arr2[i];
    }
}

void thread_sum_4(int *res, int *arr1, int *arr2, int size = SIZE, void func(int *, const int *, const int *, int) = sequential_sum)
{
    int temp = size >> 2, temp1 = temp << 1, temp2 = temp + temp1;
    thread t1(func, res + temp2, arr1 + temp2, arr2 + temp2, size - temp2);
    thread t2(func, res, arr1, arr2, temp);
    thread t3(func, res + temp, arr1 + temp, arr2 + temp, temp);
    func(res + temp1, arr1 + temp1, arr2 + temp1, temp);

    t2.join();
    t3.join();
    t1.join();
}

void thread_sum_5(int *res, int *arr1, int *arr2, int size = SIZE, void func(int *, const int *, const int *, int) = sequential_sum)
{
    int temp = size / 5, temp1 = temp << 1, temp2 = temp + temp1, temp3 = temp << 2;
    thread t1(func, res + temp3, arr1 + temp3, arr2 + temp3, size - temp3);
    thread t2(func, res, arr1, arr2, temp);
    thread t3(func, res + temp, arr1 + temp, arr2 + temp, temp);
    thread t4(func, res + temp1, arr1 + temp1, arr2 + temp1, temp);
    func(res + temp2, arr1 + temp2, arr2 + temp2, temp);

    t2.join();
    t3.join();
    t4.join();
    t1.join();
}

void thread_sum_8(int *res, int *arr1, int *arr2, int size = SIZE, void func(int *, const int *, const int *, int) = sequential_sum)
{
    int temp = size >> 3, temp1 = temp << 1, temp2 = temp + temp1, temp3 = temp << 2, temp4 = temp + temp3, temp5 = temp1 + temp3, temp6 = temp2 + temp3;
    thread t1(func, res + temp6, arr1 + temp6, arr2 + temp6, size - temp6);
    thread t2(func, res, arr1, arr2, temp);
    thread t3(func, res + temp, arr1 + temp, arr2 + temp, temp);
    thread t4(func, res + temp1, arr1 + temp1, arr2 + temp1, temp);
    thread t5(func, res + temp2, arr1 + temp2, arr2 + temp2, temp);
    thread t6(func, res + temp3, arr1 + temp3, arr2 + temp3, temp);
    thread t7(func, res + temp4, arr1 + temp4, arr2 + temp4, temp);
    func(res + temp5, arr1 + temp5, arr2 + temp5, temp);

    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t1.join();
}

int main()
{
    int i, *res = new int[SIZE];
    for (i = 1; i < SIZE; i++)
    {
        arr1[i] = arr1[i - 1] + 1;
        arr2[i] = arr1[i - 1] + 1;
    }
    auto start = steady_clock::now();
    for (i = 0; i < N; i++)
    {
        sequential_sum(res, arr1, arr2);
    }
    auto end = steady_clock::now();
    float t1 = (float)duration_cast<nanoseconds>(end - start).count();
    for (i = 0; res[i] == 2 * i && i < SIZE; i++)
        ;
    puts("Sequential:");
    printf("verify_res:\t%d\n", i == SIZE);
    printf("time:\t%f\n\n", t1 / N);

    memset(res, 0, SIZE * sizeof(int));
    start = steady_clock::now();
    for (i = 0; i < N; i++)
    {
        AVX_sum(res, arr1, arr2);
    }
    end = steady_clock::now();
    float t2 = (float)duration_cast<nanoseconds>(end - start).count();
    for (i = 0; res[i] == 2 * i && i < SIZE; i++)
        ;
    puts("AVX:");
    printf("verify_res:\t%d\n", i == SIZE);
    printf("time:\t%f\n", t2 / N);
    printf("speedup:\t%f\n\n", t1 / t2);

    memset(res, 0, SIZE * sizeof(int));
    start = steady_clock::now();
    for (i = 0; i < N; i++)
    {
        thread_sum_4(res, arr1, arr2);
    }
    end = steady_clock::now();
    float t3 = (float)duration_cast<nanoseconds>(end - start).count();
    for (i = 0; res[i] == 2 * i && i < SIZE; i++)
        ;
    puts("4threads:");
    printf("verify_res:\t%d\n", i == SIZE);
    printf("time:\t%f\n", t3 / N);
    printf("speedup:\t%f\n\n", t1 / t3);

    memset(res, 0, SIZE * sizeof(int));
    start = steady_clock::now();
    for (i = 0; i < N; i++)
    {
        thread_sum_5(res, arr1, arr2);
    }
    end = steady_clock::now();
    float t4 = (float)duration_cast<nanoseconds>(end - start).count();
    for (i = 0; res[i] == 2 * i && i < SIZE; i++)
        ;
    puts("5threads:");
    printf("verify_res:\t%d\n", i == SIZE);
    printf("time:\t%f\n", t4 / N);
    printf("speedup:\t%f\n\n", t1 / t4);

    memset(res, 0, SIZE * sizeof(int));
    start = steady_clock::now();
    for (i = 0; i < N; i++)
    {
        thread_sum_8(res, arr1, arr2);
    }
    end = steady_clock::now();
    float t5 = (float)duration_cast<nanoseconds>(end - start).count();
    for (i = 0; res[i] == 2 * i && i < SIZE; i++)
        ;
    puts("8threads:");
    printf("verify_res:\t%d\n", i == SIZE);
    printf("time:\t%f\n", t5 / N);
    printf("speedup:\t%f\n\n", t1 / t5);

    memset(res, 0, SIZE * sizeof(int));
    start = steady_clock::now();
    for (i = 0; i < N; i++)
    {
        thread_sum_4(res, arr1, arr2, SIZE, AVX_sum);
    }
    end = steady_clock::now();
    float t6 = (float)duration_cast<nanoseconds>(end - start).count();
    for (i = 0; res[i] == 2 * i && i < SIZE; i++)
        ;
    puts("4threads with AVX:");
    printf("verify_res:\t%d\n", i == SIZE);
    printf("time:\t%f\n", t6 / N);
    printf("speedup:\t%f\n\n", t1 / t6);

    memset(res, 0, SIZE * sizeof(int));
    start = steady_clock::now();
    for (i = 0; i < N; i++)
    {
        thread_sum_5(res, arr1, arr2, SIZE, AVX_sum);
    }
    end = steady_clock::now();
    float t7 = (float)duration_cast<nanoseconds>(end - start).count();
    for (i = 0; res[i] == 2 * i && i < SIZE; i++)
        ;
    puts("5threads with AVX:");
    printf("verify_res:\t%d\n", i == SIZE);
    printf("time:\t%f\n", t7 / N);
    printf("speedup:\t%f\n\n", t1 / t7);

    memset(res, 0, SIZE * sizeof(int));
    start = steady_clock::now();
    for (i = 0; i < N; i++)
    {
        thread_sum_8(res, arr1, arr2, SIZE, AVX_sum);
    }
    end = steady_clock::now();
    float t8 = (float)duration_cast<nanoseconds>(end - start).count();
    for (i = 0; res[i] == 2 * i && i < SIZE; i++)
        ;
    puts("8threads with AVX:");
    printf("verify_res:\t%d\n", i == SIZE);
    printf("time:\t%f\n", t8 / N);
    printf("speedup:\t%f\n\n", t1 / t8);
    getchar();
}