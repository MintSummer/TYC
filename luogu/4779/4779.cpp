#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;

namespace TYC
{
    typedef long long ll;
    typedef pair<ll,int> pa;
    const int MAXN=100010,inf=0x3f3f3f3f;
    int n,m,s,cnt,Head[MAXN],vis[MAXN];
    ll dis[MAXN];

    struct edge
    {
        int to,next;
        ll w;
    }E[200010];

    void add(int u,int v,ll w)
    {
        cnt++;
        E[cnt].to=v;
        E[cnt].next=Head[u];
        E[cnt].w=w;
        Head[u]=cnt;
    }

    void Dijkstra()
    {
    	memset(vis,0,sizeof(vis));
        priority_queue<pa,vector<pa>,greater<pa> > q;
        for(int i=1;i<=n;i++) dis[i]=inf;
        dis[s]=0;
        q.push(make_pair(0,s));
        while(!q.empty())
        {
            int u=q.top().second;
            q.pop();
			if(vis[u]) continue;
			vis[u]=1;
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(dis[v]>dis[u]+E[i].w)
                {
                    dis[v]=dis[u]+E[i].w;
                    if(!vis[v]) q.push(make_pair(dis[v],v));
                }
            }
        }
    }

    void work()
    {
        scanf("%d%d%d",&n,&m,&s);
        int u,v;
        ll w;
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%lld",&u,&v,&w);
            add(u,v,w);
        }
        Dijkstra();
        for(int i=1;i<=n;i++) printf("%lld ",dis[i]);
    }
}

int main()
{
	freopen("rand.in","r",stdin);
    TYC::work();
    return 0;
}
