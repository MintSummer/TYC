#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=200010,p=10007;
    int n,cnt,val[N],Head[N],mx[N],sum[N],smx[N];
    ll ans1,ans2;

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

    void dfs(int u,int f)
    {
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(v==f) continue;
            dfs(v,u);
            if(mx[u]<val[v]) smx[u]=mx[u],mx[u]=val[v];
            else if(smx[u]<val[v]) smx[u]=val[v];
            ans1=max(ans1,(ll)val[u]*mx[v]);
            ans2=(ans2+val[u]*sum[v]%p+val[v]*sum[u]%p)%p;
            sum[u]=(sum[u]+val[v])%p;
        }
        ans1=max(ans1,(ll)mx[u]*smx[u]);
    }

    void work()
    {
        n=read();
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read();
            add(u,v),add(v,u);
        }
        for(int i=1;i<=n;i++) val[i]=read();
        dfs(1,0);
        printf("%lld %lld\n",ans1,ans2*2%p);
    }
}

int main()
{
    TYC::work();
    return 0;
}
