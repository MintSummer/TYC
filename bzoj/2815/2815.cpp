#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=65534+10;
	int n,cnt,s,Head[N],deg[N],tmp[N],fa[N][18],dep[N],size[N];

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
	}E[7000010];

	void add(int u,int v)
	{
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
	}

	inline int LCA(int u,int v)
	{
		if(dep[u]<dep[v]) swap(u,v);
		for(int t=0,d=dep[u]-dep[v];d;d>>=1,t++)
			if(d&1) u=fa[u][t];
		if(u==v) return u;
		for(int i=16;i>=0;i--)
			if(fa[u][i]!=fa[v][i])
				u=fa[u][i],v=fa[v][i];
		return fa[u][0];
	}

	inline void search()
	{
		queue<int> q;
		for(int i=1;i<=n;i++)
			if(!deg[i]) q.push(i),fa[i][0]=s,dep[i]=1;
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=1;i<=16;i++)
			   fa[u][i]=fa[fa[u][i-1]][i-1];	
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(!fa[v][0]) 
					fa[v][0]=u,dep[v]=dep[u]+1;
				else 
				{
					fa[v][0]=LCA(fa[v][0],u);
					dep[v]=dep[fa[v][0]]+1;
				}
				deg[v]--;
				if(!deg[v]) q.push(v);
			}
		}
	}

	void dfs(int u)
	{
		size[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			dfs(v);
			size[u]+=size[v];
		}
	}

	void work()
	{
		n=read();
		s=n+1;
		for(int i=1;i<=n;i++)
		{
			int x=read();
			while(x!=0) add(x,i),deg[i]++,x=read();
		}
		search();
		cnt=0;
		memset(Head,0,sizeof(Head));
		for(int i=1;i<=n;i++) add(fa[i][0],i);
		dfs(s);
		for(int i=1;i<=n;i++)
			printf("%d\n",size[i]-1);
	}
}

int main()
{
	TYC::work();
	return 0;
}
