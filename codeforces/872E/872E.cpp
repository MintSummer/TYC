#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=2e5+10,p=1e9+7;
    int n,cnt,Head[N],vis[N],mark[N],size[N];
    map<int,int> idx,idy;

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

    ll qpow(ll x,ll tim)
    {
        ll ans=1;
        for(;tim;tim>>=1,x=x*x%p)
            if(tim&1) ans=ans*x%p;
        return ans;
    }

    void dfs(int u,int f)
    {
        vis[u]=size[u]=1;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) {f=0;continue;}
            if(vis[v]) continue;
            dfs(v,u);
            size[u]+=size[v];
        }
    }

    bool check(int u,int f)
    {
        if(mark[u]) return true;
        mark[u]=1;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) {f=0;continue;}
            if(check(v,u)) return true;
        }
        mark[u]=0;
        return false;
    }

    void work()
    {
        n=read();
        int nodex=0,nodey=0;
        for(int i=1;i<=n;i++)
        {
            int x=read(),y=read();
            if(!idx.count(x)) idx[x]=++nodex;
            if(!idy.count(y)) idy[y]=++nodey;
            add(idx[x],idy[y]+n),add(idy[y]+n,idx[x]);
        }
        ll ans=1;
        for(int i=1;i<=nodex;i++)
            if(!vis[i]) 
            {
                dfs(i,0);
                if(check(i,0)) ans=qpow(2,size[i])*ans%p;
                else ans=(qpow(2,size[i])-1)*ans%p;
            }
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}