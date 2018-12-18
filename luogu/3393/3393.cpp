#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	typedef pair<ll,int> pa;
	const int N=100010,M=200010;
	const ll inf=(1LL<<61);
	int n,m,k,s,Head[N],danger[N];
	
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
		edge(){}
		edge(int v,int nxt): to(v),next(nxt) {w=0;}
	}E[M<<1];
	
	inline void add(int u,int v)
	{
		static int cnt=0;
		E[++cnt]=edge(v,Head[u]);
		Head[u]=cnt;
	}
	
	void bfs()
	{
		static queue<int> q;
		for(int i=1;i<=n;i++)
			if(danger[i]==2) q.push(i);
		static int dis[N];
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(!danger[v]&&dis[u]<s) 
					danger[v]=1,dis[v]=dis[u]+1,q.push(v);
			}
		}
	}
	
	void Dijkstra()
	{
		static ll dis[N];
		static int vis[N];
		static priority_queue<pa,vector<pa>,greater<pa> > q;
		for(int i=1;i<=n;i++) dis[i]=inf;
		dis[1]=0;
		q.push(pa(dis[1],1));
		while(!q.empty())
		{
			int u=q.top().second;q.pop();
			if(vis[u]) continue;
			vis[u]=1;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(dis[u]+E[i].w<dis[v])
				{
					dis[v]=dis[u]+E[i].w;
					if(!vis[v]) q.push(pa(dis[v],v));
				}
			}
		}
		printf("%lld\n",dis[n]);
	}
	
	void work()
	{
		n=read(),m=read(),k=read(),s=read();
		int val1=read(),val2=read();
		for(int i=1;i<=k;i++) danger[read()]=2;
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			if(danger[u]==2&&danger[v]==2) continue;
			add(u,v),add(v,u);
		}
		bfs();
		for(int u=1;u<=n;u++)
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(v!=1&&v!=n) switch(danger[v])
				{
					case 0: E[i].w=val1;break;
					case 1: E[i].w=val2;break;
					case 2: E[i].w=inf;break;
				}
			}
		Dijkstra();
	}
}

int main()
{
	TYC::work();
	return 0;
}
