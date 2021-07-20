#include "multiply.h"
int main()
{
    vector<vector<int>> mat1(SIZE), mat2(SIZE);
    init(mat1, mat2);
    vector<vector<int>> ans1 = multiply(mat1, mat2);
    verify(ans1, mat1, mat2);
}