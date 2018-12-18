#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=50010;
	int n,m,cnt,ans,Head[N],fa[N][20],dep[N],dis[N];

	struct edge
	{
		int to,next;
	}E[N<<1];

	void add(int u,int v)
	{
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
	}

	void dfs(int u,int f)
	{
		dep[u]=dep[f]+1;
		fa[u][0]=f;
		for(int i=1;i<=16;i++)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			dfs(v,u);
		}
	}

	inline int LCA(int u,int v)
	{
		if(dep[u]<dep[v]) swap(u,v);
		for(int t=0,d=dep[u]-dep[v];d;d>>=1,t++)
			if(d&1) u=fa[u][t];
		if(u==v) return u;
		for(int i=16;i>=0;i--)
			if(fa[u][i]!=fa[v][i])
				u=fa[u][i],v=fa[v][i];
		return fa[u][0];
	}

	void dfs(int u)
	{
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa[u][0]) continue;
			dfs(v);
			dis[u]+=dis[v];
		}
		ans=max(ans,dis[u]);
	}

	void work()
	{
		scanf("%d%d",&n,&m);
		int u,v;
		for(int i=1;i<n;i++)
		{
			scanf("%d%d",&u,&v);
			add(u,v),add(v,u);
		}
		dfs(1,0);
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&u,&v);
			int lca=LCA(u,v);
			dis[u]++,dis[v]++;
			dis[lca]--,dis[fa[lca][0]]--;
		}
		dfs(1);
		printf("%d",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
