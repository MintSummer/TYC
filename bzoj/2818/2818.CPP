#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1e7+5;
    int cnt,n,prime[700010],phi[N];
    ll ans,sum[N>>1];
    bool vis[N];

    inline void init(int maxn)
    {
        phi[1]=1;
        for(int i=2;i<=maxn;i++)
        {
            if(!vis[i]) prime[++cnt]=i,phi[i]=i-1;
            for(int j=1,k;j<=cnt&&(k=i*prime[j])<=maxn;j++)
            {
                vis[k]=1;
                if(i%prime[j]==0) 
                {
                    phi[k]=phi[i]*prime[j];
                    break;
                }
                phi[k]=phi[i]*(prime[j]-1);
            }
        }
        for(int i=1;i<=(maxn>>1);i++) 
            sum[i]=sum[i-1]+phi[i]*2;
    }

    void work()
    {
        init(1e7);
        scanf("%d",&n);
        for(int i=1;i<=cnt&&prime[i]<=n;i++)
            ans+=sum[n/prime[i]]-1;
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
