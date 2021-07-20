#include "multiply.h"
int main()
{
    vector<vector<int>> mat1(SIZE), mat2(SIZE);
    init(mat1, mat2);
    vector<vector<int>> ans3 = strassen(mat1, mat2);
    verify(ans3, mat1, mat2);
}