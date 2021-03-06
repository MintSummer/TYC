#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=320,inf=0x3f3f3f3f;
    int N,S,T,cnt=1,ans,Head[MAXN],pre[MAXN],dis[MAXN],vis[MAXN],d[MAXN];

    struct edge
    {
	int from,to,w,c,next;
    }E[MAXN*MAXN];

    void add(int u,int v,int w,int c)
    {
	E[++cnt]=(edge){u,v,w,c,Head[u]};
	Head[u]=cnt;
    }

    void insert(int u,int v,int w,int c)
    {
	add(u,v,w,c),add(v,u,0,-c);
    }

    bool spfa()
    {
	memset(dis,inf,sizeof(dis));
	memset(pre,0,sizeof(pre));
	memset(vis,0,sizeof(vis));
	queue<int> q;
	q.push(S);
	dis[S]=0,vis[S]=1;
	while(!q.empty())
	{
	    int u=q.front();
	    q.pop();
	    vis[u]=0;
	    for(int i=Head[u];i;i=E[i].next)
	    {
		int v=E[i].to;
		if(E[i].w&&dis[v]>dis[u]+E[i].c)
		{
		    dis[v]=dis[u]+E[i].c;
		    pre[v]=i;
		    if(!vis[v]) vis[v]=1,q.push(v);
		}
	    }
	}
	return dis[T]!=inf;
    }
    
    void mcmf()
    {
	while(spfa())
	{
	    int mn=inf;
	    for(int u=T;u!=S;u=E[pre[u]].from)
		mn=min(mn,E[pre[u]].w);
	    for(int u=T;u!=S;u=E[pre[u]].from)
		E[pre[u]].w-=mn,E[pre[u]^1].w+=mn;
	    ans+=mn*dis[T];
	}
    }

    void work()
    {
	scanf("%d",&N);
	S=N+1,T=N+2;
	int tot,v,w;
	for(int u=1;u<=N;u++)
	{
	    scanf("%d",&tot);
	    d[u]-=tot;
	    while(tot--)
	    {
		scanf("%d%d",&v,&w);
		insert(u,v,inf,w);
		d[v]++;
		ans+= w;
    	    }
	    if(u!=1) insert(u,1,inf,0);
	}
	for(int i=1;i<=N;i++)
	{
	    if(d[i]>0) insert(S,i,d[i],0);
	    if(d[i]<0) insert(i,T,-d[i],0);
	}
	mcmf();
	cout<<ans;
    }
}

int main()
{
    TYC::work();
    return 0;
}
