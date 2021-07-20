#include <iostream>
#include <pthread.h>
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
				printf("(%d, %d): %d", i, j, ans[i][j]);
				return;
			}
		}
	}
	puts("Correct!");
}
struct thread_divide_and_conquer_kernel_para_no_lock
{
	vector<vector<int>> *ans;
	vector<vector<int>> *mat1;
	vector<vector<int>> *mat2;
	int x1;
	int y1;
	int x2;
	int y2;
	int x3;
	int y3;
	int sz1;
	int sz2;
	int sz3;
	thread_divide_and_conquer_kernel_para_no_lock(vector<vector<int>> *a,
												  vector<vector<int>> *m1,
												  vector<vector<int>> *m2)
	{
		ans = a;
		mat1 = m1;
		mat2 = m2;
	}
};
void *divide_and_conquer_kernel_thread_version_no_lock(void *para)
{
	thread_divide_and_conquer_kernel_para_no_lock *real_para = (thread_divide_and_conquer_kernel_para_no_lock *)para;
	int x1 = real_para->x1;
	int y1 = real_para->y1;
	int x2 = real_para->x2;
	int y2 = real_para->y2;
	int x3 = real_para->x3;
	int y3 = real_para->y3;
	int sz1 = real_para->sz1;
	int sz2 = real_para->sz2;
	int sz3 = real_para->sz3;
	if (sz1 == 0 || sz2 == 0 || sz3 == 0)
	{
		return nullptr;
	}
	if (sz1 == 1 && sz2 == 1 && sz3 == 1)
	{
		(*real_para->ans)[x3][y3] += (*real_para->mat1)[x1][y1] * (*real_para->mat2)[x2][y2];
		return nullptr;
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
	divide_and_conquer_kernel((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
							  x1, y1,
							  x2, y2,
							  x3, y3,
							  sz1_d_2, sz2_d_2, sz3_d_2);
	divide_and_conquer_kernel((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
							  x1_a_sz3_d_2, y1,
							  x2, y2_a_sz3_d_2,
							  x3, y3,
							  sz1_d_2, sz2_d_2, sz3_m_sz3_d_2);
	divide_and_conquer_kernel((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
							  x1, y1,
							  x2_a_sz2_d_2, y2,
							  x3_a_sz2_d_2, y3,
							  sz1_d_2, sz2_m_sz2_d_2, sz3_d_2);
	divide_and_conquer_kernel((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
							  x1_a_sz3_d_2, y1,
							  x2_a_sz2_d_2, y2_a_sz3_d_2,
							  x3_a_sz2_d_2, y3,
							  sz1_d_2, sz2_m_sz2_d_2, sz3_m_sz3_d_2);
	divide_and_conquer_kernel((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
							  x1, y1_a_sz1_d_2,
							  x2, y2,
							  x3, y3_a_sz1_d_2,
							  sz1_m_sz1_d_2, sz2_d_2, sz3_d_2);
	divide_and_conquer_kernel((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
							  x1_a_sz3_d_2, y1_a_sz1_d_2,
							  x2, y2_a_sz3_d_2,
							  x3, y3_a_sz1_d_2,
							  sz1_m_sz1_d_2, sz2_d_2, sz3_m_sz3_d_2);
	divide_and_conquer_kernel((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
							  x1, y1_a_sz1_d_2,
							  x2_a_sz2_d_2, y2,
							  x3_a_sz2_d_2, y3_a_sz1_d_2,
							  sz1_m_sz1_d_2, sz2_m_sz2_d_2, sz3_d_2);
	divide_and_conquer_kernel((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
							  x1_a_sz3_d_2, y1_a_sz1_d_2,
							  x2_a_sz2_d_2, y2_a_sz3_d_2,
							  x3_a_sz2_d_2, y3_a_sz1_d_2,
							  sz1_m_sz1_d_2, sz2_m_sz2_d_2, sz3_m_sz3_d_2);
	return nullptr;
}
vector<vector<int>> thread_divide_and_conquer_no_lock(vector<vector<int>> &mat1, vector<vector<int>> &mat2)
{
	vector<vector<int>> ans(mat1.size(), vector<int>(mat2[0].size()));
	int sz1_d_2 = mat1.size() / 2;
	int sz2_d_2 = mat2[0].size() / 2;
	int sz3_d_2 = mat2.size() / 2;
	int sz1_m_sz1_d_2 = mat1.size() - sz1_d_2;
	int sz2_m_sz2_d_2 = mat2[0].size() - sz2_d_2;
	int sz3_m_sz3_d_2 = mat2.size() - sz3_d_2;
	int x1_a_sz3_d_2 = sz3_d_2;
	int y1_a_sz1_d_2 = sz1_d_2;
	int x2_a_sz2_d_2 = sz2_d_2;
	int y2_a_sz3_d_2 = sz3_d_2;
	int x3_a_sz2_d_2 = sz2_d_2;
	int y3_a_sz1_d_2 = sz1_d_2;
	thread_divide_and_conquer_kernel_para_no_lock
		*para0 = new thread_divide_and_conquer_kernel_para_no_lock(&ans, &mat1, &mat2),
		*para1 = new thread_divide_and_conquer_kernel_para_no_lock(&ans, &mat1, &mat2),
		*para2 = new thread_divide_and_conquer_kernel_para_no_lock(&ans, &mat1, &mat2),
		*para3 = new thread_divide_and_conquer_kernel_para_no_lock(&ans, &mat1, &mat2),
		*para4 = new thread_divide_and_conquer_kernel_para_no_lock(&ans, &mat1, &mat2),
		*para5 = new thread_divide_and_conquer_kernel_para_no_lock(&ans, &mat1, &mat2),
		*para6 = new thread_divide_and_conquer_kernel_para_no_lock(&ans, &mat1, &mat2),
		*para7 = new thread_divide_and_conquer_kernel_para_no_lock(&ans, &mat1, &mat2);
	para0->x1 = 0;
	para0->y1 = 0;
	para0->x2 = 0;
	para0->y2 = 0;
	para0->x3 = 0;
	para0->y3 = 0;
	para0->sz1 = sz1_d_2;
	para0->sz2 = sz2_d_2;
	para0->sz3 = sz3_d_2;
	para1->x1 = x1_a_sz3_d_2;
	para1->y1 = 0;
	para1->x2 = 0;
	para1->y2 = y2_a_sz3_d_2;
	para1->x3 = 0;
	para1->y3 = 0;
	para1->sz1 = sz1_d_2;
	para1->sz2 = sz2_d_2;
	para1->sz3 = sz3_m_sz3_d_2;
	para2->x1 = 0;
	para2->y1 = 0;
	para2->x2 = x2_a_sz2_d_2;
	para2->y2 = 0;
	para2->x3 = x3_a_sz2_d_2;
	para2->y3 = 0;
	para2->sz1 = sz1_d_2;
	para2->sz2 = sz2_m_sz2_d_2;
	para2->sz3 = sz3_d_2;
	para3->x1 = x1_a_sz3_d_2;
	para3->y1 = 0;
	para3->x2 = x2_a_sz2_d_2;
	para3->y2 = y2_a_sz3_d_2;
	para3->x3 = x3_a_sz2_d_2;
	para3->y3 = 0;
	para3->sz1 = sz1_d_2;
	para3->sz2 = sz2_m_sz2_d_2;
	para3->sz3 = sz3_m_sz3_d_2;
	para4->x1 = 0;
	para4->y1 = y1_a_sz1_d_2;
	para4->x2 = 0;
	para4->y2 = 0;
	para4->x3 = 0;
	para4->y3 = y3_a_sz1_d_2;
	para4->sz1 = sz1_m_sz1_d_2;
	para4->sz2 = sz2_d_2;
	para4->sz3 = sz3_d_2;
	para5->x1 = x1_a_sz3_d_2;
	para5->y1 = y1_a_sz1_d_2;
	para5->x2 = 0;
	para5->y2 = y2_a_sz3_d_2;
	para5->x3 = 0;
	para5->y3 = y3_a_sz1_d_2;
	para5->sz1 = sz1_m_sz1_d_2;
	para5->sz2 = sz2_d_2;
	para5->sz3 = sz3_m_sz3_d_2;
	para6->x1 = 0;
	para6->y1 = y1_a_sz1_d_2;
	para6->x2 = x2_a_sz2_d_2;
	para6->y2 = 0;
	para6->x3 = x3_a_sz2_d_2;
	para6->y3 = y3_a_sz1_d_2;
	para6->sz1 = sz1_m_sz1_d_2;
	para6->sz2 = sz2_m_sz2_d_2;
	para6->sz3 = sz3_d_2;
	para7->x1 = x1_a_sz3_d_2;
	para7->y1 = y1_a_sz1_d_2;
	para7->x2 = x2_a_sz2_d_2;
	para7->y2 = y2_a_sz3_d_2;
	para7->x3 = x3_a_sz2_d_2;
	para7->y3 = y3_a_sz1_d_2;
	para7->sz1 = sz1_m_sz1_d_2;
	para7->sz2 = sz2_m_sz2_d_2;
	para7->sz3 = sz3_m_sz3_d_2;
	pthread_t t0, t1, t2, t3, t4, t5, t6;
	pthread_create(&t0, NULL, divide_and_conquer_kernel_thread_version_no_lock, (void *)para0);
	pthread_create(&t1, NULL, divide_and_conquer_kernel_thread_version_no_lock, (void *)para1);
	pthread_create(&t2, NULL, divide_and_conquer_kernel_thread_version_no_lock, (void *)para2);
	pthread_create(&t3, NULL, divide_and_conquer_kernel_thread_version_no_lock, (void *)para3);
	pthread_create(&t4, NULL, divide_and_conquer_kernel_thread_version_no_lock, (void *)para4);
	pthread_create(&t5, NULL, divide_and_conquer_kernel_thread_version_no_lock, (void *)para5);
	pthread_create(&t6, NULL, divide_and_conquer_kernel_thread_version_no_lock, (void *)para6);
	divide_and_conquer_kernel_thread_version_no_lock((void *)para7);
	pthread_join(t0, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_join(t5, NULL);
	pthread_join(t6, NULL);
	return ans;
}
struct thread_divide_and_conquer_kernel_para
{
	vector<vector<int>> *ans;
	vector<vector<int>> *mat1;
	vector<vector<int>> *mat2;
	int x1;
	int y1;
	int x2;
	int y2;
	int x3;
	int y3;
	int sz1;
	int sz2;
	int sz3;
	pthread_spinlock_t *lock;
	thread_divide_and_conquer_kernel_para(vector<vector<int>> *a,
										  vector<vector<int>> *m1,
										  vector<vector<int>> *m2,
										  pthread_spinlock_t *lk)
	{
		ans = a;
		mat1 = m1;
		mat2 = m2;
		lock = lk;
	}
};
void divide_and_conquer_kernel_lock_version(vector<vector<int>> &ans, vector<vector<int>> &mat1, vector<vector<int>> &mat2,
											int x1, int y1, int x2, int y2, int x3, int y3,
											int sz1, int sz2, int sz3,
											pthread_spinlock_t *lock)
{
	if (sz1 == 0 || sz2 == 0 || sz3 == 0)
	{
		return;
	}
	if (sz1 == 1 && sz2 == 1 && sz3 == 1)
	{
		pthread_spin_lock(lock);
		ans[x3][y3] += mat1[x1][y1] * mat2[x2][y2];
		pthread_spin_unlock(lock);
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
	divide_and_conquer_kernel_lock_version(ans, mat1, mat2,
										   x1, y1,
										   x2, y2,
										   x3, y3,
										   sz1_d_2, sz2_d_2, sz3_d_2,
										   lock);
	divide_and_conquer_kernel_lock_version(ans, mat1, mat2,
										   x1_a_sz3_d_2, y1,
										   x2, y2_a_sz3_d_2,
										   x3, y3,
										   sz1_d_2, sz2_d_2, sz3_m_sz3_d_2,
										   lock);
	divide_and_conquer_kernel_lock_version(ans, mat1, mat2,
										   x1, y1,
										   x2_a_sz2_d_2, y2,
										   x3_a_sz2_d_2, y3,
										   sz1_d_2, sz2_m_sz2_d_2, sz3_d_2,
										   lock);
	divide_and_conquer_kernel_lock_version(ans, mat1, mat2,
										   x1_a_sz3_d_2, y1,
										   x2_a_sz2_d_2, y2_a_sz3_d_2,
										   x3_a_sz2_d_2, y3,
										   sz1_d_2, sz2_m_sz2_d_2, sz3_m_sz3_d_2,
										   lock);
	divide_and_conquer_kernel_lock_version(ans, mat1, mat2,
										   x1, y1_a_sz1_d_2,
										   x2, y2,
										   x3, y3_a_sz1_d_2,
										   sz1_m_sz1_d_2, sz2_d_2, sz3_d_2,
										   lock);
	divide_and_conquer_kernel_lock_version(ans, mat1, mat2,
										   x1_a_sz3_d_2, y1_a_sz1_d_2,
										   x2, y2_a_sz3_d_2,
										   x3, y3_a_sz1_d_2,
										   sz1_m_sz1_d_2, sz2_d_2, sz3_m_sz3_d_2,
										   lock);
	divide_and_conquer_kernel_lock_version(ans, mat1, mat2,
										   x1, y1_a_sz1_d_2,
										   x2_a_sz2_d_2, y2,
										   x3_a_sz2_d_2, y3_a_sz1_d_2,
										   sz1_m_sz1_d_2, sz2_m_sz2_d_2, sz3_d_2,
										   lock);
	divide_and_conquer_kernel_lock_version(ans, mat1, mat2,
										   x1_a_sz3_d_2, y1_a_sz1_d_2,
										   x2_a_sz2_d_2, y2_a_sz3_d_2,
										   x3_a_sz2_d_2, y3_a_sz1_d_2,
										   sz1_m_sz1_d_2, sz2_m_sz2_d_2, sz3_m_sz3_d_2,
										   lock);
}
void *divide_and_conquer_kernel_thread_version(void *para)
{
	thread_divide_and_conquer_kernel_para *real_para = (thread_divide_and_conquer_kernel_para *)para;
	int x1 = real_para->x1;
	int y1 = real_para->y1;
	int x2 = real_para->x2;
	int y2 = real_para->y2;
	int x3 = real_para->x3;
	int y3 = real_para->y3;
	int sz1 = real_para->sz1;
	int sz2 = real_para->sz2;
	int sz3 = real_para->sz3;
	pthread_spinlock_t *lock = real_para->lock;
	if (sz1 == 0 || sz2 == 0 || sz3 == 0)
	{
		return nullptr;
	}
	if (sz1 == 1 && sz2 == 1 && sz3 == 1)
	{
		pthread_spin_lock(lock);
		(*real_para->ans)[x3][y3] += (*real_para->mat1)[x1][y1] * (*real_para->mat2)[x2][y2];
		pthread_spin_unlock(lock);
		return nullptr;
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
	divide_and_conquer_kernel_lock_version((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
										   x1, y1,
										   x2, y2,
										   x3, y3,
										   sz1_d_2, sz2_d_2, sz3_d_2,
										   lock);
	divide_and_conquer_kernel_lock_version((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
										   x1_a_sz3_d_2, y1,
										   x2, y2_a_sz3_d_2,
										   x3, y3,
										   sz1_d_2, sz2_d_2, sz3_m_sz3_d_2,
										   lock);
	divide_and_conquer_kernel_lock_version((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
										   x1, y1,
										   x2_a_sz2_d_2, y2,
										   x3_a_sz2_d_2, y3,
										   sz1_d_2, sz2_m_sz2_d_2, sz3_d_2,
										   lock);
	divide_and_conquer_kernel_lock_version((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
										   x1_a_sz3_d_2, y1,
										   x2_a_sz2_d_2, y2_a_sz3_d_2,
										   x3_a_sz2_d_2, y3,
										   sz1_d_2, sz2_m_sz2_d_2, sz3_m_sz3_d_2,
										   lock);
	divide_and_conquer_kernel_lock_version((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
										   x1, y1_a_sz1_d_2,
										   x2, y2,
										   x3, y3_a_sz1_d_2,
										   sz1_m_sz1_d_2, sz2_d_2, sz3_d_2,
										   lock);
	divide_and_conquer_kernel_lock_version((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
										   x1_a_sz3_d_2, y1_a_sz1_d_2,
										   x2, y2_a_sz3_d_2,
										   x3, y3_a_sz1_d_2,
										   sz1_m_sz1_d_2, sz2_d_2, sz3_m_sz3_d_2,
										   lock);
	divide_and_conquer_kernel_lock_version((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
										   x1, y1_a_sz1_d_2,
										   x2_a_sz2_d_2, y2,
										   x3_a_sz2_d_2, y3_a_sz1_d_2,
										   sz1_m_sz1_d_2, sz2_m_sz2_d_2, sz3_d_2,
										   lock);
	divide_and_conquer_kernel_lock_version((*real_para->ans), (*real_para->mat1), (*real_para->mat2),
										   x1_a_sz3_d_2, y1_a_sz1_d_2,
										   x2_a_sz2_d_2, y2_a_sz3_d_2,
										   x3_a_sz2_d_2, y3_a_sz1_d_2,
										   sz1_m_sz1_d_2, sz2_m_sz2_d_2, sz3_m_sz3_d_2,
										   lock);
	return nullptr;
}
vector<vector<int>> thread_divide_and_conquer(vector<vector<int>> &mat1, vector<vector<int>> &mat2)
{
	vector<vector<int>> ans(mat1.size(), vector<int>(mat2[0].size()));
	int sz1_d_2 = mat1.size() / 2;
	int sz2_d_2 = mat2[0].size() / 2;
	int sz3_d_2 = mat2.size() / 2;
	int sz1_m_sz1_d_2 = mat1.size() - sz1_d_2;
	int sz2_m_sz2_d_2 = mat2[0].size() - sz2_d_2;
	int sz3_m_sz3_d_2 = mat2.size() - sz3_d_2;
	int x1_a_sz3_d_2 = sz3_d_2;
	int y1_a_sz1_d_2 = sz1_d_2;
	int x2_a_sz2_d_2 = sz2_d_2;
	int y2_a_sz3_d_2 = sz3_d_2;
	int x3_a_sz2_d_2 = sz2_d_2;
	int y3_a_sz1_d_2 = sz1_d_2;
	pthread_spinlock_t *lock = new pthread_spinlock_t;
	pthread_spin_init(lock, 0);
	thread_divide_and_conquer_kernel_para
		*para0 = new thread_divide_and_conquer_kernel_para(&ans, &mat1, &mat2, lock),
		*para1 = new thread_divide_and_conquer_kernel_para(&ans, &mat1, &mat2, lock),
		*para2 = new thread_divide_and_conquer_kernel_para(&ans, &mat1, &mat2, lock),
		*para3 = new thread_divide_and_conquer_kernel_para(&ans, &mat1, &mat2, lock),
		*para4 = new thread_divide_and_conquer_kernel_para(&ans, &mat1, &mat2, lock),
		*para5 = new thread_divide_and_conquer_kernel_para(&ans, &mat1, &mat2, lock),
		*para6 = new thread_divide_and_conquer_kernel_para(&ans, &mat1, &mat2, lock),
		*para7 = new thread_divide_and_conquer_kernel_para(&ans, &mat1, &mat2, lock);
	para0->x1 = 0;
	para0->y1 = 0;
	para0->x2 = 0;
	para0->y2 = 0;
	para0->x3 = 0;
	para0->y3 = 0;
	para0->sz1 = sz1_d_2;
	para0->sz2 = sz2_d_2;
	para0->sz3 = sz3_d_2;
	para1->x1 = x1_a_sz3_d_2;
	para1->y1 = 0;
	para1->x2 = 0;
	para1->y2 = y2_a_sz3_d_2;
	para1->x3 = 0;
	para1->y3 = 0;
	para1->sz1 = sz1_d_2;
	para1->sz2 = sz2_d_2;
	para1->sz3 = sz3_m_sz3_d_2;
	para2->x1 = 0;
	para2->y1 = 0;
	para2->x2 = x2_a_sz2_d_2;
	para2->y2 = 0;
	para2->x3 = x3_a_sz2_d_2;
	para2->y3 = 0;
	para2->sz1 = sz1_d_2;
	para2->sz2 = sz2_m_sz2_d_2;
	para2->sz3 = sz3_d_2;
	para3->x1 = x1_a_sz3_d_2;
	para3->y1 = 0;
	para3->x2 = x2_a_sz2_d_2;
	para3->y2 = y2_a_sz3_d_2;
	para3->x3 = x3_a_sz2_d_2;
	para3->y3 = 0;
	para3->sz1 = sz1_d_2;
	para3->sz2 = sz2_m_sz2_d_2;
	para3->sz3 = sz3_m_sz3_d_2;
	para4->x1 = 0;
	para4->y1 = y1_a_sz1_d_2;
	para4->x2 = 0;
	para4->y2 = 0;
	para4->x3 = 0;
	para4->y3 = y3_a_sz1_d_2;
	para4->sz1 = sz1_m_sz1_d_2;
	para4->sz2 = sz2_d_2;
	para4->sz3 = sz3_d_2;
	para5->x1 = x1_a_sz3_d_2;
	para5->y1 = y1_a_sz1_d_2;
	para5->x2 = 0;
	para5->y2 = y2_a_sz3_d_2;
	para5->x3 = 0;
	para5->y3 = y3_a_sz1_d_2;
	para5->sz1 = sz1_m_sz1_d_2;
	para5->sz2 = sz2_d_2;
	para5->sz3 = sz3_m_sz3_d_2;
	para6->x1 = 0;
	para6->y1 = y1_a_sz1_d_2;
	para6->x2 = x2_a_sz2_d_2;
	para6->y2 = 0;
	para6->x3 = x3_a_sz2_d_2;
	para6->y3 = y3_a_sz1_d_2;
	para6->sz1 = sz1_m_sz1_d_2;
	para6->sz2 = sz2_m_sz2_d_2;
	para6->sz3 = sz3_d_2;
	para7->x1 = x1_a_sz3_d_2;
	para7->y1 = y1_a_sz1_d_2;
	para7->x2 = x2_a_sz2_d_2;
	para7->y2 = y2_a_sz3_d_2;
	para7->x3 = x3_a_sz2_d_2;
	para7->y3 = y3_a_sz1_d_2;
	para7->sz1 = sz1_m_sz1_d_2;
	para7->sz2 = sz2_m_sz2_d_2;
	para7->sz3 = sz3_m_sz3_d_2;
	pthread_t t0, t1, t2, t3, t4, t5, t6;
	pthread_create(&t0, NULL, divide_and_conquer_kernel_thread_version, (void *)para0);
	pthread_create(&t1, NULL, divide_and_conquer_kernel_thread_version, (void *)para1);
	pthread_create(&t2, NULL, divide_and_conquer_kernel_thread_version, (void *)para2);
	pthread_create(&t3, NULL, divide_and_conquer_kernel_thread_version, (void *)para3);
	pthread_create(&t4, NULL, divide_and_conquer_kernel_thread_version, (void *)para4);
	pthread_create(&t5, NULL, divide_and_conquer_kernel_thread_version, (void *)para5);
	pthread_create(&t6, NULL, divide_and_conquer_kernel_thread_version, (void *)para6);
	divide_and_conquer_kernel_thread_version((void *)para7);
	pthread_join(t0, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_join(t5, NULL);
	pthread_join(t6, NULL);
	return ans;
}