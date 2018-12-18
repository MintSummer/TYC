#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cctype>
#include<queue>
#include<vector>
using namespace std;

namespace TYC
{
	typedef long long ll;
	typedef pair<ll,int> pa;
	const int N=1e5+10,M=1e6+10;
	const ll INF=(1LL<<61);
	int n,m,tot,cnt,view,Head[N],vis[N],fa[N],q[N<<3];
	ll distance,dis[N],height[N];

	inline ll read()
	{
		ll x=0;int f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	struct edge
	{
		int to,next;
		ll w;
	}E[M<<1];

	inline void add(int u,int v,ll w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}

	struct Edge
	{
		int u,v;
		ll w;
		bool operator < (const Edge &a) const
		{
			return height[v]!=height[a.v]?height[v]>height[a.v]:w<a.w;
		}
	}e[M<<1];

	void bfs()
	{
		int h=1,t=0;
		q[++t]=1;
		vis[1]=1,view++;
		while(h<=t)
		{
			int u=q[h++];
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				e[++tot]=(Edge){u,v,E[i].w};
				if(!vis[v]) 
				{
					vis[v]=1,view++;
					q[++t]=v;
				}
			}
		}
	}
	
	int find(int x)
	{
		return x==fa[x]?x:fa[x]=find(fa[x]);
	}

	void kruskal()
	{
		sort(e+1,e+1+tot);
		for(int i=1;i<=n;i++) fa[i]=i;
		for(int i=1,num=0;i<=tot&&num!=view-1;i++)
		{
			int fu=find(e[i].u),fv=find(e[i].v);
			if(fu==fv) continue;
			num++;
			fa[fv]=fu;
			distance+=e[i].w;
		}
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++) height[i]=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			ll w=read();
			if(height[u]>=height[v]) add(u,v,w);
			if(height[v]>=height[u]) add(v,u,w);
		}
		bfs();
		kruskal();
		printf("%d %lld\n",view,distance);
	}
}

int  main()
{
	TYC::work();
	return 0;
}
