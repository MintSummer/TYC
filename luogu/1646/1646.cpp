#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=200010,inf=0x3f3f3f3f;
    typedef long long ll;
    int n,m,tot,cnt=1,s,t,num[110][110],Head[N],dep[N],cur[N];
    ll ans=0;

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
    }E[500010];

    inline void insert(int u,int v,int w)
    {
        E[++cnt]=(edge){v,Head[u],w};
        Head[u]=cnt;
        E[++cnt]=(edge){u,Head[v],0};
        Head[v]=cnt;
    }

    bool bfs()
    {
        memset(dep,-1,sizeof(dep));
        memcpy(cur,Head,sizeof(cur));
        queue<int> q;
        dep[s]=0;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(E[i].w&&dep[v]==-1) 
                    dep[v]=dep[u]+1,q.push(v);
            }
        }
        return dep[t]!=-1;
    }

    int dfs(int u,int mn)
    {
        if(u==t) return mn;
        int v,w,used=0;
        for(int i=Head[u];i;i=E[i].next)
        {
            v=E[i].to;
            if(E[i].w&&dep[v]==dep[u]+1)
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
        n=read(),m=read();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                num[i][j]=++tot;
        s=++tot,t=++tot;
        int x;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                insert(s,num[i][j],x=read()),ans+=x;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                insert(num[i][j],t,x=read()),ans+=x;
        for(int i=1;i<n;i++)
            for(int j=1;j<=m;j++)
            {
                insert(s,++tot,x=read());
                insert(tot,num[i][j],inf);
                insert(tot,num[i+1][j],inf);
                ans+=x;
            }
        for(int i=1;i<n;i++)
            for(int j=1;j<=m;j++)
            {
                insert(++tot,t,x=read());
                insert(num[i][j],tot,inf);
                insert(num[i+1][j],tot,inf);
                ans+=x;
            }
        for(int i=1;i<=n;i++)
            for(int j=1;j<m;j++)
            {
                insert(s,++tot,x=read());
                insert(tot,num[i][j],inf);
                insert(tot,num[i][j+1],inf);
                ans+=x;
            }
        for(int i=1;i<=n;i++)
            for(int j=1;j<m;j++)
            {
                insert(++tot,t,x=read());
                insert(num[i][j],tot,inf);
                insert(num[i][j+1],tot,inf);
                ans+=x;
            }
        Dinic();
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
