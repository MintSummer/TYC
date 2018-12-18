#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=5010,M=50010,inf=0x3f3f3f3f;
	int n,m,s,t,cnt=1,Head[N+M],cur[N+M],dep[N+M];
	ll ans=0;
	
	struct edge
	{
		int to,next,w;
	}E[M*8];
	
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
		add(u,v,w);
		add(v,u,0);
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
            int u=q.front();
            q.pop();
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(E[i].w>0&&dep[v]==-1)
                    dep[v]=dep[u]+1,q.push(v);
            }
        }
        return dep[t]!=-1;
    }

    int dfs(int u,int mn)
    {
        if(u==t||mn==0) return mn;
        int v,w,used=0;
        for(int &i=cur[u];i;i=E[i].next)
        {
            v=E[i].to;
            if(E[i].w>0&&dep[u]+1==dep[v])
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
        while(bfs()) ans-=dfs(s,inf);
    }
	
	void work()
	{
		scanf("%d%d",&n,&m);
		s=0,t=n+m+1;
		int a,b,c;
		for(int i=1;i<=n;i++) 
			scanf("%d",&a),insert(i+m,t,a);
		for(int i=1;i<=m;i++) 
		{
			scanf("%d%d%d",&a,&b,&c);
			ans+=c;
			insert(s,i,c);
			insert(i,a+m,inf),insert(i,b+m,inf);
		}
		Dinic();
		printf("%lld",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
} 
