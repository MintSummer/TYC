#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=15010,M=30010;
    typedef long long ll;
    int n,m,q,cnt,tot,tim,ffa[N*2],Head[N*2],dep[N*2],fa[N*2][20];
    ll val[M*2];
    
    struct k_edge
    {
		int u,v;
		ll w;
		bool operator < (const k_edge &a) const
		{
		    return w<a.w;
		}
    }e[M];

    struct edge
    {
		int to,next;
    }E[N*5];

    void add(int u,int v)
    {
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
    }

    int find(int a)
    {
		return ffa[a]==a?a:ffa[a]=find(ffa[a]);
    }

    void kruskal()
    {
		for(int i=1;i<=n;i++) ffa[i]=i;
		sort(e+1,e+1+m);
		tot=n;
		for(int i=1;i<=m;i++)
		{
		    int fu=find(e[i].u),fv=find(e[i].v);
		    if(fu==fv) continue;
		    tot++;
		    val[tot]=e[i].w;
		    ffa[fu]=ffa[fv]=ffa[tot]=tot;
		    add(tot,fu),add(fu,tot);
		    add(tot,fv),add(fv,tot);
		    if(tot-n==n-1) return;
		}
    }

    void dfs(int u,int f)
    {
		for(int i=Head[u];i;i=E[i].next)
		{
		    int v=E[i].to;
		    if(v==f) continue;
		    dep[v]=dep[u]+1;
		    fa[v][0]=u;
		    dfs(v,u);
		}
    }

    void init()	
    {
		tim=(int)log(tot)/log(2)+1;
		for(int j=1;j<=tim;j++)
		    for(int i=1;i<=tot;i++)
				fa[i][j]=fa[fa[i][j-1]][j-1];
    }

    int lca(int u,int v)
    {
		if(dep[u]<dep[v]) swap(u,v);
		for(int d=dep[u]-dep[v],t=0;t<=tim&&d;d>>=1,t++)
		    if(d&1) u=fa[u][t];
		if(u==v) return u;
		for(int i=tim;i>=0;i--)
		    if(fa[u][i]!=fa[v][i])
				u=fa[u][i],v=fa[v][i];
		return fa[u][0];
    }

    void work()
    {
		scanf("%d%d%d",&n,&m,&q);
		int u,v;ll w;
		for(int i=1;i<=m;i++)
		{
		    scanf("%d%d%lld",&u,&v,&w);
		    e[i]=(k_edge){u,v,w};
		}
		kruskal();
		dep[tot]=1;
		dfs(tot,0);
		init();
		while(q--)
		{
		    scanf("%d%d",&u,&v);
		    printf("%lld\n",val[lca(u,v)]);
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
