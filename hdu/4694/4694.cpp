#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int MAXN=50010;
	int n,m,cnt,dfs_clock,id[MAXN],Head[MAXN],dfn[MAXN];
	vector<int> g[MAXN],pre[MAXN],son[MAXN];
	
	inline int read()
	{
		int x=0,f=0;
		char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	void dfs(int u)
	{
		dfn[u]=++dfs_clock();
		id[dfs_clock]=u;
		for(int i=0;i<g[u].size();i++)
		{
			int v=g[u][v];
			if(!dfn[v]) continue;
			dfs(v);
			son[u].push_back(v);
		}
	}
	
	void tarjan()
	{
		for(int i=dfs_clock;i;i--)
		{
			int v=id[i];
			for(int j=0;j<pre[v].size();j++)
			{
				int u=pre[v][j];
				if(!dfn[u]) continue;
				if(dfn[u]<dfn[v])
				{
					if(dfn[u]<dfn[sdom[v]]) sdom[v]=u;
				}
				else
				{
					
				}
			}
		}
	}

	void work()
	{
		while(~scanf("%d%d",&n,&m))
		{
			for(int i=1;i<=m;i++)
			{
				int u=read(),v=read();
				g[u].push_back(v);
				pre[v].push_back(u);
			}
		}
		sdom[0]=0x3f3f3f3f;
		dfs(n);
		Tarjan();
	}
}

int main()
{
	TYC::word();
	return 0;
} 
