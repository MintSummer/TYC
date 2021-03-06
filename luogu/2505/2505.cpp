#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	typedef pair<int,int> pa;
	const int p=1000000007,inf=0x3f3f3f3f;
	const int N=1510,M=5010;
	int n,m,cnt,Head[N],dis[N],tag[M],deg[N],list[N],num1[N],num2[N];
	ll ans[M];

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
	}E[M];

	inline void add(int u,int v,int w)
	{
		E[++cnt]=(edge){u,v,Head[u],w};
		Head[u]=cnt;
	}

	void Dijkstra(int s)
	{
		memset(dis,inf,sizeof(dis));
		memset(tag,0,sizeof(tag));
		priority_queue<pa,vector<pa>,greater<pa> > q;
		dis[s]=0;
		q.push(pa(dis[s],s));
		while(!q.empty())
		{
			int u=q.top().second;
			q.pop();
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
		for(int i=1;i<=cnt;i++)
			if(dis[E[i].from]+E[i].w==dis[E[i].to])
				deg[E[i].to]++,tag[i]=1;
	}

	void topsort()
	{
		int h=1,t=0;
		memset(num1,0,sizeof(num1));
		memset(num2,0,sizeof(num2));
		for(int i=1;i<=n;i++)
			if(!deg[i]) 
				num1[i]=1,list[++t]=i;
		while(h<=t)
		{
			int u=list[h++];
			for(int i=Head[u];i;i=E[i].next)
				if(tag[i])
				{
					int v=E[i].to;
					num1[v]+=num1[u];
					deg[v]--;
					if(!deg[v]) list[++t]=v;
				}
		}
		for(int i=t;i;i--)
		{
			int u=list[i];
			num2[u]=1;
			for(int i=Head[u];i;i=E[i].next)
				if(tag[i])
				{
					int v=E[i].to;
					num2[u]+=num2[v];
				}
		}
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read(),w=read();
			add(u,v,w);
		}
		for(int i=1;i<=n;i++)
		{
			Dijkstra(i);
			topsort();
			for(int i=1;i<=m;i++)
				if(tag[i])
					ans[i]=(ans[i]+1LL*num1[E[i].from]*num2[E[i].to]%p)%p;
		}
		for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
	}
}


int main()
{
	TYC::work();
	return 0;
}
