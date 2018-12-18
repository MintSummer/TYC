#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	const int N=60;

	int n,scc,Head[N],end[N][N],G[N][N][2],belong[N],size[N],dfn[N],deg[N];
	bool vis[N][N];
	vector<int> to[N];

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
	}E[N*N];

	inline void add(int u,int v)
	{
		static int cnt=0;
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
	}

	bool check(int x,int y)
	{
		memset(vis,false,sizeof(vis));
		queue<pa> q;
		q.push(pa(1,1));
		while(!q.empty())
		{
			int a=q.front().first,b=q.front().second;
			q.pop();
			if(!end[x][a]&&end[y][b]) return false;
			int na=G[x][a][0],nb=G[y][b][0];
			if(~na&&~nb&&!vis[na][nb]) 
				vis[na][nb]=1,q.push(pa(na,nb));
			na=G[x][a][1],nb=G[y][b][1];
			if(~na&&~nb&&!vis[na][nb]) 
				vis[na][nb]=1,q.push(pa(na,nb));
		}
		return true;
	}

	void Tarjan(int u)
	{
		static int tim,top,in[N],low[N],sta[N];
		dfn[u]=low[u]=++tim;
		sta[++top]=u;
		in[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(!dfn[v]) 
				Tarjan(v),low[u]=min(low[u],low[v]);
			else 
				if(in[v]) low[u]=min(low[u],dfn[v]);
		}
		if(low[u]==dfn[u])
		{
			int x;
			scc++;
			do
			{
				x=sta[top--];
				belong[x]=scc;
				in[x]=0;
				size[scc]++;
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
				{
					to[belong[v]].push_back(belong[u]);
					deg[belong[u]]++;
				}
			}
	}

	void topsort()
	{
		static int f[N];
		queue<int> q;
		for(int i=1;i<=scc;i++)
			if(!deg[i]) q.push(i),f[i]=size[i];
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=0,sz=to[u].size();i<sz;i++)
			{
				int v=to[u][i];
				f[v]=max(f[u]+size[v],f[v]);
				deg[v]--;
				if(!deg[v]) q.push(v);
			}
		}
		int ans=0;
		for(int i=1;i<=scc;i++) ans=max(f[i],ans);
		printf("%d\n",ans);
	}

	void work()
	{
		n=read();
		for(int i=1;i<=n;i++)
		{
			int b=read(),a=read();
			while(a--) end[i][read()+1]=1;
			for(int j=1;j<=b;j++)
				G[i][j][0]=read()+1,G[i][j][1]=read()+1;
		}	
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(i!=j&&check(i,j)) add(i,j);
		for(int i=1;i<=n;i++)
			if(!dfn[i]) Tarjan(i);
		rebuild();
		topsort();
	}
}

int main()
{
	TYC::work();
	return 0;
}
