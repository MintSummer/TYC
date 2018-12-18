#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1e7+5;
    int n,cnt,prime[700010],mu[N],sum[N],f[N];
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
        for(int i=1;i<=cnt;i++)
            for(int j=1;prime[i]*j<=maxn;j++)
                f[prime[i]*j]+=mu[j];
        for(int i=1;i<=maxn;i++) 
            sum[i]=sum[i-1]+f[i];
    }

    void work()
    {
        init(1e7);
        scanf("%d"&n);
        ll ans=0;
        for(int l=1,r;l<=n;l=r+1)
        {
            r=n/(n/l);
            ans+=1LL*(n/l)*(n/l)*(sum[r]-sum[l-1]);
        }
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}