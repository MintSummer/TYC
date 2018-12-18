#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int MAXN=200010,inf=0x3f3f3f3f;
    int N,S,T,cnt=1,Head[MAXN],leaf[MAXN],dep[MAXN];

    struct edge
    {
		int to,next;
		ll w;
    }E[100010*8];

    void add(int u,int v,ll w)
    {
		cnt++;
		E[cnt].to=v;
		E[cnt].next=Head[u];
		E[cnt].w=w;
		Head[u]=cnt;
    }

    bool bfs()
    {
		memset(dep,-1,sizeof(dep));
		dep[S]=0;
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

    ll dfs(int u,ll mn)
    {
		if(u==T) return mn;
		ll w,used=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
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

    ll Dinic()
    {
		ll ans=0;
		while(bfs())
			ans+=dfs(S,inf);
		return ans;
    }

    void work()
    {
		ios::sync_with_stdio(false);
		cin>>N>>S;
		T=N+1;
		int u,v;
		ll w;
		for(int i=1;i<N;i++) 
		{
			cin>>u>>v>>w;
			add(u,v,w),add(v,u,w);
			leaf[u]++,leaf[v]++;
		}
		for(int i=1;i<=N;i++) 
			if(leaf[i]==1&&i!=S) add(i,T,inf),add(T,i,0);
		cout<<Dinic();
    }
}

int main()
{
    TYC::work();
    return 0;
}
