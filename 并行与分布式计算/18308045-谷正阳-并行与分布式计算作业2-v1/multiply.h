#include <iostream>
#include <vector>
using namespace std;
#define SIZE 300
#define ADD(ans, mat1, mat2)                           \
	vector<vector<int>> ans(mat1.size());              \
	for (int i = 0; i < mat1.size(); i++)              \
	{                                                  \
		for (int j = 0; j < mat2[0].size(); j++)       \
		{                                              \
			ans[i].push_back(mat1[i][j] + mat2[i][j]); \
		}                                              \
	}
#define MINUS(ans, mat1, mat2)                         \
	vector<vector<int>> ans(mat1.size());              \
	for (int i = 0; i < mat1.size(); i++)              \
	{                                                  \
		for (int j = 0; j < mat2[0].size(); j++)       \
		{                                              \
			ans[i].push_back(mat1[i][j] - mat2[i][j]); \
		}                                              \
	}
#define MULTIPLY(ans, mat1, mat2)                 \
	vector<vector<int>> ans(mat1.size());         \
	for (int i = 0; i < mat1.size(); i++)         \
	{                                             \
		for (int j = 0; j < mat2[0].size(); j++)  \
		{                                         \
			int t = 0;                            \
			for (int k = 0; k < mat2.size(); k++) \
			{                                     \
				t += mat1[i][k] * mat2[k][j];     \
			}                                     \
			ans[i].push_back(t);                  \
		}                                         \
	}
