#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=810*2,inf=0x3f3f3f3f;
	int n,m,s,t,cnt=1,Head[N],vis[N],dis[N],pre[N],a[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	struct edge
	{
		int to,next,w,c;
	}E[2000010];

	void insert(int u,int v,int w,int c)
	{
		E[++cnt]=(edge){v,Head[u],w,c};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v],0,-c};
		Head[v]=cnt;
	}

	bool spfa()
	{
		memset(dis,inf,sizeof(dis));
		memset(pre,0,sizeof(pre));
		queue<int> q;
		q.push(s);
		dis[s]=0,vis[s]=1;
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			vis[u]=0;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w&&dis[v]>dis[u]+E[i].c)
				{
					dis[v]=dis[u]+E[i].c;
					pre[v]=i;
					if(!vis[v]) q.push(v),vis[v]=1;
				}
			}
		}
		return dis[t]!=inf;
	}

	ll mcmf()
	{
		ll ans=0;
		while(spfa())
		{
			int mn=inf;
			for(int i=pre[t];i;i=pre[E[i^1].to])
				mn=min(mn,E[i].w);
			for(int i=pre[t];i;i=pre[E[i^1].to])
				E[i].w-=mn,E[i^1].w+=mn;
			ans+=mn*dis[t];
		}
		return ans;
	}

	void work()
	{
		n=read(),m=read();
		s=n*2+1,t=s+1;
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read(),w=read();
			if(u>v) swap(u,v); 
			if(w<a[v]) insert(u,v+n,1,w);
		}
		for(int i=1;i<=n;i++)
		{
			insert(s,i,1,0);
			insert(i+n,t,1,0);
			insert(s,i+n,1,a[i]);
		}
		printf("%lld\n",mcmf());
	}
}

int main()
{
	TYC::work();
	return 0;
}
