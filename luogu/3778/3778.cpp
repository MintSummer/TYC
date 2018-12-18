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
	const int N=110,K=1010,inf=1e9;
	int n,m,trade,tim[N];
	ll b[N][K],s[N][K],G[N][N],M[N][N],dis[N][N],Dis[N];
	bool vis[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void init()
	{
		for(int i=1;i<=n;i++) G[i][i]=0;
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(i!=j&&G[i][j]!=inf)
				{
					M[i][j]=0;
					for(int k=1;k<=trade;k++)
						if(b[i][k]!=-1&&s[j][k]!=-1)
							M[i][j]=max(M[i][j],s[j][k]-b[i][k]);
				}
	}

	queue<int> q;
	bool spfa()
	{
		while(!q.empty()) q.pop();
		memset(vis,false,sizeof(bool[n+5]));
		memset(tim,0,sizeof(int[n+5]));
		memset(Dis,0,sizeof(int[n+5]));
		for(int i=1;i<=n;i++)
			q.push(i),vis[i]=1;
		while(!q.empty())
		{
			int u=q.front();q.pop();
			vis[u]=0;
			for(int v=1;v<=n;v++)
				if(Dis[v]<=Dis[u]+dis[u][v])
				{
					Dis[v]=Dis[u]+dis[u][v];
					if(!vis[v])
					{
						tim[v]++,vis[v]=1;
						if(tim[v]>n) return true;
						q.push(v);
					}
				}
		}
		return false;
	}

	bool check(ll mid)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=M[i][j]-mid*G[i][j];
		return spfa();
	}

	void work()
	{
		n=read(),m=read(),trade=read();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=trade;j++)
				b[i][j]=read(),s[i][j]=read();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				M[i][j]=-inf,G[i][j]=inf;
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			ll w=read();
			G[u][v]=min(G[u][v],w);
		}
		init();
		ll l=0,r=1e9,mid;
		while(l<r)
		{
			mid=(l+r+1)>>1;
			if(check(mid)) l=mid;
			else r=mid-1;
		}
		printf("%lld\n",l);
	}
}

int main()
{
	TYC::work();
	return 0;
}
