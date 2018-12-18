#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=20010,M=100010;
	int n,m,fa[N],enemy[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	struct edge
	{
		int u,v,w;
		bool operator < (const edge &t) const
		{
			return w>t.w;
		}
	}e[M];

	int find(int a)
	{
		return fa[a]==a?a:fa[a]=find(fa[a]);
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++) fa[i]=i;
		for(int i=1;i<=m;i++)
			e[i]=(edge){read(),read(),read()};
		sort(e+1,e+1+m);
		int ans=0;
		for(int i=1;i<=m;i++)
		{
			int u=e[i].u,v=e[i].v;
			int fu=find(u),fv=find(v);
			if(fu==fv) {ans=e[i].w;break;}
			if(!enemy[u]) enemy[u]=v;
			else fa[fv]=find(enemy[u]);
			if(!enemy[v]) enemy[v]=u;
			else fa[fu]=find(enemy[v]);
		}
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
