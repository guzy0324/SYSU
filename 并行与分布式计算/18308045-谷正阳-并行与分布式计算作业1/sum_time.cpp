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
    int i, t;
    for (i = 0; i < size; i++)
    {
        arr1[i] + arr2[i];
    }
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
    puts("Sequential_without_move:");
    printf("time:\t%f\n\n", t1 / N);
    getchar();
}