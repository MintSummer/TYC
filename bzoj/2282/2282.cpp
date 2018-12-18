#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=300010;
	int n,Limit,cnt,Head[N],dis[N],fa[N],vis[N];

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

	inline void add(int u,int v,int w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}

	void dfs(int u,int f,const int tag=1)
	{
		if(tag) fa[u]=f;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f||vis[v]) continue;
			dis[v]=dis[u]+E[i].w;
			dfs(v,u,tag);
		}
	}

	void work()
	{
		n=read(),Limit=read();
		for(int i=1;i<n;i++)
		{
			int u=read(),v=read(),w=read();
			add(u,v,w),add(v,u,w);
		}

		int start=0,end=0;
		dfs(1,0);
		for(int i=1;i<=n;i++)
			if(dis[i]>dis[start]) start=i;
		dis[start]=0;
		dfs(start,0);
		for(int i=1;i<=n;i++)
			if(dis[i]>dis[end]) end=i;

		int ans=0x3f3f3f3f;
		for(int l=end,r=end;r;r=fa[r])
		{
			while(fa[l]&&dis[r]-dis[fa[l]]<=Limit) l=fa[l];
			ans=min(ans,max(dis[end]-dis[r],dis[l]));
		}

		for(int i=end;i;i=fa[i]) vis[i]=1;
		for(int i=end;i;i=fa[i])
			dis[i]=0,dfs(i,0,0);
		for(int i=1;i<=n;i++) ans=max(ans,dis[i]);
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
