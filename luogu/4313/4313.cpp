#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;

namespace TYC
{
    const int MAXN=100*100*4+10,inf=0x3f3f3f3f;
    const int dx[5]={0,1,0,-1,0},dy[5]={0,0,-1,0,1};
    int N,M,S,T,sum=0,cnt=1,dep[MAXN],cur[MAXN],Head[MAXN];

    int read()
    {
		int x=0;char ch=getchar();
		while(!isdigit(ch)) x=(ch=='-'?-x:x),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return x;
    }

    struct edge
    {
		int to,next,w;
    }E[MAXN*8];

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

    inline int p(int x,int y)
    {
		return (x-1)*M+y;
    }

    bool bfs()
    {
		memset(dep,-1,sizeof(dep));
		memcpy(cur,Head,sizeof(cur));
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
		for(int &i=cur[u];i;i=E[i].next)
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

    int Dinic()
    {
		int ans=0;
		while(bfs()) ans+=dfs(S,inf);
		return ans;
    }

    void work()
    {
    	N=read(),M=read();
		S=0,T=3*N*M+1;
		int x,now=N*M;
		for(int i=1;i<=N;i++) 
			for(int j=1;j<=M;j++) 
			{
				x=read();
				insert(S,p(i,j),x);
				sum+=x;
			}
		for(int i=1;i<=N;i++) 
			for(int j=1;j<=M;j++) 
			{
				x=read();
				insert(p(i,j),T,x);
				sum+=x;
			}
		for(int i=1;i<=N;i++) 
			for(int j=1;j<=M;j++)
			{
				x=read();
				sum+=x;
				now++;
				insert(S,now,x);
				insert(now,p(i,j),inf);
				for(int k=1;k<=4;k++)
				{
					int x=i+dx[k],y=j+dy[k];
					if(x<1||x>N||y<1||y>M) continue;
					insert(now,p(x,y),inf);
				}
			}
		for(int i=1;i<=N;i++) 
			for(int j=1;j<=M;j++) 
			{
				x=read();
				sum+=x;
				now++;
				insert(now,T,x);
				insert(p(i,j),now,inf);
				for(int k=1;k<=4;k++)
				{
					int x=i+dx[k],y=j+dy[k];
					if(x<1||x>N||y<1||y>M) continue;
					insert(p(x,y),now,inf);
				}
			}
		cout<<sum-Dinic();
    }
}

int main()
{
    TYC::work();
    return 0;
}
