#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=3e5+10;
    int n,m,cnt,Head[N],ans[N],tim[N],s[N],t[N],dep[N],fa[N][22],backet[N<<3],val[N];
    vector<int> link[N],dis1[N],dis2[N];

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

    struct Question
    {
        int s,t,lca,len;
    }a[N];

    void dfs(int u,int f)
    {
        dep[u]=dep[f]+1;
        fa[u][0]=f;
        for(int i=1;i<=19&&fa[u][i-1];i++)
            fa[u][i]=fa[fa[u][i-1]][i-1];
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) continue;
            dfs(v,u);
        }
    }

    int LCA(int u,int v)
    {
        if(dep[u]<dep[v]) swap(u,v);
        for(int d=dep[u]-dep[v],t=0;d;d>>=1,t++)
            if(d&1) u=fa[u][t];
        if(u==v) return u;
        for(int i=19;i>=0;i--)
            if(fa[u][i]!=fa[v][i])
                u=fa[u][i],v=fa[v][i];
        return fa[u][0];
    }

    void search1(int u,int f)
    {
        int before=backet[tim[u]+dep[u]];
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) continue;
            search1(v,u);
        }
        backet[dep[u]]+=val[u];
        ans[u]+=backet[tim[u]+dep[u]]-before;
        for(int i=0;i<link[u].size();i++)
            backet[dep[link[u][i]]]--;
    }

    void search2(int u,int f)
    {
        int before=backet[tim[u]-dep[u]+N];
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) continue;
            search2(v,u);
        }
        for(int i=0;i<dis1[u].size();i++)
            backet[dis1[u][i]+N]++;
        ans[u]+=backet[tim[u]-dep[u]+N]-before;
        for(int i=0;i<dis2[u].size();i++)
            backet[dis2[u][i]+N]--;
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read();
            add(u,v),add(v,u);
        }
        dep[0]=-1;
        dfs(1,0);
        for(int i=1;i<=n;i++) tim[i]=read();
        for(int i=1;i<=m;i++)
        {
            int s=read(),t=read();
            val[s]++;
            a[i].s=s,a[i].t=t;
            int lca=a[i].lca=LCA(s,t);
            a[i].len=dep[s]+dep[t]-dep[lca]-dep[fa[lca][0]]-1;
            link[lca].push_back(s);
        }
        search1(1,0);
        for(int i=1;i<=m;i++)
        {
            int dis=a[i].len-dep[a[i].t];
            dis1[a[i].t].push_back(dis);
            dis2[a[i].lca].push_back(dis);
        }
        search2(1,0);
        for(int i=1;i<=m;i++)
            if(dep[a[i].s]-dep[a[i].lca]==tim[a[i].lca]) 
                ans[a[i].lca]--;
        for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    }
}

int main()
{
    TYC::work();
    return 0;
}