#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

namespace TYC
{
    const int N=210;
    int n,cnt,dfs_clock,scc,top,Head[N],dfn[N],low[N],st[N],in[N],belong[N],deg[N];

    struct edge
    {
        int to,next;
    }E[800010];

    inline void add(int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
    }

    void Tarjan(int u)
    {
        dfn[u]=low[u]=++dfs_clock;
        in[u]=1;
        st[++top]=u;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(!dfn[v])
                Tarjan(v),low[u]=min(low[u],low[v]);
            else if(in[v]) low[u]=min(low[u],dfn[v]);
        }
        if(low[u]==dfn[u])
        {
            scc++;
            int x;
            do
            {
                x=st[top--];
                in[x]=0;
                belong[x]=scc;
            }
            while(x!=u);
        }
    }

    void work()
    {
        scanf("%d",&n);
        int x;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&x);
            while(x) add(i,x),scanf("%d",&x);
        }
        for(int i=1;i<=n;i++) 
            if(!dfn[i]) Tarjan(i);
        for(int u=1;u<=n;u++)
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(belong[u]!=belong[v]) 
                    deg[belong[v]]++;
            }
        int ans=0;
        for(int i=1;i<=scc;i++)
            ans+=(!deg[i]);
        printf("%d\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
