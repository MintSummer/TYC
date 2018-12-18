//最大生成树+倍增LCA 
#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int MAXN=10010,P=18,inf=0x3f3f3f3f;
	int n,m,q,cnt,Head[MAXN],ffa[MAXN],fa[MAXN][22],mn[MAXN][22],dep[MAXN],vis[MAXN];
	
	struct Edge
	{
		int u,v,w;
		bool operator < (const Edge &a) const
		{
			return w>a.w;
		}
	}e[50010];
	
	struct edge
	{
		int to,next,w;
	}E[MAXN*2];
	
	void add(int u,int v,int w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}
	
	int find(int a)
	{
		return a==ffa[a]?a:ffa[a]=find(ffa[a]);
	}
	
	void kruskal()
	{
		for(int i=1;i<=n;i++) ffa[i]=i;
		sort(e+1,e+1+m);
		int nume=0;
		for(int i=1;i<=m;i++)
		{
			int u=e[i].u,v=e[i].v;
			int fu=find(u),fv=find(v);
			if(fu==fv) continue;
			ffa[fv]=fu;
			add(u,v,e[i].w),add(v,u,e[i].w);
			if(++nume==n-1) return;
		}
	}
	
	void dfs(int u)
	{
		vis[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]) continue;
			dep[v]=dep[u]+1;
			fa[v][0]=u;
			mn[v][0]=E[i].w;
			dfs(v);
		}
	}
	
	void init()
	{
		for(int j=1;j<=P;j++)
			for(int i=1;i<=n;i++)
			{
				fa[i][j]=fa[fa[i][j-1]][j-1];
				mn[i][j]=min(mn[i][j-1],mn[fa[i][j-1]][j-1]);
			}
	}
	
	int get_ans(int x,int y)
	{
		if(find(x)!=find(y)) return -1; 
		int ans=inf;
		if(dep[x]<dep[y]) swap(x,y);
		for(int d=dep[x]-dep[y],t=0;d;d>>=1,t++)
			if(d&1) ans=min(ans,mn[x][t]),x=fa[x][t];
		if(x==y) return ans;
		for(int i=P;i>=0;i--)
			if(fa[x][i]!=fa[y][i])
			{
				ans=min(ans,min(mn[x][i],mn[y][i]));
				x=fa[x][i],y=fa[y][i];		
			}
		return min(ans,min(mn[x][0],mn[y][0]));
	}

	void work()
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
			scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
		kruskal();
		memset(mn,inf,sizeof(mn));
		for(int i=1;i<=n;i++)//喵喵喵，最大生成树中不能保证所有点都连通…… 
			if(!vis[i]) dep[i]=1,dfs(i);
		init();
		int x,y;
		scanf("%d",&q);
		while(q--)
		{
			scanf("%d%d",&x,&y);
			printf("%d\n",get_ans(x,y));
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
