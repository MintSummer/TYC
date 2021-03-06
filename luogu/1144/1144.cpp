#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int p=100003;
	const int N=1000010,M=2000010;
	int n,m,cnt,Head[N],num[N],dis[N],vis[N];
	#define Mod(x) x>p?x-p:x

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
	}E[M<<1];

	inline void add(int u,int v)
	{
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v]};
		Head[v]=cnt;
	}
	
	void bfs()
	{
		memset(dis,0x3f3f3f3f,sizeof(dis));
		queue<int> q;
		q.push(1);
		dis[1]=0,vis[1]=1,num[1]=1;
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(dis[v]==dis[u]+1)
				   	num[v]=Mod(num[v]+num[u]);
				if(dis[v]>dis[u]+1) 
					dis[v]=dis[u]+1,num[v]=num[u];
				if(!vis[v]) 
					vis[v]=1,q.push(v);
			}
		}
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			add(u,v);
		}
		bfs();
		for(int i=1;i<=n;i++) printf("%d\n",num[i]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
