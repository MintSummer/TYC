#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
    const int inf=0x3f3f3f3f,MAXN=1010;
    typedef long long ll;
    int N,M,K,T,cnt;
    int W[5050],Head[MAXN],dep[MAXN],cur[MAXN],pre[MAXN],dis[MAXN],vis[MAXN];

    struct edge
    {
	int from,to,w,c,next;
   }E[5050*4];

    void add(int u,int v,int w,int c)
    {
	E[cnt]=(edge){u,v,w,c,Head[u]};
	Head[u]=cnt++;
    }

    bool bfs()
    {
	memset(dep,-1,sizeof(dep));
	memcpy(cur,Head,sizeof(cur));
	queue<int> q;
	q.push(1);
	dep[1]=0;
	while(!q.empty())
	{
	    int u=q.front();
	    q.pop();
	    for(int i=Head[u];~i;i=E[i].next)
	    {
		int v=E[i].to;
		if(E[i].w>0&&dep[v]==-1) 
		    dep[v]=dep[u]+1,q.push(v);
	    }
	}
	return dep[N]!=-1;
    }

    int dfs(int u,int mn)
    {
	if(u==N) return mn;
	int v,w,used=0;
	for(int &i=cur[u];~i;i=E[i].next)
	{
	    v=E[i].to;
	    if(dep[v]==dep[u]+1&&E[i].w>0)
	    {
		w=dfs(v,min(E[i].w,mn-used));
		E[i].w-=w,E[i^1].w+=w;
		used+=w;
		if(used==mn) return used;
	    }
	}
	if(!used) dep[u]=-1;
	return used;
    } 

    int Dinic()
    {
	int ans=0;
	while(bfs()) 
	    ans+=dfs(1,inf);
	return ans;
    }

    bool spfa()
    {
	memset(dis,inf,sizeof(dis));
	memset(pre,-1,sizeof(pre));
	queue<int> q;
	q.push(1);
	dis[1]=0,vis[1]=1;
	while(!q.empty())
	{
	    int u=q.front();
	    q.pop();
	    vis[u]=0;
	    for(int i=Head[u];~i;i=E[i].next)
	    {
		int v=E[i].to;
		if(E[i].w>0&&dis[v]>dis[u]+E[i].c)
		{
		    dis[v]=dis[u]+E[i].c;
		    pre[v]=i;
		    if(!vis[v]) vis[v]=1,q.push(v);
		}
	    }
	}
	return dis[T]!=inf;
    }

    int mcmf()
    {
	int ans=0;
	while(spfa())
	{
	    int mn=inf;
	    for(int i=pre[T];~i;i=pre[E[i].from])
		mn=min(mn,E[i].w);
	    for(int i=pre[T];~i;i=pre[E[i].from])
		E[i].w-=mn,E[i^1].w+=mn;
	    ans+=mn*dis[T];
	}
	return ans;
    }

    void work()
    {
	ios::sync_with_stdio(false);
	memset(Head,-1,sizeof(Head));
	cin>>N>>M>>K;
	T=N+1;
	int u,v,c;
	for(int i=0;i<M;i++)
	{
	    cin>>u>>v>>c>>W[i];
	    add(u,v,c,0),add(v,u,0,0);
	}
	cout<<Dinic()<<" ";
	int tmp=cnt;
	for(int i=0;i<tmp;i+=2)
	{
	    add(E[i].from,E[i].to,inf,W[i/2]);
	    add(E[i].to,E[i].from,0,-W[i/2]);
	}
	add(N,T,K,0),add(T,N,0,0);
	cout<<mcmf();
    }
}

int main()
{
    TYC::work();
    return 0;
}

