#include "multiply.h"
int main()
{
    vector<vector<int>> mat1(SIZE), mat2(SIZE);
    init(mat1, mat2);
    vector<vector<int>> ans4 = strassen(mat1, mat2, 150);
    verify(ans4, mat1, mat2);
}