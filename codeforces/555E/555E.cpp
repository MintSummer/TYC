#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
	const int N=2e5+10;
	int n,m,ques,cnt=1,dfstim,top,tot,NumTree;
	int Head[N],dfn[N],low[N],st[N],in[N],belong[N],vis[N],dep[N],fa[N][20],up[N],down[N],mark[N],tree[N];
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
	}E[N<<1];
	
	inline void add(int u,int v)
	{
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
	}
	
	void Tarjan(int u,int pre)
	{
		dfn[u]=low[u]=++dfstim;
		st[++top]=u;
		in[u]=1;
		tree[u]=NumTree;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if((i^1)==pre) continue;
			if(!dfn[v])
				Tarjan(v,i),low[u]=min(low[u],low[v]);
			else
				if(in[v]) low[u]=min(low[u],dfn[v]);
		}
		if(dfn[u]==low[u])
		{
			int x;
			tot++;
			do
			{
				x=st[top--];
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
		dep[u]=dep[f]+1;
		fa[u][0]=f;
		for(int i=1;fa[u][i-1]&&i<=18;i++)
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
		for(int i=18;i>=0;i--)
			if(fa[u][i]!=fa[v][i])
				u=fa[u][i],v=fa[v][i];
		return fa[u][0];
	}
	
	void dfs(int u)
	{
		mark[u]=1;
		for(int i=0;i<G[u].size();i++)
		{
			int v=G[u][i];
			if(mark[v]) continue;
			dfs(v);
			up[u]+=up[v];
			down[u]+=down[v];
		}
	}
	
	void work()
	{
		n=read(),m=read(),ques=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			add(u,v),add(v,u);
		}
		for(int i=1;i<=n;i++)
			if(!dfn[i]) NumTree++,Tarjan(i,0);
		rebuild();
		for(int i=1;i<=tot;i++)
			if(!dep[i]) dfs(i,0);
		while(ques--)
		{
			int u=read(),v=read();
			if(tree[u]!=tree[v]) {puts("No");return;}
			u=belong[u],v=belong[v];
   			int lca=LCA(u,v);
   			up[u]++,up[lca]--;
   			down[v]++,down[lca]--;
		}
		for(int i=1;i<=tot;i++)
			if(!mark[i]) dfs(i);
		for(int i=1;i<=tot;i++)
			if(up[i]&&down[i]) {puts("No");return;}
		puts("Yes");
	}
}

int main()
{
	TYC::work();
	return 0;
}
