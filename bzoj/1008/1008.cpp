#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p=100003;
ll n,m;

ll mi(ll a,ll tim)
{
	ll ans=1;
	for(;tim;tim>>=1,a=(a*a)%p) if(tim&1) ans=(ans*a)%p;
	return ans;
}

int main()
{
	scanf("%lld%lld",&m,&n);
	ll ans=mi(m,n);
	ans-=(m*mi(m-1,n-1))%p;
	if(ans<0) ans+=p;//有时候%着%着就变成负数了
	printf("%lld",ans);
	return 0;
}
