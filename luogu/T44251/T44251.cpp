#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1e4+10,M=5e5+10,inf=0x3f3f3f3f;
    int n,m,cnt,Head[N],vis[N];
    ll ans=(1LL<<60),dis[N];
    queue<int> q;

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }
    
    struct Edge
    {
        int u,v,len,cost;
        bool operator < (const Edge &t) const
        {
            return (cost<t.cost)||(cost==t.cost&&len<t.len);
        }
    }e[M];

    struct edge
    {
        int to,next,w;
    }E[M];

    inline void add(int u,int v,int w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
    }

    void spfa()
    {
        while(!q.empty())
        {
            int u=q.front();q.pop();
            vis[u]=0;
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(dis[v]>dis[u]+E[i].w)
                {
                    dis[v]=dis[u]+E[i].w;
                    if(!vis[v]) vis[v]=1,q.push(v);
                }
            }            
        }
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<=m;i++)
            e[i]=(Edge){read(),read(),read(),read()};
        sort(e+1,e+1+m);
        for(int i=1;i<=n;i++) dis[i]=inf;
        dis[1]=0;
        int cost=e[1].cost-1;
        for(int i=1;i<=m;i++)
        {
            int u=e[i].u,v=e[i].v,w=e[i].len;
            add(u,v,e[i].len);
            if(dis[v]>dis[u]+w)
            {
                dis[v]=dis[u]+w;
                if(!vis[v]) vis[v]=1,q.push(v);
            }
            cost=e[i].cost;
            if(e[i+1].cost==cost) continue;
            spfa();
            ans=min(ans,(ll)dis[n]*cost);
        }
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}