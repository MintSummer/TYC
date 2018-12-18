#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    typedef long long ll;
    ll n,m,p;

    ll mul(ll x,ll y)
    {
		ll ans=0;
		for(;y;y>>=1,x=(x+x)%p)
			if(y&1) ans=(ans+x)%p;
		return ans;
    }

    ll qpow(ll x,ll tim)
    {
		ll ans=1;
		for(;tim;tim>>=1,x=mul(x,x))
			if(tim&1) ans=mul(ans,x);
		return ans;
    }

    void work()
    {
		scanf("%lld%lld%lld",&n,&m,&p);
		printf("%lld",mul(qpow(n,m-1),qpow(m,n-1)));
    }
}

int main()
{
    TYC::work();
    return 0;
}
