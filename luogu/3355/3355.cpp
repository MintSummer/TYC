#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
    const int inf=0x3f3f3f3f;
    const int dx[9]={0,-2,-1,-2,-1,1,2,2,1};
    const int dy[9]={0,-1,-2,1,2,-2,-1,1,2};
    int N,M,S,T,G[210][210],ans,dep[210*210],cnt=1,Head[210*210];

    int pos(int x,int y)
    {
		return (x-1)*N+y;
    }

    struct edge
    {
		int to,next,w;
    }E[210*210*8];

    void add(int u,int v,int w)
    {
		cnt++;
		E[cnt].to=v;
		E[cnt].next=Head[u];
		E[cnt].w=w;
		Head[u]=cnt;
    }

    void insert(int u,int v,int w)
    {
		add(u,v,w),add(v,u,0);
    }

    bool bfs()
    {
		memset(dep,-1,sizeof(dep));
		queue<int> q;
		q.push(S);
		dep[S]=0;
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w>0&&dep[v]==-1)
					dep[v]=dep[u]+1,q.push(v);
			}
		}
		return dep[T]!=-1;
    }

    int dfs(int u,int mn)
    {
		if(u==T) return mn;
		int v,w,used=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			v=E[i].to;
			if(E[i].w>0&&dep[v]==dep[u]+1)
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

    void Dinic()
    {
		while(bfs()) ans-=dfs(S,inf);
    }

    void work()
    {
		cin>>N>>M;
		int x,y;
		S=0,T=N*N+1;
		ans=N*N-M;
		for(int i=1;i<=M;i++)
		{
			cin>>x>>y;
			G[x][y]=1;
		}
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++)
			{
				if(G[i][j]) continue;
				if((i+j)%2)
				{
					insert(S,pos(i,j),1);
					for(int k=1;k<=8;k++)
					{
						int x=i+dx[k],y=j+dy[k];
						if(x<1||x>N||y<1||y>N||G[x][y]) continue;
						insert(pos(i,j),pos(x,y),inf);
					}
				}
				else insert(pos(i,j),T,1);
			}
		Dinic();
		cout<<ans;
    }
}

int main()
{
    TYC::work();
    return 0;
}
