#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p=1000000007;
ll n,k;

ll qpow(ll x,ll tim)
{
    ll ans=1;
    for(;tim;tim>>=1,x=x*x%p)
		if(tim&1) ans=ans*x%p;
    return ans;
}

int main()
{
    scanf("%lld%lld",&n,&k);
    printf("%lld",qpow(qpow(2,n),k));
    return 0;
}
