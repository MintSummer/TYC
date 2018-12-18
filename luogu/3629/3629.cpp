#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

namespace TYC
{
	const int N=100010,inf=0x3f3f3f3f;
	int n,k,cnt=1,ans,len,root,Head[N],nxt1[N],nxt2[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	struct edge
	{
		int to,next,w;
	}E[N<<1];

	void insert(int u,int v)
	{
		E[++cnt]=(edge){v,Head[u],1};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v],1};
		Head[v]=cnt;
	}

	int dfs(int u,int fa)
	{
		int mx1=0,mx2=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa) continue;
			int dis=dfs(v,u)+E[i].w;
			if(dis>mx1) 
			{
				mx2=mx1;
				mx1=dis;
				nxt2[u]=nxt1[u];
				nxt1[u]=i;
			}
			else if(dis>mx2) 
				mx2=dis,nxt2[u]=i;
		}
		if(mx1+mx2>len) 
			len=mx1+mx2,root=u;
		return mx1;
	}

	void work()
	{
		n=read(),k=read();
		for(int i=1;i<n;i++)
		{
			int u=read(),v=read();
			insert(u,v);
		}
		ans=(n-1)*2,len=0;
		dfs(1,0);
		ans=ans-len+1;
		if(k==2) 
		{
			len=0;
			for(int i=nxt1[root];i;i=nxt1[E[i].to])
				E[i].w=E[i^1].w=-1;
			for(int i=nxt2[root];i;i=nxt1[E[i].to])//注意:次长路也是从下一个的最长路转移而来的
				E[i].w=E[i^1].w=-1;
			dfs(1,0);
			ans=ans-len+1;
		}
		printf("%d\n",ans);
	}
}


int main()
{
	TYC::work();
	return 0;
}
