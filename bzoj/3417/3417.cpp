#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	typedef pair<int,int> pa;
	const int N=5010;
	const int M=1000010;
	const ll inf=(1LL<<61);

	int n,m,Head[N],hq[N];
	ll dis[N][2];

	inline ll read()
	{
		ll x=0;int f=0;char ch=getchar();
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

	struct query
	{
		int to,id,next;
		ll dis;
	}q[M];

	inline void add_q(int s,int t,ll d,int id)
	{
		static int cnt=0;
		q[++cnt]=(query){t,id,hq[s],d};
		hq[s]=cnt;
	}

	void Dijkstra(int s)
	{
		static int h,t,q[M];
		static bool vis[N];
		h=1,t=0;
		memset(vis,false,sizeof(vis));
		for(int i=1;i<=n;i++) 
			dis[i][0]=dis[i][1]=inf;
		for(int i=Head[s];i;i=E[i].next)
			dis[E[i].to][1]=1,q[++t]=E[i].to;
		while(h<=t)
		{
			int u=q[h++];
			vis[u]=0;
			if(dis[u][0])
			{
				for(int i=Head[u];i;i=E[i].next)
				{
					int v=E[i].to;
					if(dis[v][1]>dis[u][0]+1)
					{
						dis[v][1]=dis[u][0]+1;
						if(!vis[v]) vis[v]=1,q[++t]=v;
					}
				}
			}
			if(dis[u][1])
			{
				for(int i=Head[u];i;i=E[i].next)
				{
					int v=E[i].to;
					if(dis[v][0]>dis[u][1]+1)
					{
						dis[v][0]=dis[u][1]+1;
						if(!vis[v]) vis[v]=1,q[++t]=v;
					}
				}
			}
		}
	}

	void work()
	{
		n=read(),m=read();
		int ques=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			add(u,v),add(v,u);
		}
		for(int i=1;i<=ques;i++)
		{
			int s=read(),t=read();
			ll d=read();
			add_q(s,t,d,i);
		}
		static int ans[M];
		for(int i=1;i<=n;i++)
			if(hq[i])
			{
				Dijkstra(i);
				for(int j=hq[i];j;j=q[j].next)
				{
					int v=q[j].to,t=q[j].dis&1;
					if(dis[v][t]<=q[j].dis) ans[q[j].id]=1;
				}
			}
		for(int i=1;i<=ques;i++)
			puts(ans[i]?"TAK":"NIE");
	}
}

int main()
{
	TYC::work();
	return 0;
}
