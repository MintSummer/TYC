#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1e5+10;
    int n;
	ll m[N],a[N];

    ll mul(ll x,ll y,ll mod)
    {
        ll ans=0;
        for(;y;y>>=1,x=(x+x)%mod)
            if(y&1) ans=(ans+x)%mod;
        return ans;
    }

    ll exgcd(ll a,ll b,ll &x,ll &y)
    {
        if(!b) {x=1,y=0;return a;}
        ll gcd=exgcd(b,a%b,x,y);
        ll tmp=x;
        x=y;
        y=tmp-a/b*y;
        return gcd;
    }

    ll excrt()
    {
        ll M=m[1],ans=a[1];//特判第一个方程
        for(int i=2;i<=n;i++)
        {
            ll x,y,b=m[i],c=(a[i]-ans%m[i]+m[i])%m[i];
            ll gcd=exgcd(M,b,x,y);
            if(c%gcd) return -1;
            x=mul(x,c/gcd,b/gcd);
            ans+=M*x;
            M*=b/gcd;
            ans=(ans%M+M)%M;
        }
        return ans;
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>m[i]>>a[i];
        printf("%lld\n",excrt());
    }
}

int main()
{
    TYC::work();
    return 0;
}
