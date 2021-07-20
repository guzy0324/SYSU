# include <cstdlib>
# include <cmath>
using namespace std;

/*
宏定义：HIST_1D

宏定义描述：
1. 用h数组记录输入块当前位置5 x 5邻域内出现的[0, 15]有效数字出现的个数
2. 用num记录5 x 5邻域内有效数字个数（即未越界）；
   (tx2, ty2)表示当前线程位置，tx2 = 0时横向少2条，tx2 = 1时横向少1条，tx2 = n - 2时横向少1条，tx2 = n - 1时横向少2条，纵向同理
3. 注意这里块是1D表示

参数描述：
in：输入块，1D表示
O：O表示2D最外层索引转为1D索引的变量前缀名，O##2表示当前位置，O##3表示当前位置向下一位，以此类推
xx：xx表示2D最内层索引的变量前缀名，xx##2表示当前位置，xx##3表示当前位置向右一位，以此类推
*/
# define HIST_1D(in, O, xx) \
    int num = (min(tx2, 2) + min(n - tx2, 3)) * (min(ty2, 2) + min(m - ty2, 3)); \
    int h[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; \
    int x0 = tx0 >= 0, x1 = tx1 >= 0, x3 = tx3 < n, x4 = tx4 < n; \
    if (ty0 >= 0) \
    { \
        if (x0) ++h[in[O##0 + xx##0]]; if (x1) ++h[in[O##0 + xx##1]]; ++h[in[O##0 + xx##2]]; if (x3) ++h[in[O##0 + xx##3]]; if (x4) ++h[in[O##0 + xx##4]]; \
    } \
    if (ty1 >= 0) \
    { \
        if (x0) ++h[in[O##1 + xx##0]]; if (x1) ++h[in[O##1 + xx##1]]; ++h[in[O##1 + xx##2]]; if (x3) ++h[in[O##1 + xx##3]]; if (x4) ++h[in[O##1 + xx##4]]; \
    } \
        if (x0) ++h[in[O##2 + xx##0]]; if (x1) ++h[in[O##2 + xx##1]]; ++h[in[O##2 + xx##2]]; if (x3) ++h[in[O##2 + xx##3]]; if (x4) ++h[in[O##2 + xx##4]]; \
    if (ty3 < m) \
    { \
        if (x0) ++h[in[O##3 + xx##0]]; if (x1) ++h[in[O##3 + xx##1]]; ++h[in[O##3 + xx##2]]; if (x3) ++h[in[O##3 + xx##3]]; if (x4) ++h[in[O##3 + xx##4]]; \
    } \
    if (ty4 < m) \
    { \
        if (x0) ++h[in[O##4 + xx##0]]; if (x1) ++h[in[O##4 + xx##1]]; ++h[in[O##4 + xx##2]]; if (x3) ++h[in[O##4 + xx##3]]; if (x4) ++h[in[O##4 + xx##4]]; \
    }

/*
宏定义：HIST_2D

宏定义描述：
1. 用h数组记录输入块当前位置5 x 5邻域内出现的[0, 15]有效数字出现的个数
2. 用num记录5 x 5邻域内有效数字个数（即未越界）；
   (tx2, ty2)表示当前线程位置，tx2 = 0时横向少2条，tx2 = 1时横向少1条，tx2 = n - 2时横向少1条，tx2 = n - 1时横向少2条，纵向同理
3. 注意这里块是2D表示

参数描述：
in：输入块，2D表示
yy：yy表示2D最外层索引的变量前缀名，yy##2表示当前位置，yy##3表示当前位置向下一位，以此类推
xx：xx表示2D最内层索引的变量前缀名，xx##2表示当前位置，xx##3表示当前位置向右一位，以此类推
*/
# define HIST_2D(in, yy, xx) \
    int num = (min(tx2, 2) + min(n - tx2, 3)) * (min(ty2, 2) + min(m - ty2, 3)); \
    int h[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; \
    int x0 = tx0 >= 0, x1 = tx1 >= 0, x3 = tx3 < n, x4 = tx4 < n; \
    if (ty0 >= 0) \
    { \
        if (x0) ++h[in[yy##0][xx##0]]; if (x1) ++h[in[yy##0][xx##1]]; ++h[in[yy##0][xx##2]]; if (x3) ++h[in[yy##0][xx##3]]; if (x4) ++h[in[yy##0][xx##4]]; \
    } \
    if (ty1 >= 0) \
    { \
        if (x0) ++h[in[yy##1][xx##0]]; if (x1) ++h[in[yy##1][xx##1]]; ++h[in[yy##1][xx##2]]; if (x3) ++h[in[yy##1][xx##3]]; if (x4) ++h[in[yy##1][xx##4]]; \
    } \
        if (x0) ++h[in[yy##2][xx##0]]; if (x1) ++h[in[yy##2][xx##1]]; ++h[in[yy##2][xx##2]]; if (x3) ++h[in[yy##2][xx##3]]; if (x4) ++h[in[yy##2][xx##4]]; \
    if (ty3 < m) \
    { \
        if (x0) ++h[in[yy##3][xx##0]]; if (x1) ++h[in[yy##3][xx##1]]; ++h[in[yy##3][xx##2]]; if (x3) ++h[in[yy##3][xx##3]]; if (x4) ++h[in[yy##3][xx##4]]; \
    } \
    if (ty4 < m) \
    { \
        if (x0) ++h[in[yy##4][xx##0]]; if (x1) ++h[in[yy##4][xx##1]]; ++h[in[yy##4][xx##2]]; if (x3) ++h[in[yy##4][xx##3]]; if (x4) ++h[in[yy##4][xx##4]]; \
    } \

/*
宏定义：ENTROPY_LOGF

宏定义描述：
1. 用logf函数计算熵
2. h为[0, 15]出现统计图，num为有效数字总数
3. 熵公式由sum([e / num * log(e / num) * for e in h])改写为sum([e * log(e) * for e in h]) / (-num) + log(num)

参数描述：无
*/
# define ENTROPY_LOGF \
    (((h[0]  == 0 ? 0.0f : h[0]  * logf((float)h[0]))  \
    + (h[1]  == 0 ? 0.0f : h[1]  * logf((float)h[1]))  \
    + (h[2]  == 0 ? 0.0f : h[2]  * logf((float)h[2]))  \
    + (h[3]  == 0 ? 0.0f : h[3]  * logf((float)h[3]))  \
    + (h[4]  == 0 ? 0.0f : h[4]  * logf((float)h[4]))  \
    + (h[5]  == 0 ? 0.0f : h[5]  * logf((float)h[5]))  \
    + (h[6]  == 0 ? 0.0f : h[6]  * logf((float)h[6]))  \
    + (h[7]  == 0 ? 0.0f : h[7]  * logf((float)h[7]))  \
    + (h[8]  == 0 ? 0.0f : h[8]  * logf((float)h[8]))  \
    + (h[9]  == 0 ? 0.0f : h[9]  * logf((float)h[9]))  \
    + (h[10] == 0 ? 0.0f : h[10] * logf((float)h[10])) \
    + (h[11] == 0 ? 0.0f : h[11] * logf((float)h[11])) \
    + (h[12] == 0 ? 0.0f : h[12] * logf((float)h[12])) \
    + (h[13] == 0 ? 0.0f : h[13] * logf((float)h[13])) \
    + (h[14] == 0 ? 0.0f : h[14] * logf((float)h[14])) \
    + (h[15] == 0 ? 0.0f : h[15] * logf((float)h[15]))) / (-num) + logf((float)num))

/*
宏定义：ENTROPY_LOGT

宏定义描述：
1. 查表logt来计算熵
2. h为[0, 15]出现统计图，num为有效数字总数
3. 熵公式由sum([e / num * log(e / num) * for e in h])改写为sum([e * log(e) * for e in h]) / (-num) + log(num)

参数描述：
logt：表名
deref：表的解引用方式，可以是*，也可以是__ldg
*/
# define ENTROPY_LOGT(logt, deref) \
    ((h[0]  * deref(logt + h[0])  + h[1]  * deref(logt + h[1])  \
    + h[2]  * deref(logt + h[2])  + h[3]  * deref(logt + h[3])  \
    + h[4]  * deref(logt + h[4])  + h[5]  * deref(logt + h[5])  \
    + h[6]  * deref(logt + h[6])  + h[7]  * deref(logt + h[7])  \
    + h[8]  * deref(logt + h[8])  + h[9]  * deref(logt + h[9])  \
    + h[10] * deref(logt + h[10]) + h[11] * deref(logt + h[11]) \
    + h[12] * deref(logt + h[12]) + h[13] * deref(logt + h[13]) \
    + h[14] * deref(logt + h[14]) + h[15] * deref(logt + h[15])) / (-num) + logt[num])

/*
函数：init_data

函数描述：
1. 随机初始化输入矩阵
2. 每点随机数取[0, 15]

参数描述：
in_host：输入矩阵的1D形式
m：输入矩阵列数
n：输入矩阵行数
seed：随机种子，保证实验结果可重现
*/
void init_data(int* in_host, int m, int n, int seed)
{
    srand(seed);
    for (int i = 0; i < m * n; ++i)
    {
        in_host[i] = rand() % 16;
    }
}

float logt_h[26] = {0.0f, 0.0f, 0.6931471805599453f, 1.0986122886681098f, 1.3862943611198906f, 1.6094379124341003f, 1.791759469228055f, 1.9459101490553132f, 2.0794415416798357f, 2.1972245773362196f, 2.302585092994046f, 2.3978952727983707f, 2.4849066497880004f, 2.5649493574615367f, 2.6390573296152584f, 2.70805020110221f, 2.772588722239781f, 2.833213344056216f, 2.8903717578961645f, 2.9444389791664403f, 2.995732273553991f, 3.044522437723423f, 3.091042453358316f, 3.1354942159291497f, 3.1780538303479458f, 3.2188758248682006f};

/*
函数：check_result

函数描述：检查运行结果是否正确，是返回1，否返回0

参数描述：
out：待检查输出矩阵的1D形式
in：输入矩阵的1D形式
m：矩阵列数
n：矩阵行数
p：检查精度，默认0.0001，即允许误差+-0.0001
seed：随机种子，保证实验结果可重现
*/
int check_result(float* out, int* in, int m, int n, float p = 0.0001)
{
    for (int ty2 = 0; ty2 < m; ++ty2)
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
            if (abs(ENTROPY_LOGT(logt_h, *) - out[O2 + tx2]) > p)
            {
                return 0;
            }
        }
    }
    return 1;
}

/*
函数：divup

函数描述：整数除法向上取整

参数描述：
a：被除数
b：除数
*/
inline int divup(int a, int b)
{
    return a / b + (a % b != 0);
}
