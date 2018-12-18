#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=500010;

	int n,m,Head[N],mark[N];
	ll inmx[N],outmx[N],insum[N],outsum[N];
	multiset<ll> s[N];

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
	}E[N<<1];

	inline void add(int u,int v,int w)
	{
		static int cnt=0;
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}

	void dfs1(int u,int f)
	{
		inmx[u]=insum[u]=-1;
		if(mark[u]) inmx[u]=insum[u]=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			dfs1(v,u);
			if(~insum[v]) 
			{
				if(insum[u]==-1) insum[u]=0;
				insum[u]+=insum[v]+E[i].w*2;
				inmx[u]=max(inmx[u],inmx[v]+E[i].w);
			}
		}
	}

	void dfs2(int u,int f)
	{
		ll tot=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			if(~insum[v]||mark[v]) tot+=insum[v]+E[i].w*2;
			if(~inmx[v]) s[u].insert(inmx[v]+E[i].w);
		}
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			if(~outmx[u]) outmx[v]=max(outmx[v],outmx[u]+E[i].w);
			if(~inmx[v]) s[u].erase(s[u].find(inmx[v]+E[i].w));
			if(!s[u].empty()) outmx[v]=max(outmx[v],(*s[u].rbegin())+E[i].w);
			if(~inmx[v]) s[u].insert(inmx[v]+E[i].w);
			outsum[v]+=outsum[u]+E[i].w*2+tot;
			if(~insum[v]||mark[v]) outsum[v]-=insum[v]+E[i].w*2;
			dfs2(v,u);
		}
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<n;i++)
		{
			int u=read(),v=read(),w=read();
			add(u,v,w),add(v,u,w);
		}
		for(int i=1;i<=m;i++) mark[read()]=1;
		dfs1(1,0);
		dfs2(1,0);
		for(int i=1;i<=n;i++)
			printf("%lld\n",max(insum[i],0LL)+max(outsum[i],0LL)-max(0LL,max(inmx[i],outmx[i])));
	}
}

int main()
{
	TYC::work();
	return 0;
}
