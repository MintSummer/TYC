#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1010,M=100010,inf=0x3f3f3f3f;
	int n,m,cnt,tot,top,dfstim,in[N],st[N],Head[N],col[N],dfn[N],low[N],belong[N],diameter[N],vis[N],dis[N],fa[N],mark[N];
	
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
	
	bool bfs_color()
	{
		memset(col,-1,sizeof(col));
		memset(vis,0,sizeof(vis));
		queue<int> q;
		col[1]=1;
		q.push(1);
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(~col[v]&&col[v]==col[u]) return false;
				else col[v]=col[u]^1;
				if(!vis[v]) vis[v]=1,q.push(v);
			}
		}
		return true;
	}
	
	void bfs_diameter(int s)
	{
		queue<int> q;
		memset(dis,inf,sizeof(dis));
		memset(vis,0,sizeof(vis));
		dis[s]=0;
		q.push(s);
		vis[s]=1;
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(belong[v]!=belong[u]||vis[v]) continue;
				vis[v]=1;
				dis[v]=dis[u]+1;
				q.push(v);
			}
		}
	}
	
	int find(int x)
	{
		return fa[x]==x?x:fa[x]=find(fa[x]);
	}
	
	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++) fa[i]=i;
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			add(u,v),add(v,u);
			int fu=find(u),fv=find(v);
			if(fu!=fv) fa[fu]=fv;
		}
		if(!bfs_color()) {puts("-1");return;}
		for(int i=1;i<=n;i++) find(i);
		for(int i=1;i<=n;i++)
		{
			bfs_diameter(i);
			for(int j=1;j<=n;j++)
				if(dis[j]!=inf)
					diameter[fa[i]]=max(diameter[fa[i]],dis[j]);
		}
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			int f=fa[i];
			if(!mark[f])
				ans+=diameter[f],mark[f]=1;
		}
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
