#include "multiply.h"
int main()
{
    vector<vector<int>> mat1(SIZE), mat2(SIZE);
    init(mat1, mat2);
    vector<vector<int>> ans2 = thread_divide_and_conquer(mat1, mat2);
    verify(ans2, mat1, mat2);
}