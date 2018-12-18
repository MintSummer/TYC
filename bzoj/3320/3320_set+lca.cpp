#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<set>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1e5+10;
    int n,m,cnt,dfs_clock,Head[N],size[N],son[N],top[N],dep[N],fa[N],dfn[N],node[N],mark[N];
    ll dis[N];
    set<int> s;

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
        ll w;
    }E[N<<1];

    inline void add(int u,int v,int w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
    }

    void dfs(int u)
    {
        int hs=0;
        dep[u]=dep[fa[u]]+1;
        size[u]=1;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u]) continue;
            dis[v]=dis[u]+E[i].w;
            fa[v]=u;
            dfs(v);
            if(size[v]>size[hs]) hs=v;
            size[u]+=size[v];
        }
        son[u]=hs;
    }

    void dfs(int u,int ance)
    {
        top[u]=ance;
        dfn[u]=++dfs_clock;
        node[dfs_clock]=u;
        if(son[u]) dfs(son[u],ance);
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==fa[u]||v==son[u]) continue;
            dfs(v,v);
        }
    }

    inline int LCA(int x,int y)
    {
        while(top[x]!=top[y])
        {
            if(dep[top[x]]<dep[top[y]]) swap(x,y);
            x=fa[top[x]];
        }
        return dep[x]>dep[y]?y:x;
    }

    inline ll get_len(int x,int y)
    {
        int lca=LCA(x,y);
        return dis[x]+dis[y]-dis[lca]*2;
    }

    void work()
    {
        n=read(),m=read();
        ll total=0;
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read(),w=read();
            total+=w;
            add(u,v,w),add(v,u,w);
        }
        dfs(1);
        dfs(1,1);
        ll ans=0,len;
        s.insert(0),s.insert(n+1);
        while(m--)
        {
            int x=read(),val=(mark[x]?-1:1);
			if(!mark[x]) s.insert(dfn[x]);
            int las=*--s.find(dfn[x]),nxt=*++s.find(dfn[x]);
            if(las>=1) ans+=val*get_len(node[las],x);
            if(nxt<=n) ans+=val*get_len(x,node[nxt]);
            if(las>=1&&nxt<=n) ans+=-val*get_len(node[las],node[nxt]);
			if(mark[x]) s.erase(dfn[x]);
            int first=*++s.find(0),end=*--s.find(n+1);
            if(first>=1&&end<=n) len=get_len(node[first],node[end]);
            else len=0;
            printf("%lld\n",ans+len);
			mark[x]^=1;
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
