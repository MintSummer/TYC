//必须用邻接表存储的恶心题
#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=2010,M=N*(N-1),inf=0x3f3f3f3f;
    int n,m,G[N][N],tag[M],dis[N],cnt[N],vis[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    void spfa(int s)
    {
        memset(dis,inf,sizeof(dis));
        queue<int> q;
        dis[s]=0,cnt[s]=1,vis[s]=1;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            vis[u]=0;
            for(int v=1;v<=n;v++)
                if(G[u][v]!=inf)
                {
                    if(dis[v]==dis[u]+G[u][v]) 
                        cnt[v]+=cnt[u];
                    if(dis[v]>dis[u]+G[u][v])
                        dis[v]=dis[u]+G[u][v],cnt[v]=cnt[u];
                    if(cnt[v]&&!vis[v]) vis[v]=1,q.push(v);
                }
            if(u!=n) cnt[u]=0;
        }
    }

    void work()
    {
        n=read(),m=read();
        memset(G,inf,sizeof(G));
        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read(),w=read();
            G[u][v]=min(G[u][v],w);
        }
        spfa(1);
        if(dis[n]==inf) puts("No answer");
        else printf("%d %d\n",dis[n],cnt[n]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
