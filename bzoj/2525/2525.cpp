#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=300010;
	const int inf=0x3f3f3f3f;

	int n,m,tot,mid,Head[N],danger[N],dp[N][2];

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

	void dfs(int u,int f)
	{
		int t1=danger[u]?0:-inf,t2=inf;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			dfs(v,u);
			t1=max(t1,dp[v][0]+1);
			t2=min(t2,dp[v][1]+1);
		}
		if(t1+t2<=mid) t1=-inf;
		else if(t1==mid) tot++,t1=-inf,t2=0;
		dp[u][0]=t1,dp[u][1]=t2;
	}

	bool check()
	{
		tot=0;
		dfs(1,0);
		return tot+(dp[1][0]+dp[1][1]>mid)<=m;
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++) danger[i]=read();
		for(int i=1;i<n;i++)
		{
			int u=read(),v=read();
			add(u,v),add(v,u);
		}
		int l=0,r=n,ans;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(check()) ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
