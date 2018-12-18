#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const ll p=19940417;
    const ll inv2=9970209;
    const ll inv6=3323403; 
    ll n,m;

    ll sum(ll l,ll r)
    {
        return (l+r)*(r-l+1)%p*inv2%p;
    }

    ll sqr_sum(ll x)
    {
        return x*(x+1)%p*(2*x+1)%p*inv6%p;
    }

    ll sqr(ll l,ll r)
    {
        return sqr_sum(r)-sqr_sum(l-1);
    }

    void work()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cin>>n>>m;
        if(n>m) swap(n,m);
        ll sum1=0,sum2=0,sum3=0;
        for(int l=1,r;l<=n;l=r+1)
        {
            r=n/(n/l);
            sum1=(sum1+sum(l,r)*(n/l)%p)%p;
        }
        for(int l=1,r;l<=m;l=r+1)
        {
            r=m/(m/l);
            sum2=(sum2+sum(l,r)*(m/l)%p)%p; 
        }
        ll ans1=(n*n%p-sum1+p)%p*(m*m%p-sum2+p)%p;
        sum2=0;
        for(int l=1,r;l<=n;l=r+1)
        {
            r=min(n,m/(m/l));
            sum2=(sum2+sum(l,r)*(m/l)%p)%p;
        }
        for(int l=1,r;l<=n;l=r+1)
        {
            r=min(m/(m/l),n/(n/l));
            sum3=(sum3+sqr(l,r)*(n/l)%p*(m/l)%p)%p;
        }
        ll ans2=(n*m%p*n%p-m*sum1%p-n*sum2%p+sum3+p)%p;
        printf("%lld\n",(ans1-ans2+p)%p);
    }
}

int main()
{
    TYC::work();
    return 0;
}