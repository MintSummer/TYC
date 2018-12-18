#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int p=20101009,N=1e7+10;
    const int inv2=(p+1)/2;
    int n,m,cnt,mu[N],prime[N];
    ll sum[N];
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
            sum[i]=(sum[i-1]+1LL*i*i*mu[i]%p)%p;
    }

    inline ll cal(ll x)
    {
        return (1+x)*x%p*inv2%p;
    }

    ll F(int x,int y)
    {
        ll ans=0,limit=min(x,y);
        for(ll l=1,r;l<=limit;l=r+1)
        {
            r=min(x/(x/l),y/(y/l));
            ans=(ans+cal(x/l)*cal(y/l)%p*(sum[r]-sum[l-1]+p)%p)%p;
        }
        return ans;
    }

    void work()
    {
        scanf("%d%d",&n,&m);
        ll limit=min(n,m),ans=0;
        init(limit);
        for(ll d=1,last;d<=limit;d=last+1)
        {
            last=min(n/(n/d),m/(m/d));
            ans=(ans+(d+last)*(last-d+1)%p*inv2%p*F(n/d,m/d)%p)%p;
        }
        printf("%lld\n",(ans+p)%p);
    }
}

int main()
{
    TYC::work();
    return 0;
}
