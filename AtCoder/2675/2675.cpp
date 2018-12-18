#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
	const int N=2e5+10;
	int n,root1,root2,cnt,Head[N],son[N],vis[N*4],ans[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	struct edge
	{
		int to,next,id;
	}E[N*4];
	
	inline void add(int u,int v,int id)
	{
		E[++cnt]=(edge){v,Head[u],id};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v],id};
		Head[v]=cnt;
	}
	
	void dfs(int u,int f)
	{
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			son[u]++;
			dfs(v,u);
		}
	}
	
	void dfs(int u)
	{
		for(int &i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to,id=E[i].id;
			if(vis[id]) continue;
			vis[id]=1;
			if(u+n==v) ans[u]=1;
			else if(v+n==u) ans[v]=-1;
			dfs(v);
		}
	}
	
	void work()
	{
		n=read();
		int Num=0;
  		for(int i=1;i<=n;i++)
		{
			int f=read();
			if(f==-1) root1=i;
			else add(f,i,++Num);
		}
		for(int i=1;i<=n;i++)
		{
			int f=read();
			if(f==-1) root2=i+n;
			else add(f+n,i+n,++Num);
		}
		dfs(root1,0);
		dfs(root2,0);
		for(int i=1;i<=n;i++)
			if((son[i]&1)!=(son[i+n]&1)) {puts("IMPOSSIBLE");return;}
			else if(!(son[i]&1)) add(i,i+n,++Num);
		puts("POSSIBLE");
		add(0,root1,++Num),add(0,root2,++Num);
		dfs(0);
		for(int i=1;i<=n;i++)
			printf("%d ",ans[i]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
