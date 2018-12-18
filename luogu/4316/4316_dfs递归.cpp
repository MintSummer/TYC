#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int N=100010;
    int n,m,cnt,Head[N],deg[N],vis[N];
    double f[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct edge
    {
        int to,next,w;
    }E[N<<4];

    inline void add(int u,int v,int w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
    }

    void dfs(int u)
    {
        if(u==n) {f[u]=0;return;}
        if(vis[u]) return;
        vis[u]=1;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            dfs(v);
            f[u]+=(f[v]+E[i].w)/deg[u];
        }
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read(),w=read();
            add(u,v,w);
            deg[u]++;
        }
        dfs(1);
        printf("%.2lf",f[1]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
