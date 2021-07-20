#include <iostream>
#define MAXN 1000
using namespace std;
struct node
{
    int value;
    node *next;
    node(int v, node *n) : value(v), next(n){};
};
node *a;
int n;
int b[MAXN];
int ans[MAXN];
int gcd_table[MAXN + 1][MAXN + 1];
//调用时一定0 <= a <= b
int euclid(int a, int b)
{
    if (gcd_table[a][b] == 0)
    {
        if (a == 0)
        {
            gcd_table[a][b] = b;
        }
        else
        {
            gcd_table[a][b] = euclid(b % a, a);
        }
    }
    return gcd_table[a][b];
}
void dfs(int index)
{
    node *cur = a;
    int gcd = cur->value;
    cur = cur->next;
    while (cur != nullptr)
    {
        gcd = euclid(gcd, cur->value);
        cur = cur->next;
    }
    if (gcd < ans[index])
    {
        return;
    }
    b[index] = gcd;
    if (index == n - 1)
    {
        for (int i = 0; i < n; i++)
        {
            ans[i] = b[i];
        }
    }
    node *last = nullptr;
    cur = a;
    while (cur->next != nullptr)
    {
        if (cur == a)
        {
            a = cur->next;
            dfs(index + 1);
            a = cur;
        }
        else
        {
            last->next = cur->next;
            dfs(index + 1);
            last->next = cur;
        }
        last = cur;
        cur = cur->next;
    }
}
int main()
{
    scanf("%d", &n);
    a = new node(n, nullptr);
    for (int i = n - 1; i >= 1; i--)
    {
        a = new node(i, a);
    }
    dfs(0);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", ans[i]);
    }
}