#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int p=20101009,N=1e7+10;
    const int inv2=(p+1)/2;
    int n,m,cnt,mu[N],prime[N],sum[N];
    bool vis[N];

    inline void init(int maxn)
    {
        mu[1]=1;
        for(int i=2;i<=maxn;i++)
        {
            if(!vis[i]) prime[++cnt]=i,mu[i]=-1;
            for(int j=1,k;j<=cnt&&(k=i*prime[j])<=maxn;j++)
            {
                vis[k]=1;
                if(i%prime[j]==0) {mu[k]=0;break;}
                mu[k]=-mu[i];
            }
        }
        for(int i=1;i<=maxn;i++)
            sum[i]=(ll)(sum[i-1]+1LL*i*i*mu[i]%p)%p;
    }

    inline ll cal(int x)
    {
        return (ll)(1+x)*x%p*inv2%p;
    }

    void work()
    {
        scanf("%d%d",&n,&m);
        int limit=min(n,m);
        init(limit);
        ll ans=0;
        for(int d=1;d<=limit;d++)
        {
            int tn=n/d,tm=m/d,lim=min(tn,tm);
            ll tot=0;
            for(int l=1,r;l<=lim;l=r+1)
            {
                r=min(tn/(tn/l),tm/(tm/l));
                tot=(tot+cal(tn/l)*cal(tm/l)%p*(sum[r]-sum[l-1]+p)%p)%p;
            }
            ans=(ans+tot*d%p)%p;
        }
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
