#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<queue>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=110,K=1010,inf=0x3f3f3f3f;
	int n,m,trade;
	ll b[N][K],s[N][K],G[N][N],M[N][N],dis[N];
	bool vis[N],flag;

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void init()
	{
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				M[i][j]=0;
				for(int k=1;k<=trade;k++)
					if(b[i][k]!=-1&&s[j][k]!=-1)
						M[i][j]=max(M[i][j],s[j][k]-b[i][k]);
			}
	}

	void dfs(int u,ll mid)
	{
		if(vis[u]||flag) {flag=true;return;}
		vis[u]=1;
		for(int v=1;v<=n;v++)
		{
			if(u==v) continue;
			ll w=M[u][v]-mid*G[u][v];
			if(dis[u]+w>=dis[v])
			{
				dis[v]=dis[u]+w;
				dfs(v,mid);
			}
		}
		vis[u]=0;
	}

	bool check(ll mid)
	{
		memset(dis,0,sizeof(dis));
		memset(vis,false,sizeof(vis));
		flag=false;
		for(int i=1;i<=n;i++)
		{
			dfs(i,mid);
			if(flag) return true;
		}
		return false;
	}

	void work()
	{
		n=read(),m=read(),trade=read();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=trade;j++)
				b[i][j]=read(),s[i][j]=read();
		memset(G,inf,sizeof(G));
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			ll w=read();
			G[u][v]=min(G[u][v],w);
		}
		init();
		ll l=0,r=1e9,mid,ans;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(check(mid)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
