#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int inf=0x3f3f3f3f,N=10010;
	const int dx[5]={0,0,0,1,-1},dy[5]={0,1,-1,0,0};
	int n,m,tot,s,t,cnt=1,Head[N],G[110][110],num[110][110],dep[N],cur[N];

	struct edge
	{
		int to,next,w;
	}E[800010];

	inline void insert(int u,int v,int w)
	{
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v],0};
		Head[v]=cnt;
	}

	bool bfs()
	{
		memset(dep,-1,sizeof(dep));
		memcpy(cur,Head,sizeof(cur));
		queue<int> q;
		q.push(s);
		dep[s]=0;
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w&&dep[v]==-1)
				{
					dep[v]=dep[u]+1;
					q.push(v);
				}
			}
		}
		return dep[t]!=-1;
	}

	int dfs(int u,int mn)
	{
		if(u==t) return mn;
		int v,w,used=0;
		for(int &i=cur[u];i;i=E[i].next)
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
		scanf("%d%d",&n,&m);
		s=n*m+1,t=s+1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				scanf("%d",&G[i][j]);
				num[i][j]=++tot;
				if(G[i][j]==1) insert(s,num[i][j],inf);
				else if(G[i][j]==2) insert(num[i][j],t,inf);
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(G[i][j]==1||G[i][j]==0)
					for(int k=1;k<=4;k++)
					{
						int x=i+dx[k],y=j+dy[k];
						if(x<1||x>n||y<1||y>m||G[x][y]==1) continue;
						insert(num[i][j],num[x][y],1);
					}
		printf("%d\n",Dinic());
	}
}

int main()
{
	TYC::work();
	return 0;
}
