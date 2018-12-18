#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
	const int N=100010;
	int n,m,cnt,Head[N],fa[N],dep[N],vis[N],pre[N],tree_edge[N<<1],tag[N],ans[N<<1];
	
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
	
	void dfs(int u,int f)
	{
		vis[u]=1;
		fa[u]=f;
		dep[u]=dep[f]+1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]) continue;
			tree_edge[i]=1;
			pre[v]=i;
			dfs(v,u);
		}
	}

	void dfs(int u)
	{
		vis[u]=1;
		for(int i=Head[u];i;i=E[i].next)
			if(tree_edge[i])
			{
				int v=E[i].to;
				if(vis[v]) continue;
				dfs(v);
				tag[u]+=tag[v];
			}
	}
	
	void get_ans()
	{
		int tot=0;
		for(int i=1;i<=cnt;i+=2)
		{
			if(tree_edge[i]||tree_edge[i+1]) continue;
			int u=E[i+1].to,v=E[i].to;
			if(dep[u]<dep[v]) swap(u,v);
			int flag=0,t;
			for(t=u;fa[t]!=v;t=fa[t])
				if(tag[t]!=1) {flag=1;break;}
			if(!flag&&tag[t]==1)
			{
				ans[++tot]=(i-1)/2+1;
				while(u!=v)
				{
					ans[++tot]=(pre[u]-1)/2+1;
					u=fa[u];
				}
			}
		}
		printf("%d\n",tot);
		sort(ans+1,ans+1+tot);
		for(int i=1;i<=tot;i++) printf("%d ",ans[i]);
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
			if(!vis[i]) dfs(i,0);
		for(int i=1;i<=cnt;i+=2)
		{
			if(tree_edge[i]||tree_edge[i+1]) continue;
			int u=E[i+1].to,v=E[i].to;
			if(dep[u]<dep[v]) swap(u,v);
			tag[u]++,tag[v]--;
		}
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++)
			if(!vis[i]) dfs(i);
		get_ans();
	}
}

int main()
{
	TYC::work();
	return 0;
}
