#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=500010;
    int n,m,root,cnt,Head[N],ans[N],fa[N],vis[N];
    
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

    struct node
    {
        int v,id;
    };
    vector<node> q[N];

    int find(int x)
    {
        return x==fa[x]?x:fa[x]=find(fa[x]);
    }

    void Tarjan(int u,int f)
    {
        fa[u]=u;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) continue;
            Tarjan(v,u);
            fa[find(v)]=u;
        }
		vis[u]=1;
        for(int i=0;i<q[u].size();i++)
            if(vis[q[u][i].v])
                ans[q[u][i].id]=find(q[u][i].v);
    }

    void work()
    {
        n=read(),m=read(),root=read();
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read();
            add(u,v),add(v,u);
        }
        for(int i=1;i<=n;i++)
        {
            int u=read(),v=read();
            q[u].push_back((node){v,i});
            q[v].push_back((node){u,i});
        }
        Tarjan(root,0);
        for(int i=1;i<=m;i++)
            printf("%d\n",ans[i]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
