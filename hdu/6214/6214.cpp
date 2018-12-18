#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=210;
	const int M=1010;
	const int Base=1000;

	int n,m,cnt,s,t,Head[N],dep[N];

	inline int read()
	{
		int x=0,f=0; char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void init()
	{
		cnt=1;
		memset(Head,0,sizeof(Head));
	}

	struct edge
	{
		int to,next,w;
	}E[M<<1];

	inline void add(int u,int v,int w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v],0};
		Head[v]=cnt;
	}

	bool bfs()
	{
		memset(dep,0,sizeof(dep));
		queue<int> q;
		q.push(s);
		dep[s]=1;
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w&&dep[v]==0)
					dep[v]=dep[u]+1,q.push(v);
			}
		}
		return dep[t];
	}

	int dfs(int u,int mn)
	{
		if(u==t||!mn) return mn;
		int v,w,used=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			v=E[i].to;
			if(E[i].w&&dep[v]==dep[u]+1)
			{
				w=dfs(v,min(mn-used,E[i].w));
				used+=w;
				E[i].w-=w,E[i^1].w+=w;
				if(used==mn) return used;
			}
		}
		if(!used) dep[u]=0;
		return used;
	}

	int Dinic()
	{
		int ans=0;
		while(bfs()) 
			ans+=dfs(s,0x3f3f3f3f);
		return ans;
	}

	void work()
	{
		int T=read();
		while(T--)
		{
			n=read(),m=read();
			s=read(),t=read();
			init();
			for(int i=1;i<=m;i++)
			{
				int u=read(),v=read(),w=read();
				add(u,v,w*Base+1);
			}
			printf("%d\n",Dinic()%Base);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
