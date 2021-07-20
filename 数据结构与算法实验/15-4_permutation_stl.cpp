/*
next_permutation(a, a + n)将a[0, n)修改为重排列的下一项，对应prev_permutation
*/
#include<bits/stdc++.h>
using namespace std;
int a[10005],n,m;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)scanf("%d",&a[i]);
    while(m--)    next_permutation(a,a+n);
    for(int i=0;i<n-1;i++)    printf("%d ",a[i]);    printf("%d",a[n-1]);
    return 0;
}
