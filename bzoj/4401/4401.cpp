#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1000010;
	int n,cnt,Head[N],size[N],num[N];

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
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v]};
		Head[v]=cnt;
	}

	void dfs(int u,int f)
	{
		size[u]=1;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			dfs(v,u);
			size[u]+=size[v];
		}
	}

	void work()
	{
		n=read();
		for(int i=1;i<n;i++)
		{
			int u=read(),v=read();
			add(u,v);
		}
		dfs(1,0);
		int ans=0;
		for(int i=1;i<=n;i++) num[size[i]]++;
		for(int block=1;block<=n;block++)
			if(n%block==0)
			{
				int tot=0;
				for(int j=block;j<=n;j+=block) tot+=num[j];
				ans+=(tot==n/block);
			}
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
