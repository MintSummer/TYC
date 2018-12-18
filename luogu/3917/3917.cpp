#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1e5+10;
    int n,num[N];
    ll ans=0,a[N],sum[N];

    void work()
    {
        scanf("%d",&n);
        ll mx=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%lld",&a[i]);
            a[i]^=a[i-1];
            mx=max(mx,a[i]);
            ans+=a[i];
        }
        for(int i=0;(1LL<<i)<=mx&&i<=32;i++)
        {
            for(int j=1;j<=n;j++)
                num[j]=num[j-1]+((a[j]>>i)&1);
            int one=num[n],zero=n-num[n];
            for(int j=1;j<=n;j++)
            {
                if((a[j]>>i)&1) ans+=(1LL<<i)*(zero-(j-num[j]));
                else ans+=(1LL<<i)*(one-num[j]);
            }
        }
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}