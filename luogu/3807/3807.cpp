#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1e5;
ll f[MAXN+10];

void init(int x)
{
    f[0]=1;
    for(int i=1;i<=x;i++) f[i]=(f[i-1]*i)%x;
}

ll qpow(ll x,ll tim,ll p)
{
    ll ans=1;
    for(;tim;tim>>=1,x=x*x%p)
		if(tim&1) ans=ans*x%p;
    return ans;
}

//C(n,m)%p = C(n/p,m/p)*C(n%p,m%p)%p
ll solve(ll n,ll m,ll p)
{
    ll ans=1;
    while(n&&m)
    {
		ll a=n%p,b=m%p;
		if(a<b) return 0;
		ans=ans*f[a]%p*qpow(f[b],p-2,p)%p*qpow(f[a-b],p-2,p)%p;
		n/=p,m/=p;
    }
    return ans;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
		ll n,m,p;
		scanf("%lld%lld%lld",&n,&m,&p);
		init(p);
		printf("%lld\n",solve(n+m,m,p));
    }
    return 0;
}
