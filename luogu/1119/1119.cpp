#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	const int N=210,inf=0x3f3f3f3f;
	int n,m,cnt,ques,tim[N],dis[N][N],ans[50010],vis[N];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	inline void write(int x)
	{
		if(x<0) putchar('-'),x=-x;
		if(!x) putchar('0');
		else
		{
			int len=0;
			static int bask[15];
			while(x) bask[++len]=x%10,x/=10;
			for(;len;len--) putchar('0'+bask[len]);
		}
		putchar('\n');
	}
	
	struct edge
	{
		int to,w;
	};
	vector<edge> G[N];
	
	void Dijkstra(int s,int *dis)
	{
		dis[s]=0;
		dis[0]=inf;
		memset(vis,0,sizeof(int[n+1]));
		while(1)
		{
			int u=0;
			for(int i=1;i<=s;i++)
				if(!vis[i]&&dis[i]<dis[u]) u=i;
			vis[u]=1;
			if(!u) return;
			for(int i=0;i<G[u].size();i++)
			{
				int v=G[u][i].to,w=G[u][i].w;
				if(v<=s&&dis[v]>dis[u]+w)
					dis[v]=dis[u]+w;
			}
		}
	}
	
	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++) tim[i]=read();
		for(int i=1;i<=m;i++)
		{
			int u=read()+1,v=read()+1,w=read();
			G[u].push_back((edge){v,w});
			G[v].push_back((edge){u,w});
		}
		memset(dis,inf,sizeof(dis));
		ques=read();
		int now=1;
		for(int i=1;i<=ques;i++)
		{
			int start=read()+1,end=read()+1,Time=read();
			while(now<=n&&tim[now]<=Time)
			{
				Dijkstra(now,dis[now]);
				for(int u=1;u<=now;u++) dis[u][now]=dis[now][u];
				for(int u=1;u<=now;u++)
					for(int v=1;v<=now;v++)
						dis[v][u]=min(dis[u][v],dis[u][now]+dis[now][v]);
				now++;
			}
			if(dis[start][end]!=inf) write(dis[start][end]);
			else write(-1);
		}
	}
}

int main()
{
	freopen("a.in","r",stdin);
	TYC::work();
	return 0;
}
