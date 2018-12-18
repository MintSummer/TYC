#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

namespace TYC
{
    const int N=100010,M=200010,inf=0x3f3f3f3f;
    typedef pair<int,int> pa;
    int T,n,m,k,p,cnt,Head[N],vis[N],cur[N],dis[N],instack[N][55],dp[N][55];
    #define Mod(x) x>p?x-p:x;

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    inline void init()
    {
        cnt=0;
        memset(Head,0,sizeof(Head));
        memset(cur,0,sizeof(cur));
        memset(vis,0,sizeof(vis));
        memset(dis,inf,sizeof(dis));
        memset(dp,0,sizeof(dp));
        memset(instack,0,sizeof(instack));
    }

    struct edge
    {
        int to,next,w;
    }E[M<<1];

    inline void add(int u,int v,int w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
        E[++cnt]=(edge){u,cur[v],w};
        cur[v]=cnt;
    }

    void Dijkstra()
    {
        priority_queue<pa,vector<pa>,greater<pa> > q; 
        dis[n]=0;
        q.push(pa(0,n));
        while(!q.empty())
        {
            int u=q.top().second;
            q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(int i=cur[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(dis[v]>dis[u]+E[i].w)
                {
                    dis[v]=dis[u]+E[i].w;
                    if(!vis[v]) q.push(pa(dis[v],v));
                }
            }
        }
    }

    int dfs(int u,int rest)
    {
        if(instack[u][rest]) return -1;
        if(dp[u][rest]) return dp[u][rest];
        instack[u][rest]=1;
        if(u==n) dp[u][rest]=1;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to,delta=dis[v]+E[i].w-dis[u];
            if(delta>rest) continue;
            int tmp=dfs(v,rest-delta);
            if(tmp==-1) return -1;
            dp[u][rest]=Mod(dp[u][rest]+tmp);
        }
        instack[u][rest]=0;
        return dp[u][rest];
    }

    void work()
    {
        T=read();
        while(T--)
        {
            init();
            n=read(),m=read(),k=read(),p=read();
            for(int i=1;i<=m;i++)
            {
                int u=read(),v=read(),w=read();
                add(u,v,w);
            }
            Dijkstra();
            printf("%d\n",dfs(1,k));
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
