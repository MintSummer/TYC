#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=100010;
	int n,m,cnt,scc,dfs_clock,top,in[N],st[N],Head[N],dfn[N],low[N],belong[N],size[N],deg[N],tag[N];

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
	}E[300000*2+10];

	inline void add(int u,int v)
	{
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
	}

	void Tarjan(int u)
	{
		dfn[u]=low[u]=++dfs_clock;
		st[++top]=u;
		in[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(!dfn[v]) Tarjan(v),low[u]=min(low[u],low[v]);
			else if(in[v]) low[u]=min(low[u],dfn[v]);
		}
		if(dfn[u]==low[u])
		{
			scc++;
			int x;
			do
			{
				x=st[top--];
				belong[x]=scc;
				size[scc]++;
				in[x]=0;
			}
			while(x!=u);
		}
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			add(u,v);
		}
		for(int i=1;i<=n;i++)
			if(!dfn[i]) Tarjan(i);
		for(int u=1;u<=n;u++)
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(belong[u]!=belong[v])
					deg[belong[v]]++;
			}
		int ans=0,flag=0;
		for(int i=1;i<=scc;i++)
			if(!deg[i]) 
			{
				if(!flag&&size[i]==1)
				{
					int u;
					for(u=1;u<=n;u++) 
						if(belong[u]==i) break;
					flag=1;
					for(int j=Head[u];j;j=E[j].next)
						if(deg[belong[E[j].to]]==1) {flag=0;break;}
				}
				ans++;
			}
		ans-=flag;
		printf("%f",1.0-(double)ans/n);
	}
}

int main()
{
	TYC::work();
	return 0;
}
