#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

namespace TYC
{
	const int N=2010;
	int n,m,fa[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	struct Edge
	{
		int u,v,w;
		bool operator < (const Edge &t) const
		{
			return w<t.w;
		}
	}e[N*N];

	int find(int x)
	{
		return x==fa[x]?x:fa[x]=find(fa[x]);
	}

	long long kruskal()
	{
		long long ans=0;
		sort(e+1,e+1+m);
		for(int i=0;i<=n;i++) fa[i]=i;
		for(int i=1;i<=m;i++)
		{
			int u=find(e[i].u),v=find(e[i].v);
			if(u!=v)
			{
				fa[u]=v;
				ans+=e[i].w;
			}
		}
		return ans;
	}

	void work()
	{
		n=read();
		for(int i=1;i<=n;i++)
			for(int j=i;j<=n;j++)
				e[++m]=(Edge){i-1,j,read()};
		printf("%lld\n",kruskal());
	}
}

int main()
{
	TYC::work();
	return 0;
}
