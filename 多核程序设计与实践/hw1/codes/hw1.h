#include "cuda_runtime.h"
#include "device_launch_parameters.h"

/* 函数：divup
   函数描述：求upper(A/B)
   参数描述：
   A：被除数
   B：除数 */
__host__ __device__ inline int divup(int A, int B)
{
    return A % B ? A / B + 1 : A / B;
}

/* 函数：check_matrix
   函数描述：检查结果是否C=A+B
   参数描述：
   A_data：A的数据
   B_data：B的数据
   C_data：C的数据
   n：行数
   m：列数 */
bool check_matrix(int* A_data, int* B_data, int* C_data, int n, int m)
{
    int size = sizeof(int) * n * m;
    int* h_A = (int*)malloc(size);
    int* h_B = (int*)malloc(size);
    int* h_C = (int*)malloc(size);
    cudaMemcpy(h_A, A_data, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(h_B, B_data, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(h_C, C_data, size, cudaMemcpyDeviceToHost);
    for (int i = 0; i < n * m; ++i)
    {
        if (h_A[i] + h_B[i] != h_C[i])
        {
            return false;
        }
    }
    free(h_A);
    free(h_B);
    free(h_C);
    return true;
}

/* 函数：init_data
   函数描述：初始化矩阵数据，A_data[tid]=tid
   参数描述：
   A_data：矩阵数据
   n：行数
   m：列数 */
__global__ void init_data(int* A_data, int n, int m)
{
    int tid = blockDim.x * blockDim.x + threadIdx.x;
    if (tid < n * m)
    {
        A_data[tid] = tid;
    }
}

/* 函数：init_matrix
   函数描述：矩阵数据转化为二维数组形式
   参数描述：
   A：二维数组
   A_data：矩阵数据
   n：行数
   m：列数 */
__global__ void init_matrix(int** A, int* A_data, int n, int m)
{
    int tid = blockDim.x * blockIdx.x + threadIdx.x;
    if (tid < n)
    {
        A[tid] = &A_data[tid * m];
    }
}

/* 函数：matrix_add_1
   函数描述：二维数组，grid，block做C=A+B
   参数描述：
   A：矩阵A
   B：矩阵B
   C：矩阵C
   n：行数
   m：列数 */
__global__ void matrix_add_1(int** A, int** B, int** C, int n, int m)
{
    int x = blockDim.x * blockIdx.x + threadIdx.x;
    int y = blockDim.y * blockIdx.y + threadIdx.y;
    if (y < n && x < m)
    {
        C[y][x] = A[y][x] + B[y][x];
    }
}

/* 函数：matrix_add_2
   函数描述：一维数组，二维grid，block做C=A+B
   参数描述：
   A_data：矩阵A的数据
   B_data：矩阵B的数据
   C_data：矩阵C的数据
   n：行数
   m：列数 */
__global__ void matrix_add_2(int* A_data, int* B_data, int* C_data, int n, int m)
{
    int x = blockDim.x * blockIdx.x + threadIdx.x;
    int y = blockDim.y * blockIdx.y + threadIdx.y;
    if (y < n && x < m)
    {
        int pos = y * m + x;
        C_data[pos] = A_data[pos] + B_data[pos];
    }
}

/* 函数：matrix_add_3
   函数描述：一维数组，grid，block做C=A+B
   参数描述：
   A_data：矩阵A的数据
   B_data：矩阵B的数据
   C_data：矩阵C的数据
   n：行数
   m：列数 */
__global__ void matrix_add_3(int* A_data, int* B_data, int* C_data, int n, int m)
{
    int tid = blockDim.x * blockIdx.x + threadIdx.x;
    if (tid < n * m)
    {
        C_data[tid] = A_data[tid] + B_data[tid];
    }
}

/* 函数：matrix_add_4
   函数描述：一维数组，grid，block，每个线程计算k个元素，做C=A+B
   参数描述：
   A_data：矩阵A的数据
   B_data：矩阵B的数据
   C_data：矩阵C的数据
   n：行数
   m：列数
   k：每个线程计算元素数 */
__global__ void matrix_add_4(int* A_data, int* B_data, int* C_data, int n, int m, int k)
{
    int tid = blockDim.x * blockIdx.x + threadIdx.x;
    if (tid < divup(n * m, k))
    {
        for (int i = tid * k; i < n * m && i < (tid + 1) * k; ++i)
        {
			C_data[i] = A_data[i] + B_data[i];
        }
    }
}
