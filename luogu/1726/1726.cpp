#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cctype>
#include<vector>
using namespace std;

namespace TYC
{
    const int N=5010,M=50010;
    int n,m,cnt,dfstim,tot,top,in[N],belong[N],st[N],low[N],dfn[N],Head[N];

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
    }E[M<<1];

    struct SCC
    {
        vector<int> node;
        bool operator < (const SCC &t) const
        {
            return node.size()>t.node.size();
        }
    }scc[N];

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
            else if(in[v]) 
                low[u]=min(low[u],dfn[v]);
        }
        if(dfn[u]==low[u])
        {
            tot++;
            int x;
            do
            {
                x=st[top--];
                belong[x]=tot;
                in[x]=0;
                scc[tot].node.push_back(x);
            }
            while(x!=u);
        }
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read(),opt=read();
            add(u,v);
            if(opt==2) add(v,u);
        }
        for(int i=1;i<=n;i++)
            if(!dfn[i]) Tarjan(i);
        sort(scc+1,scc+1+tot);
        int num=0,SIZE=scc[1].node.size();
        printf("%d\n",SIZE);
        for(int i=1;i<=n;i++)
            if(scc[i].node.size()==SIZE) num++;
        for(int i=1;i<=num;i++)
            sort(scc[i].node.begin(),scc[i].node.end());
        if(num==1)
        {
            for(int i=0;i<SIZE;i++)
                printf("%d ",scc[1].node[i]);
            return;
        }
        for(int i=0;i<SIZE;i++)
        {
            int flag=0;
            for(int j=2;j<=num;j++)
                if(scc[j].node[i]!=scc[1].node[i]) 
                    {flag=1;break;}
            if(!flag) continue;
            int id=1;
            for(int j=2;j<=num;j++)
                if(scc[j].node[i]<scc[id].node[i]) id=j;
            for(int j=0;j<SIZE;j++)
                printf("%d ",scc[id].node[j]);
            return;
        }
        for(int i=0;i<scc[1].node.size();i++)
                printf("%d ",scc[1].node[i]);
    }
}

int main()
{
    TYC::work();
    return 0;    
}