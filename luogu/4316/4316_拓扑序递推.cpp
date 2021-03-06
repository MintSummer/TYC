#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int N=100010;
    int n,m,cnt,h,t,Head[N],deg[N],q[N],out[N];
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

    inline void search(int s)
    {
        h=1,t=0;
        q[++t]=s;
        while(h<=t)
        {
            int u=q[h++];
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                --deg[v];
                if(!deg[v]) q[++t]=v;
            }
        }
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read(),w=read();
            add(u,v,w);
            deg[v]++,out[u]++;
        }
        search(1);
        for(int i=t-1;i;i--)
            for(int j=Head[q[i]];j;j=E[j].next)
                f[q[i]]+=(f[E[j].to]+E[j].w)/out[q[i]];
        printf("%.2lf",f[1]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
