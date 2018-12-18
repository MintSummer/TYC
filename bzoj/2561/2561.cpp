#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
    const int inf=0x3f3f3f3f,MAXN=40010;
    int N,M,S,T,L,ans,cnt=1,Head[MAXN],dep[MAXN];

    struct Edge
    {
		int u,v,w;
		bool operator < (const Edge &a) const
		{
			return w<a.w;
		}
    }e[200010];

    struct edge
    {
		int to,next,w;
    }E[MAXN*10];

    void add(int u,int v)
    {
		cnt++;
		E[cnt].to=v;
		E[cnt].next=Head[u];
		E[cnt].w=1;
		Head[u]=cnt;
    }

    void insert(int u,int v)
    {
		add(u,v),add(v,u);
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
				 {
					 dep[v]=dep[u]+1;
					 q.push(v);
				 }
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
		while(bfs()) ans+=dfs(S,inf);
    }

    void work()
    {
		ios::sync_with_stdio(false);
		cin>>N>>M;
		for(int i=1;i<=M;i++)
			cin>>e[i].u>>e[i].v>>e[i].w;
		sort(e+1,e+M+1);
		cin>>S>>T>>L;
		for(int i=1;i<=M;i++)
			if(e[i].w<L) insert(e[i].u,e[i].v);
			else break;
		Dinic();
		cnt=1;
		memset(Head,0,sizeof(Head));
		for(int i=M;i>=1;i--)
			if(e[i].w>L) insert(e[i].u,e[i].v);
			else break;
		Dinic();
		cout<<ans;
    }
}

int main()
{
    TYC::work();
    return 0;
}
