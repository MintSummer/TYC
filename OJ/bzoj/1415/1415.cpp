#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef pair<int,int> pii;
    const int N=1010,inf=0x3f3f3f3f;
    int n,m,sc,sk,cnt,Head[N],deg[N],dis[N][N],nxt[N][N];
    bool vis[N];
    double dp[N][N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    struct edge
    {
        int to,next;
    }E[N<<1];

    inline void add(int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
    }

    inline void Dijkstra(int s,int *dist)
    {
        priority_queue<pii,vector<pii>,greater<pii> > q;
        memset(vis,false,sizeof(int[n+1]));
        dist[s]=0;
        q.push(make_pair(0,s));
        while(!q.empty())
        {
            int u=q.top().second;q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(dist[v]>dist[u]+1)
                {
                    dist[v]=dist[u]+1;
                    if(!vis[v]) q.push(make_pair(dist[v],v));
                }
            }
        }
    }

    inline void init()
    {
        memset(dis,inf,sizeof(dis));
        for(int i=1;i<=n;i++) Dijkstra(i,dis[i]);
        for(int u=1;u<=n;u++)
            for(int aim=1;aim<=n;aim++)
            {
                if(u==aim) {nxt[u][aim]=aim;continue;}
                int to=-1;
                for(int i=Head[u];i;i=E[i].next)
                {
                    int v=E[i].to;
                    if(to==-1||dis[v][aim]<dis[to][aim]) to=v;
                    else if(dis[v][aim]==dis[to][aim]&&v<to) to=v;
                }
                nxt[u][aim]=to;
            }
    }

	double dfs(int u,int k)
	{
		if(dp[u][k]!=-1.0) return dp[u][k];
		double &ans=dp[u][k];
		if(u==k) return ans=0.0;
		if(nxt[u][k]==k||nxt[nxt[u][k]][k]==k) return ans=1.0;
		ans=0.0;
		for(int i=Head[k];i;i=E[i].next)
			ans+=dfs(nxt[nxt[u][k]][k],E[i].to);
		return ans=(ans+dfs(nxt[nxt[u][k]][k],k))/(deg[k]+1)+1;
	}

    void work()
    {
        n=read(),m=read();
        sc=read(),sk=read();
        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read();
            add(u,v),add(v,u);
            deg[u]++,deg[v]++;
        }
        init();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dp[i][j]=-1.0;
        printf("%.3f\n",dfs(sc,sk));
    }
}

int main()
{
    TYC::work();
    return 0;
}
