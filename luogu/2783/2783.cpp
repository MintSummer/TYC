#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

namespace TYC
{
	const int N=20000,M=100000;
	int n,m,cnt,tot,top,dfstim,Head[N],st[N],dfn[N],low[N],in[N],size[N],belong[N],fa[N][18],dep[N];
	vector<int> G[N];

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
	}E[M<<1];

	inline void add(int u,int v)
	{
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
	}

	void Tarjan(int u,int f)
	{
		dfn[u]=low[u]=++dfstim;
		st[++top]=u;
		in[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			if(!dfn[v])
				Tarjan(v,u),low[u]=min(low[u],low[v]);
			else
				if(in[v]) low[u]=min(low[u],dfn[v]);
		}
		if(low[u]==dfn[u])
		{
			tot++;
			int x;
			do
			{
				x=st[top--];
				size[tot]=x;
				belong[x]=tot;
				in[x]=0;
			}
			while(x!=u);
		}
	}

	void rebuild()
	{
		for(int u=1;u<=n;u++)
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(belong[u]!=belong[v])
					G[belong[u]].push_back(belong[v]);
			}
	}

	void dfs(int u,int f)
	{
		fa[u][0]=f;
		dep[u]=dep[f]+1;
		for(int i=1;fa[u][i-1]&&i<=14;i++)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		for(int i=0;i<G[u].size();i++)
		{
			int v=G[u][i];
			if(v==f) continue;
			dfs(v,u);
		}
	}

	inline int LCA(int u,int v)
	{
		if(dep[u]<dep[v]) swap(u,v);
		for(int d=dep[u]-dep[v],t=0;d;d>>=1,t++)
			if(d&1) u=fa[u][t];
		if(u==v) return u;
		for(int i=14;i>=0;i--)
			if(fa[u][i]!=fa[v][i])
				u=fa[u][i],v=fa[v][i];
		return fa[u][0];
	}

	inline void write(int x)
	{
		if(!x) putchar('0');
		else
		{
			int len=0;
			static int bask[50];
			while(x) bask[++len]=(x&1),x>>=1;
			for(int i=len;i;i--) putchar('0'+bask[i]);
		}
		puts("");
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			add(u,v),add(v,u);
		}
		for(int i=1;i<=n;i++)
			if(!dfn[i]) Tarjan(i,0);
		rebuild();
		dfs(1,0);
		int ques=read();
		while(ques--)
		{
			int u=read(),v=read();
			u=belong[u],v=belong[v];
			int lca=LCA(u,v),ans=dep[u]+dep[v]-dep[lca]-dep[fa[lca][0]];
			write(ans);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
