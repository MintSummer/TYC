#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=10010,M=200010,inf=0x3f3f3f3f;
    int n,m,s,t,cnt1,cnt2,h1[N],h2[N],dis[N];
    bool mark[N],vis[N];
    typedef pair<int,int> pa;

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
    }e1[M],e2[M];

    inline void add(edge *E,int *Head,int &cnt,int u,int v)
    {
        E[++cnt]=(edge){v,Head[u]};
        Head[u]=cnt;
    }

    void Dijkstra(edge *E,int *Head,int start)
    {
        memset(dis,inf,sizeof(dis));
        memset(vis,false,sizeof(vis));
        priority_queue<pa,vector<pa>,greater<pa> > q;
        dis[start]=0;
        q.push(pa(0,start));
        while(!q.empty())
        {
            int u=q.top().second;q.pop();
            if(vis[u]||mark[u]) continue;
            vis[u]=1;
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(mark[v]) continue;
                if(dis[v]>dis[u]+1)
                {
                    dis[v]=dis[u]+1;
                    if(!vis[v]) q.push(pa(dis[v],v));
                }
            }
        }
    }

    void work()
    {
        n=read(),m=read();
        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read();
            add(e1,h1,cnt1,u,v);
            add(e2,h2,cnt2,v,u);
        }
		scanf("%d%d",&s,&t);
        Dijkstra(e2,h2,t);
        for(int u=1;u<=n;u++)
            if(dis[u]==inf) 
            {
                mark[u]=1;
                for(int i=h2[u];i;i=e2[i].next)
                    mark[e2[i].to]=1;
            }
        Dijkstra(e1,h1,s);
        if(dis[t]==inf) puts("-1");
        else printf("%d\n",dis[t]); 
    }
}

int main()
{
    TYC::work();
    return 0;
}
