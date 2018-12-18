#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=3010,inf=0x3f3f3f3f;
    int N,r[MAXN],p,m,f,n,s,cnt=1,S,T,Head[MAXN*2],pre[MAXN*2],vis[MAXN*2];
    ll dis[MAXN*2];

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
	add(u,v,w,c);
	add(v,u,0,-c);
    }

    bool spfa()
    {
	for(int i=S;i<=T;i++) dis[i]=1e12;
	memset(pre,0,sizeof(pre));
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
		if(E[i].w>0&&dis[v]>dis[u]+E[i].c)
		{
		    dis[v]=dis[u]+E[i].c;
		    pre[v]=i;
		    if(!vis[v]) vis[v]=1,q.push(v); 
		}
	    }
	}
	return dis[T]!=1e12;
    }

    ll mcmf()
    {
	ll ans=0;
	while(spfa())
	{
	    int mn=inf;
	    for(int i=pre[T];i;i=pre[E[i].from])
		mn=min(mn,E[i].w);
	    for(int i=pre[T];i;i=pre[E[i].from])
		E[i].w-=mn,E[i^1].w+=mn;
	    ans+=(ll)mn*dis[T];
	}
	return ans;
    }

    void work()
    {
	ios::sync_with_stdio(false);
	cin>>N;
	for(int i=1;i<=N;i++) cin>>r[i];
	cin>>p>>m>>f>>n>>s;
	S=0,T=2*N+1;
	for(int i=1;i<=N;i++)
	{
	    insert(S,2*i-1,inf,p);
	    insert(2*i-1,T,r[i],0);

	    if(i+m<=N) insert(2*i,2*(i+m)-1,inf,f);
	    if(i+n<=N) insert(2*i,2*(i+n)-1,inf,s);
	    insert(S,2*i,r[i],0);
	    insert(2*i,2*(i+1),inf,0);
	}
	cout<<mcmf();
    }
}

int main()
{
    TYC::work();
    return 0;
}
