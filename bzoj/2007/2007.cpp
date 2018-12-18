#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=250010,inf=0x3f3f3f3f;
	typedef long long ll;
	typedef pair<ll,int> pa;
	int n,tot,s,t,cnt,Head[N],num[510][510];
	ll dis[N];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	struct edge
	{
		int from,to,next,w;
	}E[N<<3];

	inline void insert(int u,int v,int w)
	{
		E[++cnt]=(edge){u,v,Head[u],w};
		Head[u]=cnt;
	}

	ll Dijkstra()
	{
		for(int i=1;i<=t;i++) dis[i]=1e14;
		priority_queue<pa,vector<pa>,greater<pa> > q;
		q.push(pa(0,s));
		dis[s]=0;
		while(!q.empty())
		{
			int u=q.top().second,d=q.top().first;
			q.pop();
			if(d<dis[u]) continue;
			if(u==t) break;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(dis[v]>dis[u]+E[i].w)
				{
					dis[v]=dis[u]+E[i].w;
					q.push(pa(dis[v],v));
				}
			}
		}
		return dis[t];
	}

	void work()
	{
		n=read();
		s=n*n+1,t=s+1;
		for(int i=0;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				int x=read();
				if(i==0) insert(i*n+j,t,x);
				else if(i==n) insert(s,(i-1)*n+j,x);
				else insert(i*n+j,(i-1)*n+j,x);
			}
		for(int i=1;i<=n;i++)
			for(int j=0;j<=n;j++)
			{
				int x=read();
				if(j==0) insert(s,(i-1)*n+1,x);
				else if(j==n) insert(i*n,t,x);
				else insert((i-1)*n+j,(i-1)*n+j+1,x);
			}
		for(int i=0;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				int x=read();
				if(i==0) insert(t,i*n+j,x);
				else if(i==n) insert((i-1)*n+j,s,x);
				else insert((i-1)*n+j,i*n+j,x);
			}
		for(int i=1;i<=n;i++)
			for(int j=0;j<=n;j++)
			{
				int x=read();
				if(j==0) insert((i-1)*n+1,s,x);
				else if(j==n) insert(t,i*n,x);
				else insert((i-1)*n+j+1,(i-1)*n+j,x);
			}
		printf("%lld\n",Dijkstra());
	}
}

int main()
{
	TYC::work();
	return 0;
}
