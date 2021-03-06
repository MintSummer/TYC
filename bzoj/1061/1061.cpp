#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
	const int N=10010,inf=0x3f3f3f3f;
	int n,m,s,t,cnt=1,Head[N],pre[N],vis[N];
	long long dis[N];

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
	}E[800010];

	inline void insert(int u,int v,int w,int c)
	{
		E[++cnt]=(edge){v,Head[u],w,c};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v],0,-c};
		Head[v]=cnt;
	}

	bool spfa()
	{
		for(int i=s;i<=t;i++) dis[i]=1e14;
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
					if(!vis[v]) vis[v]=1,q.push(v);
				}
			}
		}
		return dis[t]!=1e14;
	}

	long long mcmf()
	{
		long long ans=0;
		while(spfa())
		{
			int mn=inf+10;
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
		s=0,t=n+2;
		insert(s,1,inf,0);
		insert(n+1,t,inf,0);
		for(int i=1;i<=n;i++)
			insert(i,i+1,inf-read(),0);	
		for(int i=1;i<=m;i++)
		{
			int l=read(),r=read(),c=read();
			insert(l,r+1,inf,c);
		}
		printf("%lld\n",mcmf());
	}
}

int main()
{
	TYC::work();
	return 0;
}
