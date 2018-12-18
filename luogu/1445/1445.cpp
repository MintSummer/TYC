#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const ll p=1e9+7;
    const int N=1e6+10;
    int n,cnt,prime[N],f[N],num[N];
    bool vis[N];

    void init()
    {
        for(int i=2;i<=n;i++)
        {
            if(!vis[i]) prime[++cnt]=i,f[i]=cnt;
            for(int j=1;j<=cnt&&i*prime[j]<=n;j++)
            {
                vis[i*prime[j]]=1;
                f[i*prime[j]]=j;
                if(!(i%prime[j])) break;
            }
        }
    }

    void work()
    {
        scanf("%d",&n);
        init();
        for(int i=1;i<=n;i++)
            for(int t=i;t!=1;t/=prime[f[t]]) num[f[t]]++;
        for(int i=1;i<=cnt;i++) num[i]<<=1;
        ll ans=1;
        for(int i=1;i<=cnt;i++)
            ans=ans*(num[i]+1)%p;
        printf("%lld\n",ans);
    }
}

int main()
{
    TYC::work();
    return 0;
}
