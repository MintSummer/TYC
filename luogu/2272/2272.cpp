#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=1e5+10;
	int n,m,p,cnt,dfs_clock,top,scc,tot,ans1,ans2;
	int in[N],Head[N],dfn[N],low[N],st[N],belong[N],size[N],f[N],deg[N],q[N],head[N],plan[N],vis[N];
	vector<int> node[N];

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
	}E[1000010*2],e[1000010*2];

	void add(int u,int v)
	{
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
	}

	void ins(int u,int v)
	{
		e[++tot]=(edge){v,head[u]};
		head[u]=tot;
	}

	void Tarjan(int u)
	{
		dfn[u]=low[u]=++dfs_clock;
		in[u]=1;
		st[++top]=u;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(!dfn[v])
				Tarjan(v),low[u]=min(low[u],low[v]);
			else if(in[v]) low[u]=min(low[u],dfn[v]);
		}
		if(dfn[u]==low[u])
		{
			int x;
			scc++;
			do
			{
				x=st[top--];
				belong[x]=scc;
				in[x]=0;
				size[scc]++;
				node[scc].push_back(x);
			}
			while(x!=u);
		}
	}

	void search()
	{
		int h=1,t=0;
		for(int i=1;i<=scc;i++)
			if(!deg[i]) 
				q[++t]=i,f[i]=size[i],plan[i]=1;
		while(h<=t)
		{
			int u=q[h++];
			for(int i=head[u];i;i=e[i].next)
			{
				int v=e[i].to;
				deg[v]--;
				if(f[v]<f[u]+size[v])
				{
					f[v]=f[u]+size[v];
					plan[v]=plan[u];
				}
				else if(f[v]==f[u]+size[v])
					plan[v]=(ll)(plan[u]+plan[v])%p;
				if(!deg[v]) q[++t]=v;
			}
		}
	}

	void work()
	{
		n=read(),m=read(),p=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			add(u,v);
		}
		for(int i=1;i<=n;i++)
			if(!dfn[i]) Tarjan(i);
		for(int now=1;now<=scc;now++)
			for(int k=0;k<size[now];k++)
			{
				int u=node[now][k];
				for(int i=Head[u];i;i=E[i].next)
				{
					int v=E[i].to;
					if(now!=belong[v]&&vis[belong[v]]!=now)
					{
						vis[belong[v]]=now;
						deg[belong[v]]++;
						ins(now,belong[v]);
					}
				}
			}
		search();
		for(int i=1;i<=n;i++) ans1=max(ans1,f[i]);
		for(int i=1;i<=n;i++)
			if(ans1==f[i]) ans2=(ll)(ans2+plan[i])%p;
		printf("%d\n%d",ans1,ans2);
	}
}

int main()
{
	TYC::work();
	return 0;
}
