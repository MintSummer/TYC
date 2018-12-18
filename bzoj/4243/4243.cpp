#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=1e5+10;
	const int M=2e5+10;

	int n,m,Head[N],fa[N],size[N];

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
	}E[M];

	inline void add(int u,int v)
	{
		static int cnt=0;
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
	}

	int find(int x)
	{
		return x==fa[x]?x:fa[x]=find(fa[x]);
	}

	void bfs()
	{
		static queue<int> q;
		static int vis[N];
		for(int i=1;i<=n;i++)
			if(size[find(i)]>1) q.push(i),vis[i]=1;
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				int fu=find(u),fv=find(v);
				if(fu!=fv)
				{
					fa[fv]=fu;
					size[fu]+=size[fv];
					if(!vis[v]) q.push(v);
				}
			}
		}
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++) fa[i]=i,size[i]=1;
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			add(u,v);
		}
		for(int u=1;u<=n;u++)
		{
			if(!Head[u]) continue;
			int now=E[Head[u]].to,f=find(now);
			for(int i=E[Head[u]].next;i;i=E[i].next)
			{
				int v=E[i].to,fv=find(v);
				if(f!=fv) fa[fv]=f,size[f]+=size[fv];
			}
		}
		bfs();
		ll ans=0;
		static int vis[N];
		for(int i=1;i<=n;i++)
		{
			int f=find(i);
			if(!vis[f])
			{
				vis[f]=1;
				if(size[f]==1)
					for(int j=Head[i];j;j=E[j].next) ans++;
				else 
					ans+=(ll)size[f]*(size[f]-1);
			}
		}
		printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