vector<vector<int>> multiply(vector<vector<int>> &mat1, vector<vector<int>> &mat2)
{
	MULTIPLY(ans, mat1, mat2)
	return ans;
}
void divide_and_conquer_kernel(vector<vector<int>> &ans, vector<vector<int>> &mat1, vector<vector<int>> &mat2,
							   int x1, int y1, int x2, int y2, int x3, int y3,
							   int sz1, int sz2, int sz3)
{
	if (sz1 == 0 || sz2 == 0 || sz3 == 0)
	{
		return;
	}
	if (sz1 == 1 && sz2 == 1 && sz3 == 1)
	{
		ans[x3][y3] += mat1[x1][y1] * mat2[x2][y2];
		return;
	}
	int sz1_d_2 = sz1 / 2;
	int sz2_d_2 = sz2 / 2;
	int sz3_d_2 = sz3 / 2;
	int sz1_m_sz1_d_2 = sz1 - sz1_d_2;
	int sz2_m_sz2_d_2 = sz2 - sz2_d_2;
	int sz3_m_sz3_d_2 = sz3 - sz3_d_2;
	int x1_a_sz3_d_2 = x1 + sz3_d_2;
	int y1_a_sz1_d_2 = y1 + sz1_d_2;
	int x2_a_sz2_d_2 = x2 + sz2_d_2;
	int y2_a_sz3_d_2 = y2 + sz3_d_2;
	int x3_a_sz2_d_2 = x3 + sz2_d_2;
	int y3_a_sz1_d_2 = y3 + sz1_d_2;
	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1, y1,
							  x2, y2,
							  x3, y3,
							  sz1_d_2, sz2_d_2, sz3_d_2);
	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1_a_sz3_d_2, y1,
							  x2, y2_a_sz3_d_2,
							  x3, y3,
							  sz1_d_2, sz2_d_2, sz3_m_sz3_d_2);
	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1, y1,
							  x2_a_sz2_d_2, y2,
							  x3_a_sz2_d_2, y3,
							  sz1_d_2, sz2_m_sz2_d_2, sz3_d_2);
	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1_a_sz3_d_2, y1,
							  x2_a_sz2_d_2, y2_a_sz3_d_2,
							  x3_a_sz2_d_2, y3,
							  sz1_d_2, sz2_m_sz2_d_2, sz3_m_sz3_d_2);
	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1, y1_a_sz1_d_2,
							  x2, y2,
							  x3, y3_a_sz1_d_2,
							  sz1_m_sz1_d_2, sz2_d_2, sz3_d_2);
	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1_a_sz3_d_2, y1_a_sz1_d_2,
							  x2, y2_a_sz3_d_2,
							  x3, y3_a_sz1_d_2,
							  sz1_m_sz1_d_2, sz2_d_2, sz3_m_sz3_d_2);
	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1, y1_a_sz1_d_2,
							  x2_a_sz2_d_2, y2,
							  x3_a_sz2_d_2, y3_a_sz1_d_2,
							  sz1_m_sz1_d_2, sz2_m_sz2_d_2, sz3_d_2);
	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1_a_sz3_d_2, y1_a_sz1_d_2,
							  x2_a_sz2_d_2, y2_a_sz3_d_2,
							  x3_a_sz2_d_2, y3_a_sz1_d_2,
							  sz1_m_sz1_d_2, sz2_m_sz2_d_2, sz3_m_sz3_d_2);
}
vector<vector<int>> divide_and_conquer(vector<vector<int>> &mat1, vector<vector<int>> &mat2)
{
	vector<vector<int>> ans(mat1.size(), vector<int>(mat2[0].size()));
	divide_and_conquer_kernel(ans, mat1, mat2, 0, 0, 0, 0, 0, 0, mat1.size(), mat2[0].size(), mat2.size());
	return ans;
}
inline int CEIL_ODD(int n)
{
	return n % 2 ? n + 1 : n;
}
vector<vector<int>> strassen(vector<vector<int>> &mat1, vector<vector<int>> &mat2, int flag = 1)
{
	if (mat1.size() <= flag || mat2[0].size() <= flag || mat2.size() <= flag)
	{
        MULTIPLY(ans, mat1, mat2)
		return ans;
	}
	int sz1t = CEIL_ODD(mat1.size()), sz2t = CEIL_ODD(mat2[0].size()), sz3t = CEIL_ODD(mat2.size()), i, j;
	if (sz1t != mat1.size())
	{
		mat1.push_back(vector<int>(sz3t));
	}
	if (sz3t != mat2.size())
	{
		mat2.push_back(vector<int>(sz2t));
		for (i = 0; i < mat1.size(); i++)
		{
			mat1[i].push_back(0);
		}
	}
	if (sz2t != mat2[0].size())
	{
		for (i = 0; i < mat2.size(); i++)
		{
			mat2[i].push_back(0);
		}
	}
	int sz1t_d_2 = sz1t / 2;
	int sz2t_d_2 = sz2t / 2;
	int sz3t_d_2 = sz3t / 2;
	vector<vector<int>> ans(sz1t), a, b, c, d, e, f, g, h, p1, p2, p3, p4, p5, p6, p7;
	for (i = 0; i < sz1t_d_2; i++)
	{
		a.push_back(vector<int>(mat1[i].begin(), mat1[i].begin() + sz3t_d_2));
		b.push_back(vector<int>(mat1[i].begin() + sz3t_d_2, mat1[i].end()));
		c.push_back(vector<int>(mat1[sz1t_d_2 + i].begin(), mat1[sz1t_d_2 + i].begin() + sz3t_d_2));
		d.push_back(vector<int>(mat1[sz1t_d_2 + i].begin() + sz3t_d_2, mat1[sz1t_d_2 + i].end()));
	}
	for (i = 0; i < sz3t_d_2; i++)
	{
		e.push_back(vector<int>(mat2[i].begin(), mat2[i].begin() + sz2t_d_2));
		f.push_back(vector<int>(mat2[i].begin() + sz2t_d_2, mat2[i].end()));
		g.push_back(vector<int>(mat2[sz3t_d_2 + i].begin(), mat2[sz3t_d_2 + i].begin() + sz2t_d_2));
		h.push_back(vector<int>(mat2[sz3t_d_2 + i].begin() + sz2t_d_2, mat2[sz3t_d_2 + i].end()));
	}
	MINUS(f_m_h, f, h)
	ADD(a_a_b, a, b)
	ADD(c_a_d, c, d)
	MINUS(g_m_e, g, e)
	ADD(a_a_d, a, d)
	ADD(e_a_h, e, h)
	MINUS(b_m_d, b, d)
	ADD(g_a_h, g, h)
	MINUS(a_m_c, a, c)
	ADD(e_a_f, e, f)
	p1 = strassen(a, f_m_h, flag);
	p2 = strassen(a_a_b, h, flag);
	p3 = strassen(c_a_d, e, flag);
	p4 = strassen(d, g_m_e, flag);
	p5 = strassen(a_a_d, e_a_h, flag);
	p6 = strassen(b_m_d, g_a_h, flag);
	p7 = strassen(a_m_c, e_a_f, flag);
	for (i = 0; i < sz1t_d_2; i++)
	{
		for (j = 0; j < sz2t_d_2; j++)
		{
			ans[i].push_back(p5[i][j] + p4[i][j] - p2[i][j] + p6[i][j]);
			ans[i + sz1t_d_2].push_back(p3[i][j] + p4[i][j]);
		}
	}
	for (i = 0; i < sz1t_d_2; i++)
	{
		for (j = 0; j < sz2t_d_2; j++)
		{
			ans[i].push_back(p1[i][j] + p2[i][j]);
			ans[i + sz1t_d_2].push_back(p5[i][j] + p1[i][j] - p3[i][j] - p7[i][j]);
		}
	}
	if (sz1t != mat1.size())
	{
		mat1.pop_back();
		ans.pop_back();
	}
	if (sz3t != mat2.size())
	{
		mat2.pop_back();
		for (i = 0; i < mat1.size(); i++)
		{
			mat1[i].pop_back();
		}
	}
	if (sz2t != mat2[0].size())
	{
		for (i = 0; i < mat2.size() && i < mat1.size(); i++)
		{
			mat2[i].pop_back();
			ans[i].pop_back();
		}
		if (i == mat2.size())
		{
			for (; i < mat1.size(); i++)
			{
				ans[i].pop_back();
			}
		}
		else
		{
			for (; i < mat2.size(); i++)
			{
				mat1[i].pop_back();
			}
		}
	}
	return ans;
}
void init(vector<vector<int>> &mat1, vector<vector<int>> &mat2)
{
	int i, j;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < i; j++)
		{
			mat1[i].push_back(0);
			mat2[i].push_back(0);
		}
		mat1[i].push_back(1);
		mat2[i].push_back(1);
		for (j++; j < SIZE; j++)
		{
			mat1[i].push_back(0);
			mat2[i].push_back(0);
		}
	}
}
void print_mat(vector<vector<int>> &mat)
{
	int i, j;
	for (i = 0; i < mat.size(); i++)
	{
		for (j = 0; j < mat[i].size(); j++)
		{
			printf("%d ", mat[i][j]);
		}
		putchar('\n');
	}
}
void verify(vector<vector<int>> &ans, vector<vector<int>> &mat1, vector<vector<int>> &mat2)
{
	int i, j;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (ans[i][j] != mat1[i][j])
			{
				puts("Wrong!");
				return;
			}
		}
	}
	puts("Correct!");
}