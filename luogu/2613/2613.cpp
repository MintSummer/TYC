#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const ll p=19260817;
	
	inline ll qpow(ll x,ll tim)
	{
		ll ans=1;
		for(;tim;tim>>=1,x=x*x%p)
			if(tim&1) ans=ans*x%p;
		return ans;
	}
	
	inline ll read()
	{
		ll x=0;char ch=getchar();
		while(!isdigit(ch)) ch=getchar();
		while(isdigit(ch)) x=(x*10+ch-'0')%p,ch=getchar();
		return x;
	}
	
	void work()
	{
		ll a=read(),b=read();
		if(!b) puts("Angry!");
		else printf("%lld\n",a*qpow(b,p-2)%p);
	}
}

int main()
{
	TYC::work();
	return 0;
}
