#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1e5+10;
    int n,a[N],sum[N],f[N];
    ll ans=0;

    void work()
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
        {
            sum[i]=sum[i-1]^a[i];
            for(int j=0;j<i;j++)
                ans+=sum[i]^sum[j];
        }
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}