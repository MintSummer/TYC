#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

namespace XXJ
{
	ll bin[65],a[65];
	inline void insert(ll x)
	{
		for(int i=60;i>=0;i--)
			if(x&bin[i])
			{
				if(!a[i]) {a[i]=x;return;}
				else x^=a[i];
			}
	}

	inline ll query(ll x)
	{
		ll ans=x;
		for(int i=60;i>=0;i--)
			if((ans^a[i])>ans) 
				ans^=a[i];
		return ans;
	}
}

namespace TYC
{
	const int N=50010,M=100010;
	int n,m,cnt,Head[N],vis[N];
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
		int to,next;
		ll w;
	}E[M<<1];

	inline void add(int u,int v,ll w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}

	void dfs(int u,ll w)
	{
		dis[u]=w,vis[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(!vis[v]) dfs(v,w^E[i].w);
			else XXJ::insert(dis[u]^dis[v]^E[i].w);
		}
	}

	void work()
	{
		n=read();m=read();
		XXJ::bin[0]=1;
		for(int i=1;i<=60;i++) XXJ::bin[i]=XXJ::bin[i-1]<<1;
		int u,v;ll w;
		for(int i=1;i<=m;i++)
		{
			u=read(),v=read();
			scanf("%lld",&w);
			add(u,v,w),add(v,u,w);
		}
		dfs(1,0LL);
		printf("%lld\n",XXJ::query(dis[n]));
	}
}

int main()
{
	TYC::work();
	return 0;
}
