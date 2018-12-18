#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=210,inf=0x3f3f3f3f;
	const int G[10][10]={{0,1,1,0,0},{0,0,1,0,1},{0,0,0,1,1},{1,1,0,0,0},{1,0,0,1,0}};
	int n,m,s,t,a[N],b[N],Head[N],dep[N];

	struct edge
	{
		int to,next,w;
	}E[N*N];

	inline void add(int u,int v,int w)
	{
		static int cnt=1;
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v],0};
		Head[v]=cnt;
	}
	
	inline int ID(char ch)
	{
		switch(ch)
		{
			case 'J': return 0;
			case 'H': return 1;
			case 'W': return 2;
			case 'Y': return 3;
			case 'E': return 4;
		}
		return 0;
	}

	bool bfs()
	{
		queue<int> q;
		memset(dep,-1,sizeof(dep));
		dep[s]=0;
		q.push(s);
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w&&dep[v]==-1)
					dep[v]=dep[u]+1,q.push(v);
			}
		}
		return dep[t]!=-1;
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
		if(!used) dep[u]=-1;
		return used;
	}

	int Dinic()
	{
		int ans=0;
		while(bfs()) ans+=dfs(s,inf);
		return ans;
	}

	void work()
	{
		ios::sync_with_stdio(false);
		cin>>n>>m;
		s=n+n+1,t=s+1;
		string name;
		int x,magic=0;
		for(int i=1;i<=n;i++)
		{
			cin>>name;
			a[i]=ID(name[0]);
			magic+=(name[0]=='Y');
		}
		for(int i=1;i<=n;i++)
		{
			cin>>name;
			b[i]=ID(name[0]);
		}
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			if(a[i]==0) x+=magic;
			add(s,i,x);
		}
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			if(b[i]==0) x+=magic;
			add(i+n,t,x);
		}
		for(int i=1;i<=n;i++) 	
			for(int j=1;j<=n;j++)
				if(G[a[i]][b[j]]) add(i,j+n,1);
		printf("%d\n",min(m,Dinic()));
	}
}

int main()
{
	TYC::work();
	return 0;
}
