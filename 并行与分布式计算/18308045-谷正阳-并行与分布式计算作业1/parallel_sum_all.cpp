#include <chrono>
#include <immintrin.h>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;
using namespace std::chrono;
#define SIZE 10000
#define N 1
int arr[SIZE] = {0};

int sequential_sum(const int *arr)
{
    int i, res = 0;
    for (i = 0; i < SIZE; i++)
    {
        res += arr[i];
    }
    return res;
}

int AVX_sum(const int *arr)
{
    int i;
    __m256i sum_blk = _mm256_set1_epi32(0), *pnt = (__m256i *)arr;
    for (i = 0; i<SIZE>> 3; i++)
    {
        sum_blk = _mm256_add_epi32(sum_blk, _mm256_loadu_si256(pnt + i));
    }

    const int *tmp_blk = (const int *)&sum_blk;
    int res = 0;
    res += tmp_blk[0] + tmp_blk[1] + tmp_blk[2] + tmp_blk[3] + tmp_blk[4] + tmp_blk[5] + tmp_blk[6] + tmp_blk[7];

    for (i = i << 3; i < SIZE; i++)
    {
        res += arr[i];
    }
    return res;
}

int thread_sum(int *arr, int left = 0, int right = SIZE)
{
    if (right - left == 1)
    {
        return arr[left];
    }
    int a, b;
    thread tmp([&b, arr, left, right]() {
        b = thread_sum(arr, (left + right) >> 1, right);
    });
    a = thread_sum(arr, left, (left + right) >> 1);
    tmp.join();
    return a + b;
}

int thread_sum_1(int *arr)
{
    int i, size = SIZE;
    vector<thread *> vec;
    thread *tmp;
    while (size > 1)
    {
        for (i = 0; i<size>> 1; i++)
        {
            tmp = new thread([arr, size, i]() {
                arr[i] += arr[size - i - 1];
            });
            vec.push_back(tmp);
        }
        while (!vec.empty())
        {
            vec.back()->join();
            vec.pop_back();
        }
        size = size - i;
    }
    return arr[0];
}

int main()
{
    int i, res;
    for (i = 1; i < SIZE; i++)
    {
        arr[i] = arr[i - 1] + 1;
    }
    auto start = steady_clock::now();
    for (i = 0; i < N; i++)
    {
        res = sequential_sum(arr);
    }
    auto end = steady_clock::now();
    float t1 = (float)duration_cast<nanoseconds>(end - start).count() / N;
    puts("Sequential:");
    printf("res:\t%d\n", res);
    printf("time:\t%lld\n\n", t1);

    start = steady_clock::now();
    for (i = 0; i < N; i++)
    {
        res = AVX_sum(arr);
    }
    end = steady_clock::now();
    float t2 = (float)duration_cast<nanoseconds>(end - start).count() / N;
    puts("AVX:");
    printf("res:\t%d\n", res);
    printf("time:\t%lld\n", t2);
    printf("speedup:\t%f\n\n", t1 / t2);

    start = steady_clock::now();
    for (i = 0; i < N; i++)
    {
        res = thread_sum(arr);
    }
    end = steady_clock::now();
    float t3 = (float)duration_cast<nanoseconds>(end - start).count() / N;
    puts("Thread0:");
    printf("res:\t%d\n", res);
    printf("time:\t%lld\n", t3);
    printf("speedup:\t%f\n\n", t1 / t3);

    start = steady_clock::now();
    for (i = 0; i < N; i++)
    {
        res = thread_sum_1(arr);
    }
    end = steady_clock::now();
    float t4 = (float)duration_cast<nanoseconds>(end - start).count() / N;
    puts("Thread1:");
    printf("res:\t%d\n", res);
    printf("time:\t%lld\n", t4);
    printf("speedup:\t%f\n\n", t1 / t4);
    getchar();
}