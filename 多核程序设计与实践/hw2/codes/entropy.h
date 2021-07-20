# include "cuda_runtime.h"
# include "device_launch_parameters.h"
# include "utils.h"

// # define BDIM_X (8)
// # define BDIM_Y (8)
// # define BDIM_X (16)
// # define BDIM_Y (16)
// # define BDIM_X (24)
// # define BDIM_Y (24)
# define BDIM_X (32)
# define BDIM_Y (32)
# define SDIM_X (BDIM_X + 4)
# define SDIM_Y (BDIM_Y + 4)

/*
函数：init_matrix

函数描述：用矩阵1D形式初始化2D形式

参数描述：
A：矩阵2D形式
A_data：矩阵1D形式
m：矩阵行数
n：矩阵列数
*/
template<typename T> __global__ void init_matrix(T** A, T* A_data, int m, int n)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < m)
    {
        A[tid] = A_data + tid * n;
    }
}

/*
函数：entropy

函数描述：
1. baseline，不使用特殊的存储
2. 使用logf函数计算熵

参数描述：
out：输出矩阵
in：输入矩阵
m：矩阵行数
n：矩阵列数
*/
__global__ void entropy(float** out, int** in, int m, int n)
{
    int tx2 = blockIdx.x * BDIM_X + threadIdx.x, ty2 = blockIdx.y * BDIM_Y + threadIdx.y;
    if (ty2 < m && tx2 < n)
    {
        int tx1 = tx2 - 1, ty1 = ty2 - 1;
        int tx0 = tx1 - 1, ty0 = ty1 - 1;
        int tx3 = tx2 + 1, ty3 = ty2 + 1;
        int tx4 = tx3 + 1, ty4 = ty3 + 1;
        HIST_2D(in, ty, tx)
        out[ty2][tx2] = ENTROPY_LOGF;
    }
}

texture<int, 2, cudaReadModeElementType> tex;

/*
函数：bind_texture

函数描述：绑定2D纹理

参数描述：
buffer：矩阵1D表示
m：矩阵行数
n：矩阵列数
*/
__host__ void bind_texture(int* buffer, int m, int n)
{
    cudaChannelFormatDesc desc = cudaCreateChannelDesc<int>();
    cudaBindTexture2D(0, tex, buffer, desc, n, m, n * sizeof(int));
}

