#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=2e6+10;
    int n,m,tot,cnt,scc,top,dfstim;
    int Head[N],id[N>>1][2],dfn[N],low[N],st[N],in[N],belong[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct edge
    {
        int to,next;
    }E[N<<1];

    inline void add(int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
    }

    void Tarjan(int u)
    {
        dfn[u]=low[u]=++dfstim;
        st[++top]=u;
        in[u]=1;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(!dfn[v]) 
                Tarjan(v),low[u]=min(low[u],low[v]);
            else 
                if(in[v]) low[u]=min(low[u],dfn[v]);
        }
        if(dfn[u]==low[u])
        {
            int x;
            scc++;
            do
            {
                x=st[top--];
                belong[x]=scc;
                in[x]=0;
            }
            while(x!=u);
        }
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<=n;i++)
            id[i][0]=++tot,id[i][1]=++tot;
        for(int i=1;i<=m;i++)
        {
            int x=read(),a=read(),y=read(),b=read();
            add(id[x][a^1],id[y][b]);
            add(id[y][b^1],id[x][a]);
        }
        for(int i=1;i<=tot;i++) 
            if(!dfn[i]) Tarjan(i);
        int flag=0;
        for(int i=1;i<=n;i++)
            if(belong[id[i][0]]==belong[id[i][1]])
                {flag=1;break;}
        if(flag) puts("IMPOSSIBLE");
        else 
        {
            puts("POSSIBLE");
            for(int i=1;i<=n;i++)
                if(belong[id[i][0]]<belong[id[i][1]]) printf("0 ");
                else printf("1 ");
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}