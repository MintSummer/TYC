#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=1010;
	int n,s,t,cnt=1,Head[N],dep[N],cur[N];
	ll ans;

	inline ll read()
	{
		ll x=0;int f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=1LL*x*10+ch-'0',ch=getchar();
		return x;
	}

	struct edge
	{
		int to,next;
		ll w;
	}E[N*N*4];

	void insert(int u,int v,ll w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v],0};
		Head[v]=cnt;
	}

	bool bfs()
	{
		memset(dep,-1,sizeof(dep));
		memcpy(cur,Head,sizeof(cur));
		queue<int> q;
		q.push(s);
		dep[s]=0;
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w&&dep[v]==-1)
					dep[v]=dep[u]+1,q.push(v);
			}
		}
		return dep[t]!=-1;
	}

	ll dfs(int u,ll mn)
	{
		if(u==t) return mn;
		int v,w;
		ll used=0;
		for(int &i=cur[u];i;i=E[i].next)
		{
			v=E[i].to;
			if(E[i].w&&dep[v]==dep[u]+1)
			{
				w=dfs(v,min(E[i].w,mn-used));
				used+=w;
				E[i].w-=w,E[i^1].w+=w;
				if(used==mn) return used;
			}
		}
		if(!used) dep[u]=-1;
		return used;
	}

	void Dinic()
	{
		while(bfs()) ans-=dfs(s,1e14);
	}

	void work()
	{
		scanf("%d",&n);
		s=n+1,t=s+1;
		ll x;
		for(int i=1;i<=n;i++) 
			x=read(),insert(i,t,x);
		for(int i=1;i<=n;i++)
		{
			ll sum=0;
			for(int j=1;j<=n;j++)
			{
				x=read();
				sum+=x;
				insert(i,j,x*2);
			}
			ans+=sum;
			insert(s,i,sum);
		}
		Dinic();
		printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
