#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int inf=0x3f3f3f3f,MAXN=510;
    typedef long long ll;
    int N,M,cnt,top,tot,tim,K;
    int Head[MAXN],cut[MAXN],vis[MAXN],belong[MAXN],size[MAXN];

    struct edge
    {
        int to,next;
    }E[MAXN*MAXN];

    void add(int u,int v)
    {
        cnt++;
        E[cnt].to=v;
        E[cnt].next=Head[u];
        Head[u]=cnt;
    }

    void init()
    {
        N=cnt=tot=top=tim=K=0;
        memset(Head,0,sizeof(Head));
        memset(cut,0,sizeof(cut));
        memset(belong,0,sizeof(belong));
        memset(size,0,sizeof(size));
    }

    void dfs1(int u)
    {
        vis[u]=1;
        for(int i=Head[u];i;i=E[i].next)
            if(!vis[E[i].to]&&E[i].to!=K)
            {
                vis[E[i].to]=1;
                dfs1(E[i].to);
            }
    }

    void dfs2(int u)
    {
        vis[u]=1;
        if(!belong[u]) belong[u]=K;
        else belong[u]=-1;
        for(int i=Head[u];i;i=E[i].next)
            if(!vis[E[i].to]&&!cut[E[i].to]) 
                dfs2(E[i].to);
    }

    void work()
    {
        int u,v;
        for(int i=1;i<=M;i++)
        {
            cin>>u>>v;
            add(u,v),add(v,u);
            N=max(N,max(u,v));
        }
        for(K=1;K<=N;K++)
        {
            memset(vis,0,sizeof(vis));
            dfs1(K%N+1);
            for(int i=1;i<=N;i++)
            if(!vis[i]&&i!=K)
            {
                cut[K]=1;
                break;
            }
        }    
        K=0;
        for(int u=1;u<=N;u++)
            if(cut[u])
            {
                memset(vis,0,sizeof(vis));
                for(int i=Head[u];i;i=E[i].next)
                    if(!vis[E[i].to]&&!cut[E[i].to])
                    K++,dfs2(E[i].to);
            }
        for(int i=1;i<=N;i++)
            if(belong[i]!=-1) size[belong[i]]++;
        ll tot=0,ans=1;
        for(int i=1;i<=K;i++)
            if(size[i]!=0) tot++,ans*=size[i];
        if(!tot) cout<<"2 "<<N*(N-1)/2<<endl;
        else cout<<tot<<" "<<ans<<endl;
    }

    void solve()
    {
        ios::sync_with_stdio(false);
        int kase=0;	
        while(1)
        {
            kase++;
            cin>>M;
            if(!M) break;
            init();
            cout<<"Case "<<kase<<": ";
            work();
        }
    }
}

int main()
{
    TYC::solve();
    return 0;
}
