#include <cstdarg>
#include <iostream>
#include <vector>
using namespace std;
struct Matrix
{
    float **arr;
    size_t row;
    size_t col;
    Matrix(size_t r, size_t c, float v);
    Matrix(Matrix &m);
    Matrix(char *format, ...);
    ~Matrix();

private:
    void copy(Matrix &m);
    void del();
};
Matrix::Matrix(size_t r, size_t c, float v)
{
    row = r;
    col = c;
    arr = (float **)malloc(sizeof(float *) * row);
    for (int i = 0; i < row; i++)
    {
        arr[i] = (float *)malloc(sizeof(float) * col);
        for (int j = 0; j < col; j++)
        {
            arr[i][j] = v;
        }
    }
}
Matrix::Matrix(Matrix &m)
{
    copy(m);
}
Matrix::Matrix(char *format, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, format);
    if (format == nullptr)
    {
        return;
    }
    vector<vector<Matrix *>> mat_ptr_arr_arr;
    vector<int> col_arr;
    for (int i = 0; *format != 0; i++)
    {
        if (*format != 'm')
        {
            del();
            goto ret;
        }
        Matrix *mat_ptr = va_arg(arg_ptr, Matrix *);
        if (mat_ptr == nullptr)
        {
            return;
        }
        mat_ptr_arr_arr.push_back(vector<Matrix *>());
        col_arr.push_back(mat_ptr->col);
        mat_ptr_arr_arr[i].push_back(new Matrix(*mat_ptr));
        format++;
        for (; *format != 0 && *format != ';'; format += 2)
        {
            if (*(format + 1) != 'm')
            {
                del();
                goto ret;
            }
            mat_ptr = va_arg(arg_ptr, Matrix *);
            if (mat_ptr == nullptr)
            {
                del();
                goto ret;
            }
            if (*format == ',')
            {
                if (mat_ptr_arr_arr[i][0]->row != mat_ptr->row)
                {
                    del();
                    goto ret;
                }
                col_arr[i] += mat_ptr->col;
            }
            else
            {
                del();
                goto ret;
            }
            mat_ptr_arr_arr[i].push_back(new Matrix(*mat_ptr));
        }
        if (col_arr[0] != col_arr[i])
        {
            del();
            goto ret;
        }
        if (*format == ';')
        {
            format++;
        }
    }
    va_end(arg_ptr);
    for (int i = 0; i < mat_ptr_arr_arr.size(); i++)
    {
        for (int j = 0; j < mat_ptr_arr_arr.size(); j++)
        {
            mat_ptr_arr_arr[i][j];
        }
    }
    copy(*mat_ptr_arr_arr[0][0]);
ret:
    for (int i = 0; i < mat_ptr_arr_arr.size(); i++)
    {
        for (int j = 0; j < mat_ptr_arr_arr[i].size(); j++)
        {
            delete mat_ptr_arr_arr[i][j];
        }
    }
    return;
}
Matrix::~Matrix()
{
    del();
}
void Matrix::copy(Matrix &m)
{
    row = m.row;
    col = m.col;
    arr = (float **)malloc(sizeof(float *) * row);
    for (int i = 0; i < row; i++)
    {
        arr[i] = (float *)malloc(sizeof(float) * col);
        for (int j = 0; j < col; j++)
        {
            arr[i][j] = m.arr[i][j];
        }
    }
}
void Matrix::del()
{
    if (arr != nullptr)
    {
        for (int i = 0; i < row; i++)
        {
            free(arr[i]);
        }
        free(arr);
        arr = nullptr;
    }
    col = 0;
    row = 0;
}
int main()
{
    Matrix m0(1, 1, 0);
    Matrix m1(1, 1, 1);
    Matrix m2(2, 1, 2);
    Matrix m3(2, 1, 3);
    Matrix m4(1, 2, 4);
    Matrix m5((char *)"m,m;m,m;m", &m0, &m1, &m2, &m3, &m4);
    return 0;
}
/*
function [P] = gauss_seidel(A, B, P0, k)
    P = zeros(size(A, 2), k);
    coef = [-A, B];
    coef = coef ./ diag(A);
    coef(1:size(coef, 2):end) = 0;
    P(:, 1) = P0;
    for j = 1:size(A, 2)
        P(j, 1) = coef(j, :) * [P(:, 1); 1];
    end
    for i = 2:k
        P(:, i) = P(:, i - 1);
        for j = 1:size(A, 2)
            P(j, i) = coef(j, :) * [P(:, i); 1];
        end
    end
end
*/