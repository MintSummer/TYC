#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	const int N=2000010;

	int n,m,ans,Head[N],son[N],val[N],vis[N];
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
		static int cnt=0;
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
	}

	bool cmp(const int &x,const int &y)
	{
		return son[x]+val[x]<son[y]+val[y];
	}

	void dfs(int u)
	{
		int sz=G[u].size();
		for(int i=0;i<sz;i++) 
			son[u]++,dfs(G[u][i]);
		sort(G[u].begin(),G[u].end(),cmp);
		for(int i=0;i<sz;i++)
		{
			int v=G[u][i];
			if(val[u]+son[u]+val[v]+son[v]-1<=m)
			{
				ans++;
				val[u]+=val[v];
				son[u]+=son[v]-1;
			}
			else break;
		}
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++) val[i]=read();
		for(int i=1;i<=n;i++)
		{
			int t=read();
			while(t--) G[i].push_back(read()+1);
		}
		dfs(1);
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
