#include <bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef pair<int,int> pa;
    const int N=110010,M=2500010;
    int n,m,k,s,t,Head[N];
    
    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }
    
    struct edge
    {
        int to,next,w;
    }E[M];
    
    inline void add(int u,int v,int w,const int tag=0)
    {
        static int cnt=0;
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
        if(tag) return;
        E[++cnt]=(edge){u,Head[v],w};
        Head[v]=cnt;
    }
    
    void Dijkstra()
    {
        static int dis[N],vis[N];
        static priority_queue<pa,vector<pa>,greater<pa> > q;
        memset(dis,0x3f3f3f3f,sizeof(dis));
        dis[s]=0;
        q.push(pa(dis[s],s));
        while(!q.empty())
        {
            int u=q.top().second;q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(dis[v]>dis[u]+E[i].w)
                {
                    dis[v]=dis[u]+E[i].w;
                    if(!vis[v]) q.push(pa(dis[v],v));
                }			
            }
        }
        printf("%d\n",dis[t+n*k]);
    }
    
    void work()
    {
        n=read(),m=read(),k=read();
        s=read()+1,t=read()+1;
        for(int i=1;i<=m;i++)
        {
            int u=read()+1,v=read()+1,w=read();
            for(int j=0;j<=k;j++) add(u+n*j,v+n*j,w);
            for(int j=1;j<=k;j++) add(u+n*(j-1),v+n*j,0,1);
            for(int j=1;j<=k;j++) add(v+n*(j-1),u+n*j,0,1);
        }
        for(int i=1;i<=k;i++) add(t+n*(i-1),t+n*i,0);
        Dijkstra();
    }
}

int main()
{
    TYC::work();
    return 0;
} 
