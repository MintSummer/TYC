#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<set>
#include<vector>
#include<cctype>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	const int N=1510,M=N*N,inf=0x3f3f3f3f;
	int n,m,s1,t1,s2,t2,cnt,Head[N],dis[4][N],deg[N],f[N];
	bool vis[N];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	struct edge
	{
		int to,next,w;
	}E[M];
	
	inline void add(int u,int v,int w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}
	
	struct Edge
	{
		int to,w;
	};
	vector<Edge> G[N];
	
	priority_queue<pa,vector<pa>,greater<pa> > q;
	void Dijkstra(int s,int *dis)
	{
		while(!q.empty()) q.pop();
		memset(vis,false,sizeof(bool[n+5]));
		q.push(pa(0,s));
		dis[s]=0;
		while(!q.empty())
		{
			int u=q.top().second;q.pop();
			if(vis[u]) continue;
			vis[u]=true;
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
	
	inline void rebuild()
	{
		for(int u=1;u<=n;u++)
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(dis[0][u]+E[i].w+dis[1][v]==dis[0][t1] &&
					(dis[2][u]+E[i].w+dis[3][v]==dis[2][t2] || dis[2][v]+E[i].w+dis[3][u]==dis[2][t2]))
						G[u].push_back((Edge){v,E[i].w}),deg[v]++;
			}
	}
	
	void topsort()
	{
		static int q[N];
		int h=1,t=0;
		for(int i=1;i<=n;i++)
			if(!deg[i]) q[++t]=i;
		while(h<=t)
		{
			int u=q[h++];
			for(int i=0;i<G[u].size();i++)
			{
				int v=G[u][i].to;
				f[v]=max(f[v],f[u]+G[u][i].w);
				deg[v]--;
				if(!deg[v]) q[++t]=v;
			}
		}
	}
	
	void work()
	{
		n=read(),m=read();
		s1=read(),t1=read(),s2=read(),t2=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read(),w=read();
			add(u,v,w),add(v,u,w);
		}
		memset(dis,inf,sizeof(dis));
		Dijkstra(s1,dis[0]);
		Dijkstra(t1,dis[1]);
		Dijkstra(s2,dis[2]);
		Dijkstra(t2,dis[3]);
		rebuild();
		topsort();
		int ans=0;
		for(int i=1;i<=n;i++) ans=max(ans,f[i]);
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
