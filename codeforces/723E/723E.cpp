#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
	const int N=210,M=N*N;
	int n,m,cnt,Head[N],deg[N],vis[M<<1];
	
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
	
	void dfs(int u)
	{
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[i]) continue;
			if(u&&v) printf("%d %d\n",u,v);
			vis[i]=vis[i^1]=1;
			dfs(v);
		}
	}
	
	void work()
	{
		int T=read();
		while(T--)
		{
			n=read(),m=read();
			cnt=1;
			memset(deg,0,sizeof(int[n+1]));
			memset(Head,0,sizeof(int[n+2]));
			memset(vis,0,sizeof(vis));
			for(int i=1;i<=m;i++)
			{
				int u=read(),v=read();
				add(u,v),add(v,u);
				deg[u]++,deg[v]++;
			}
			int ans=0;
			for(int i=1;i<=n;i++)
				if(!(deg[i]&1)) ans++;
				else add(i,0),add(0,i);
			printf("%d\n",ans);
			for(int i=1;i<=n;i++) dfs(i);
			
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
