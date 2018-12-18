#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;

namespace TYC
{
	#define ll long long
	#define pa pair<ll,int>
	#define inf 9000000000000000000LL
	using namespace __gnu_pbds;
	typedef __gnu_pbds::priority_queue<pa,greater<pa>,pairing_heap_tag > pq;
	const int N=1000005,M=10000005;
	pq::point_iterator id[N];
	int n,m,cnt,Head[N];
	ll dis[N];

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
	}E[M];

	void add(int u,int v,int w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}

	void Dijkstra()
	{
		pq q;
		for(int i=1;i<=n;i++) dis[i]=inf;
		dis[1]=0;
		id[1]=q.push(make_pair(0,1));
		while(!q.empty())
		{
			int u=q.top().second;
			q.pop();
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(dis[v]>dis[u]+E[i].w)
				{
					dis[v]=dis[u]+E[i].w;
					if(id[v]!=0) q.modify(id[v],make_pair(dis[v],v));
					else id[v]=q.push(make_pair(dis[v],v));
				}
			}
		}
	}

	void work()
	{
		n=read(),m=read();
		int T=read(),rxa=read(),rxc=read(),rya=read(),ryc=read(),rp=read(),x,y,a,b;
		for(int i=1;i<=T;i++)
		{
			x=((ll)x*rxa+rxc)%rp;
			y=((ll)y*rya+ryc)%rp;
			a=min(x%n+1,y%n+1);
			b=max(y%n+1,y%n+1);
			add(a,b,100000000LL-100LL*a);
		}
		for(int i=1;i<=m-T;i++)
		{
			x=read(),y=read(),a=read();
			add(x,y,a);
		}
		Dijkstra();
		printf("%lld\n",dis[n]);
	}
}


int main()
{
	TYC::work();
	return 0;
}
