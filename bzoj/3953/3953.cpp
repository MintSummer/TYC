#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int N=100010,M=200010,inf=0x3f3f3f3f;
    typedef long long ll;
    typedef pair<ll,int> pa;
    int T,n,m,k,p,cnt,Head[N],vis[N],cur[N];
    ll dis[N];

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
        memset(dis,inf,sizeof(dis));
        priority_queue<pa,vector<pa>,greater<pa> > q; 
        dis[s]=0;
        q.push(0,n);

    }

    void work()
    {
        T=read();
        while(T--)
        {
            n=read(),m=read(),k=read(),p=read();
            for(int i=1;i<=n;i++)
            {
                int u=read(),v=read(),w=read();
                add(u,v,w);
            }
            Dijkstra();
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}