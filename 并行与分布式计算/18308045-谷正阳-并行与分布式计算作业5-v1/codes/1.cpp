#include <chrono>
#include <iostream>
#include <omp.h>
using namespace std;
using namespace std::chrono;
struct Mat
{
    float *val;
    size_t row;
    size_t col;
};
struct Vec
{
    float *val;
    size_t size;
};
Vec gen_vec(size_t size)
{
    Vec vec;
    vec.size = size;
    vec.val = new float[size + 1];
    for (size_t i = 1; i <= size; i++)
    {
        vec.val[i] = i;
    }
    return vec;
}
void print_vec(Vec vec)
{
    for (size_t i = 1; i <= vec.size; i++)
    {
        printf("%f ", vec.val[i]);
    }
    putchar('\n');
}
bool cmp_vec(Vec vec1, Vec vec2, float eps = 1e-6)
{
    if (vec1.size != vec2.size)
    {
        return false;
    }
    for (size_t i = 1; i <= vec1.size; i++)
    {
        if (abs(vec1.val[i] - vec2.val[i]) > eps)
        {
            return false;
        }
    }
    return true;
}
struct CRS
{
    float *val;
    size_t *col_ind;
    size_t *row_ptr;
    size_t row;
};
void Mat2CRS(CRS &crs, Mat &mat, float eps = 1e-6)
{
    size_t index = 1;
    crs.row = 0;
    crs.val = new float[mat.col + 1];
    crs.col_ind = new size_t[mat.col + 1];
    crs.row_ptr = new size_t[mat.row + 2];
    for (size_t i = 1; i <= mat.row; i++)
    {
        crs.row_ptr[++crs.row] = index;
        for (size_t j = 1; j <= mat.col; j++)
        {
            if (abs(mat.val[i * (mat.col + 1) + j]) > eps)
            {
                crs.val[index] = mat.val[i * (mat.col + 1) + j];
                crs.col_ind[index++] = j;
            }
        }
    }
    crs.row_ptr[crs.row + 1] = index;
}
CRS read_HB_as_CRS(const char *path)
{
    FILE *fp = fopen(path, "r");
    fseek(fp, 2 * 81 + 28, SEEK_SET);
    size_t n;
    CRS crs;
    fscanf(fp, "%zu%zu", &crs.row, &n);
    fseek(fp, 4 * 81, SEEK_SET);
    crs.row_ptr = new size_t[crs.row + 2];
    for (size_t i = 1; i <= crs.row + 1; i++)
    {
        fscanf(fp, "%zu", crs.row_ptr + i);
    }
    crs.col_ind = new size_t[n + 1];
    for (size_t i = 1; i <= n; i++)
    {
        fscanf(fp, "%zu", crs.col_ind + i);
    }
    crs.val = new float[n + 1];
    for (size_t i = 1; i <= n; i++)
    {
        fscanf(fp, "%f", crs.val + i);
    }
    fclose(fp);
    return crs;
}
void mul(Vec ans, CRS crs, Vec vec, unsigned char num_t = 1)
{
#pragma omp parallel for num_threads(num_t)
    for (int i = 1; i <= crs.row; i++)
    {
        //printf("i = %zu, ThreadId = %d\n", i, omp_get_thread_num());
        ans.val[i] = 0;
        for (size_t j = crs.row_ptr[i]; j < crs.row_ptr[i + 1]; j++)
        {
            ans.val[i] += vec.val[crs.col_ind[j]] * crs.val[j];
        }
    }
}
float mat_val[] = {0, 0, 0, 0, 0,
                   0, 19, 27, 0, 0,
                   0, 0, 0, 0, 0,
                   0, 0, 0, 0, 52,
                   0, 81, 0, 95, 33};
Mat mat;
float vec_val[] = {0, 1, 2, 3, 4};
Vec vec;
CRS crs;
int main()
{
    /*
    mat.val = mat_val;
    mat.row = 4;
    mat.col = 4;
    Mat2CRS(crs, mat);
    vec.val = vec_val;
    vec.size = 4;
    Vec ans = 
    print_vec(mul(crs, vec));
    */
    crs = read_HB_as_CRS("1138_bus.rsa");
    vec = gen_vec(1138);
    Vec ans;
    ans.size = crs.row;
    ans.val = new float[crs.row + 1];
    auto start = steady_clock::now();
    mul(ans, crs, vec);
    auto end = steady_clock::now();
    float tm = (float)duration_cast<nanoseconds>(end - start).count();
    printf("Num of threads: %d\n", 1);
    printf("Time: %f\n", tm);
    Vec ans_t;
    ans_t.size = crs.row;
    ans_t.val = new float[crs.row + 1];
    for (unsigned char num_t = 2; num_t <= omp_get_num_procs(); num_t++)
    {
        start = steady_clock::now();
        mul(ans_t, crs, vec, num_t);
        end = steady_clock::now();
        tm = (float)duration_cast<nanoseconds>(end - start).count();
        printf("Num of threads: %d\n", num_t);
        printf("Verify: %d\n", cmp_vec(ans_t, ans));
        printf("Time: %f\n", tm);
    }
    return 0;
}