/*
函数：entropy_texture

函数描述：
1. 使用2D纹理内存
2. 使用logf函数计算熵
3. tex代替原本的输入矩阵in，查询官方文档（https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html），tex必须作为静态全局变量（查关键词static global）
4. 因为用到tex2D来解引用，没有想到如何写成和HIST_1D，HIST_2D统一的宏定义，因而在此并未使用宏定义

参数描述：
out：输出矩阵
m：矩阵行数
n：矩阵列数
*/
__global__ void entropy_texture(float** out, int m, int n)
{
    int tx2 = blockIdx.x * BDIM_X + threadIdx.x, ty2 = blockIdx.y * BDIM_Y + threadIdx.y;
    if (ty2 < m && tx2 < n)
    {
        int tx1 = tx2 - 1, ty1 = ty2 - 1;
        int tx0 = tx1 - 1, ty0 = ty1 - 1;
        int tx3 = tx2 + 1, ty3 = ty2 + 1;
        int tx4 = tx3 + 1, ty4 = ty3 + 1;

        // tx2 = 0时横向少2条，tx2 = 1时横向少1条，tx2 = n - 2时横向少1条，tx2 = n - 1时横向少2条
        int num = (min(tx2, 2) + min(n - tx2, 3)) * (min(ty2, 2) + min(m - ty2, 3));
        int h[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int x0 = tx0 >= 0, x1 = tx1 >= 0, x3 = tx3 < n, x4 = tx4 < n;
        if (ty0 >= 0)
        {
            if (x0) ++h[tex2D(tex, tx0, ty0)]; if (x1) ++h[tex2D(tex, tx1, ty0)]; ++h[tex2D(tex, tx2, ty0)]; if (x3) ++h[tex2D(tex, tx3, ty0)]; if (x4) ++h[tex2D(tex, tx4, ty0)];
        }
        if (ty1 >= 0)
        {
            if (x0) ++h[tex2D(tex, tx0, ty1)]; if (x1) ++h[tex2D(tex, tx1, ty1)]; ++h[tex2D(tex, tx2, ty1)]; if (x3) ++h[tex2D(tex, tx3, ty1)]; if (x4) ++h[tex2D(tex, tx4, ty1)];
        }
            if (x0) ++h[tex2D(tex, tx0, ty2)]; if (x1) ++h[tex2D(tex, tx1, ty2)]; ++h[tex2D(tex, tx2, ty2)]; if (x3) ++h[tex2D(tex, tx3, ty2)]; if (x4) ++h[tex2D(tex, tx4, ty2)];
        if (ty3 < m)
        {
            if (x0) ++h[tex2D(tex, tx0, ty3)]; if (x1) ++h[tex2D(tex, tx1, ty3)]; ++h[tex2D(tex, tx2, ty3)]; if (x3) ++h[tex2D(tex, tx3, ty3)]; if (x4) ++h[tex2D(tex, tx4, ty3)];
        }
        if (ty4 < m)
        {
            if (x0) ++h[tex2D(tex, tx0, ty4)]; if (x1) ++h[tex2D(tex, tx1, ty4)]; ++h[tex2D(tex, tx2, ty4)]; if (x3) ++h[tex2D(tex, tx3, ty4)]; if (x4) ++h[tex2D(tex, tx4, ty4)];
        }
        out[ty2][tx2] = ENTROPY_LOGF;
    }
}

/*
函数：entropy_shared

函数描述：
1. 使用共享内存
2. 经过分析应该不会出现存储体冲突的问题
3. 使用logf函数计算熵

参数描述：
out：输出矩阵
in：输入矩阵
m：矩阵行数
n：矩阵列数
*/
__global__ void entropy_shared(float** out, int** in, int m, int n)
{
    int tx2 = blockIdx.x * BDIM_X + threadIdx.x, ty2 = blockIdx.y * BDIM_Y + threadIdx.y;
    if (ty2 < m && tx2 < n)
    {
        int tx1 = tx2 - 1, ty1 = ty2 - 1;
        int tx0 = tx1 - 1, ty0 = ty1 - 1;
        int tx3 = tx2 + 1, ty3 = ty2 + 1;
        int tx4 = tx3 + 1, ty4 = ty3 + 1;

        __shared__ int smem[SDIM_X * SDIM_Y];
        int sx0 = threadIdx.x, sO0 = threadIdx.y * SDIM_X;
        int sx1 = sx0 + 1    , sO1 = sO0 + SDIM_X;
        int sx2 = sx1 + 1    , sO2 = sO1 + SDIM_X;
        int sx3 = sx2 + 1    , sO3 = sO2 + SDIM_X;
        int sx4 = sx3 + 1    , sO4 = sO3 + SDIM_X;
        smem[sO2 + sx2] = in[ty2][tx2];
        int sxm, sOm, txm, tym;
        if (sx0 <= 1)
        {
            /*
            如果BDIM_X >= 32，则此操作在不同warp中进行，不可能出现冲突；
            如果BDIM_X < 32，则执行此操作的线程对smem的访问差值小于32，不会出现冲突
            */
            sxm = sx2 + BDIM_X;
            txm = tx2 + BDIM_X;

            smem[sO2 + sx0] = tx0 <  0             ? 0 : in[ty2][tx0];
            smem[sO2 + sxm] = txm >= n             ? 0 : in[ty2][txm];
        }
        if (sO0 <= SDIM_X)
        {
            tym = ty2 + BDIM_Y;
            sOm = sO2 + BDIM_Y * SDIM_X;

            smem[sO0 + sx2] =             ty0 <  0 ? 0 : in[ty0][tx2];
            smem[sOm + sx2] =             tym >= m ? 0 : in[tym][tx2];
        }
        if (sx0 <= 1 && sO0 <= SDIM_X)
        {
            smem[sO0 + sx0] = tx0 <  0 || ty0 <  0 ? 0 : in[ty0][tx0];
            smem[sO0 + sxm] = txm >= n || ty0 <  0 ? 0 : in[ty0][txm];
            smem[sOm + sx0] = tx0 <  0 || tym >= m ? 0 : in[tym][tx0];
            smem[sOm + sxm] = txm >= n || tym >= m ? 0 : in[tym][txm];
        }
        __syncthreads();

        HIST_1D(smem, sO, sx)
        out[ty2][tx2] = ENTROPY_LOGF;
    }
}

__device__ float logt[26] = {0.0f, 0.0f, 0.6931471805599453f, 1.0986122886681098f, 1.3862943611198906f, 1.6094379124341003f, 1.791759469228055f, 1.9459101490553132f, 2.0794415416798357f, 2.1972245773362196f, 2.302585092994046f, 2.3978952727983707f, 2.4849066497880004f, 2.5649493574615367f, 2.6390573296152584f, 2.70805020110221f, 2.772588722239781f, 2.833213344056216f, 2.8903717578961645f, 2.9444389791664403f, 2.995732273553991f, 3.044522437723423f, 3.091042453358316f, 3.1354942159291497f, 3.1780538303479458f, 3.2188758248682006f};

/*
函数：entropy_shared_log

函数描述：
1. 使用共享内存
2. 经过分析应该不会出现存储体冲突的问题
3. 查询logt计算熵
4. logt存在全局内存

参数描述：
out：输出矩阵
in：输入矩阵
m：矩阵行数
n：矩阵列数
*/
__global__ void entropy_shared_log(float** out, int** in, int m, int n)
{
    int tx2 = blockIdx.x * BDIM_X + threadIdx.x, ty2 = blockIdx.y * BDIM_Y + threadIdx.y;
    if (ty2 < m && tx2 < n)
    {
        int tx1 = tx2 - 1, ty1 = ty2 - 1;
        int tx0 = tx1 - 1, ty0 = ty1 - 1;
        int tx3 = tx2 + 1, ty3 = ty2 + 1;
        int tx4 = tx3 + 1, ty4 = ty3 + 1;

        __shared__ int smem[SDIM_X * SDIM_Y];
        int sx0 = threadIdx.x, sO0 = threadIdx.y * SDIM_X;
        int sx1 = sx0 + 1    , sO1 = sO0 + SDIM_X;
        int sx2 = sx1 + 1    , sO2 = sO1 + SDIM_X;
        int sx3 = sx2 + 1    , sO3 = sO2 + SDIM_X;
        int sx4 = sx3 + 1    , sO4 = sO3 + SDIM_X;
        smem[sO2 + sx2] = in[ty2][tx2];
        int sxm, sOm, txm, tym;
        if (sx0 <= 1)
        {
            /*
            如果BDIM_X >= 32，则此操作在不同warp中进行，不可能出现冲突；
            如果BDIM_X < 32，则执行此操作的线程对smem的访问差值小于32，不会出现冲突
            */
            sxm = sx2 + BDIM_X;
            txm = tx2 + BDIM_X;

            smem[sO2 + sx0] = tx0 <  0             ? 0 : in[ty2][tx0];
            smem[sO2 + sxm] = txm >= n             ? 0 : in[ty2][txm];
        }
        if (sO0 <= SDIM_X)
        {
            tym = ty2 + BDIM_Y;
            sOm = sO2 + BDIM_Y * SDIM_X;

            smem[sO0 + sx2] =             ty0 <  0 ? 0 : in[ty0][tx2];
            smem[sOm + sx2] =             tym >= m ? 0 : in[tym][tx2];
        }
        if (sx0 <= 1 && sO0 <= SDIM_X)
        {
            smem[sO0 + sx0] = tx0 <  0 || ty0 <  0 ? 0 : in[ty0][tx0];
            smem[sO0 + sxm] = txm >= n || ty0 <  0 ? 0 : in[ty0][txm];
            smem[sOm + sx0] = tx0 <  0 || tym >= m ? 0 : in[tym][tx0];
            smem[sOm + sxm] = txm >= n || tym >= m ? 0 : in[tym][txm];
        }
        __syncthreads();

        HIST_1D(smem, sO, sx)
        out[ty2][tx2] = ENTROPY_LOGT(logt, *);
    }
}

/*
函数：entropy_shared_log_ldg

函数描述：
1. 使用共享内存
2. 经过分析应该不会出现存储体冲突的问题
3. 查询logt计算熵
4. logt使用只读的方式访问

参数描述：
out：输出矩阵
in：输入矩阵
m：矩阵行数
n：矩阵列数
*/
__global__ void entropy_shared_log_ldg(float** out, int** in, int m, int n)
{
    int tx2 = blockIdx.x * BDIM_X + threadIdx.x, ty2 = blockIdx.y * BDIM_Y + threadIdx.y;
    if (ty2 < m && tx2 < n)
    {
        int tx1 = tx2 - 1, ty1 = ty2 - 1;
        int tx0 = tx1 - 1, ty0 = ty1 - 1;
        int tx3 = tx2 + 1, ty3 = ty2 + 1;
        int tx4 = tx3 + 1, ty4 = ty3 + 1;

        __shared__ int smem[SDIM_X * SDIM_Y];
        int sx0 = threadIdx.x, sO0 = threadIdx.y * SDIM_X;
        int sx1 = sx0 + 1    , sO1 = sO0 + SDIM_X;
        int sx2 = sx1 + 1    , sO2 = sO1 + SDIM_X;
        int sx3 = sx2 + 1    , sO3 = sO2 + SDIM_X;
        int sx4 = sx3 + 1    , sO4 = sO3 + SDIM_X;
        smem[sO2 + sx2] = in[ty2][tx2];
        int sxm, sOm, txm, tym;
        if (sx0 <= 1)
        {
            /*
            如果BDIM_X >= 32，则此操作在不同warp中进行，不可能出现冲突；
            如果BDIM_X < 32，则执行此操作的线程对smem的访问差值小于32，不会出现冲突
            */
            sxm = sx2 + BDIM_X;
            txm = tx2 + BDIM_X;

            smem[sO2 + sx0] = tx0 <  0             ? 0 : in[ty2][tx0];
            smem[sO2 + sxm] = txm >= n             ? 0 : in[ty2][txm];
        }
        if (sO0 <= SDIM_X)
        {
            tym = ty2 + BDIM_Y;
            sOm = sO2 + BDIM_Y * SDIM_X;

            smem[sO0 + sx2] =             ty0 <  0 ? 0 : in[ty0][tx2];
            smem[sOm + sx2] =             tym >= m ? 0 : in[tym][tx2];
        }
        if (sx0 <= 1 && sO0 <= SDIM_X)
        {
            smem[sO0 + sx0] = tx0 <  0 || ty0 <  0 ? 0 : in[ty0][tx0];
            smem[sO0 + sxm] = txm >= n || ty0 <  0 ? 0 : in[ty0][txm];
            smem[sOm + sx0] = tx0 <  0 || tym >= m ? 0 : in[tym][tx0];
            smem[sOm + sxm] = txm >= n || tym >= m ? 0 : in[tym][txm];
        }
        __syncthreads();

        HIST_1D(smem, sO, sx)
        out[ty2][tx2] = ENTROPY_LOGT(logt, __ldg);
    }
}

/*
函数：entropy_shared_log_shared

函数描述：
1. 使用共享内存
2. 经过分析应该不会出现存储体冲突的问题
3. 查询logt计算熵
4. logt加载到共享内存

参数描述：
out：输出矩阵
in：输入矩阵
m：矩阵行数
n：矩阵列数
*/
__global__ void entropy_shared_log_shared(float** out, int** in, int m, int n)
{
    __shared__ float smem2[26];
    int idx = threadIdx.y * BDIM_X + threadIdx.x;
    if (idx <= 25)
    {
        smem2[idx] = logt[idx];
    }

    int tx2 = blockIdx.x * BDIM_X + threadIdx.x, ty2 = blockIdx.y * BDIM_Y + threadIdx.y;
    if (ty2 < m && tx2 < n)
    {
        int tx1 = tx2 - 1, ty1 = ty2 - 1;
        int tx0 = tx1 - 1, ty0 = ty1 - 1;
        int tx3 = tx2 + 1, ty3 = ty2 + 1;
        int tx4 = tx3 + 1, ty4 = ty3 + 1;

        __shared__ int smem[SDIM_X * SDIM_Y];
        int sx0 = threadIdx.x, sO0 = threadIdx.y * SDIM_X;
        int sx1 = sx0 + 1    , sO1 = sO0 + SDIM_X;
        int sx2 = sx1 + 1    , sO2 = sO1 + SDIM_X;
        int sx3 = sx2 + 1    , sO3 = sO2 + SDIM_X;
        int sx4 = sx3 + 1    , sO4 = sO3 + SDIM_X;
        smem[sO2 + sx2] = in[ty2][tx2];
        int sxm, sOm, txm, tym;
        if (sx0 <= 1)
        {
            // 如果BDIM_X >= 32，则此操作在不同warp中进行，不可能出现冲突；
            // 如果BDIM_X < 32，则执行此操作的线程对smem的访问差值小于32，不会出现冲突
            sxm = sx2 + BDIM_X;
            txm = tx2 + BDIM_X;

            smem[sO2 + sx0] = tx0 <  0             ? 0 : in[ty2][tx0];
            smem[sO2 + sxm] = txm >= n             ? 0 : in[ty2][txm];
        }
        if (sO0 <= SDIM_X)
        {
            tym = ty2 + BDIM_Y;
            sOm = sO2 + BDIM_Y * SDIM_X;

            smem[sO0 + sx2] =             ty0 <  0 ? 0 : in[ty0][tx2];
            smem[sOm + sx2] =             tym >= m ? 0 : in[tym][tx2];
        }
        if (sx0 <= 1 && sO0 <= SDIM_X)
        {
            smem[sO0 + sx0] = tx0 <  0 || ty0 <  0 ? 0 : in[ty0][tx0];
            smem[sO0 + sxm] = txm >= n || ty0 <  0 ? 0 : in[ty0][txm];
            smem[sOm + sx0] = tx0 <  0 || tym >= m ? 0 : in[tym][tx0];
            smem[sOm + sxm] = txm >= n || tym >= m ? 0 : in[tym][txm];
        }
        __syncthreads();

        HIST_1D(smem, sO, sx)
        out[ty2][tx2] = ENTROPY_LOGT(smem2, *);
    }
}
