#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cctype>
#include<ctime>
#include<vector>
#include<map>
#include<queue>
#include<set>
using namespace std;

namespace TYC
{
	const int N=5010;
	const double eps=1e-4;
	int n,m,cnt,vis[N],Head[N];
	double dis[N];

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
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}

	bool dfs(int u,double mid)
	{
		vis[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(dis[v]>dis[u]+E[i].w+mid)
			{
				dis[v]=dis[u]+E[i].w+mid;
				if(vis[v]) return true;
				if(dfs(v,mid)) return true;
			}
		}
		vis[u]=0;
		return false;
	}

	inline bool check(double mid)
	{
		memset(vis,0,sizeof(vis));
		memset(dis,0,sizeof(dis));
		for(int i=1;i<=n+2;i++)
			if(dfs(i,mid)) return true;
		return false;
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read(),a=read(),b=read(),c=read(),d=read();
			if(c)  add(v,u,a-d);
			add(u,v,b+d);
		}
		double l=0,r=1e9,mid,ans;
		while(l<=r)
		{
			mid=(l+r)/2;
			if(check(mid)) ans=mid,l=mid+eps;
			else r=mid-eps;
		}
		printf("%.2f",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
