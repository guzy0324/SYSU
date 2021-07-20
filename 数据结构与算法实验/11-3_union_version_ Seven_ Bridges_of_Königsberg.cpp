#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,fa[1010],cnt[1010]={0},ans=0;
bool dg[1010],visit[1010];
long long read()//快读 
{
    long long ans=0;
    char ch=getchar(),last=' ';
    while(ch<'0'||ch>'9')
    {last=ch;ch=getchar();}
    while(ch>='0'&&ch<='9')
    {ans=ans*10+ch-'0';ch=getchar();}
    if(last=='-')ans=-ans;
    return ans;
}
int get(int k)//寻找根节点 
{
    if(fa[k]==k)return k;
    else return fa[k]=get(fa[k]);
}
void Union(int x,int y)//合并 
{
    fa[get(x)]=get(y);
}
int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
     fa[i]=i;
    for(int i=1;i<=m;i++){
     a=read();b=read();
     dg[a]=!dg[a];dg[b]=!dg[b];
     //真为奇数，假为偶数 
     visit[a]=true;
     visit[b]=true;
     //访问过标记为true
     if(get(a)!=get(b))Union(a,b);
     //如果不在一个集合就合并 
    }
    for(int i=1;i<=n;i++){
     if(dg[i])cnt[get(i)]++;
     //统计每个点所在的图共有几个度数为奇数的 
    }
    for(int i=1;i<=n;i++){
        if(get(i)==i&&visit[i]){
        //如果是根节点同时已经被访问过 
         if(cnt[i]>0)ans+=cnt[i]>>1;
         //加上该图的答案 
         else ans++;
         //否则该图可以一笔画，答案加1 
        }
    }
    cout<<ans;
    return 0;
}
