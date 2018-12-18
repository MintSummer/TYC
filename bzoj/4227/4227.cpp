#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	typedef pair<ll,int> pa;
	
	const int N=100010;
	const int M=200010;
	const int MX=500010;
	const ll inf=0x3f3f3f3f;
	
	int n,m,node,cnt,Head[N],deg[MX],dep[MX],id[MX],size[MX],fa[MX][21];
	ll dis[N];
	vector<int> G[MX],Tree[MX];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void write(ll x)
	{
		if(x<0) putchar('-'),x=-x;
		if(!x) putchar('0');
		else
		{
			int len=0;
			static int bask[50];
			while(x) bask[++len]=x%10,x/=10;
			for(;len;len--) putchar('0'+bask[len]);
		}
		putchar('\n');
	}

	struct edge
	{
		int to,next,w;
	}E[M<<1];

	inline void add(int u,int v,int w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}

	void Dijkstra(int s)
	{
		static int vis[MX];
		static priority_queue<pa,vector<pa>,greater<pa> > q;
		for(int i=1;i<=n;i++) dis[i]=inf;
		dis[s]=0;
		q.push(pa(0,s));
		while(!q.empty())
		{
			int u=q.top().second;q.pop();
			if(vis[u]) continue;
			vis[u]=1;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(dis[v]>dis[u]+E[i].w)
				{
					dis[v]=dis[u]+E[i].w;
					if(!vis[v]) q.push(pa(dis[v],v));
				}
			}
		}
	}

	void rebuild()
	{
		node=n;
		for(int u=1;u<=n;u++)
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(dis[v]==dis[u]+E[i].w)
				{
					id[i]=++node;
					G[u].push_back(node),deg[node]++;
					G[node].push_back(v),deg[v]++;
				}
			}
	}

	inline int LCA(int u,int v)
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

	void topsort()
	{
		static int q[MX];
		int h=1,t=0;
		q[++t]=++node;
		for(int i=1;i<node;i++)
			if(!deg[i]) 
			{
				G[node].push_back(i);
				deg[i]++;
				Tree[node].push_back(i);
			}
		while(h<=t)
		{
			int u=q[h++];
			for(int i=1;fa[u][i-1]&&i<=19;i++) 
				fa[u][i]=fa[fa[u][i-1]][i-1];
			if(fa[u][0]&&fa[u][0]!=node)
				Tree[fa[u][0]].push_back(u);
			for(int i=0;i<G[u].size();i++)
			{
				int v=G[u][i];
				if(!fa[v][0]) fa[v][0]=u;
				else fa[v][0]=LCA(fa[v][0],u);
				dep[v]=dep[fa[v][0]]+1;
				deg[v]--;
				if(!deg[v]) q[++t]=v;
			}
		}
	}

	void dfs(int u)
	{
		size[u]=(u<=n&&dis[u]<inf);
		for(int i=0;i<Tree[u].size();i++)
		{
			dfs(Tree[u][i]);
			size[u]+=size[Tree[u][i]];
		}
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read(),w=read();
			add(u,v,w),add(v,u,w);
		}
		int s=read();
		Dijkstra(s);
		rebuild();
		topsort();
		dfs(node);
		static int ans[MX];
		for(int i=1;i<=cnt;i+=2)
		{
			int a=id[i]?size[id[i]]:0;
			int b=id[i+1]?size[id[i+1]]:0;
			ans[E[i].to]+=a+b;
			ans[E[i+1].to]+=a+b;
		}
		for(int i=1;i<=n;i++) write(ans[i]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
