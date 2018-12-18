#include<bits/stdc++.h>
using namespace std;

namespace TYC
{	
	typedef long long ll;
	const int N=1e5+10;

	int n,m,T,p,B[N];
	ll ans,fac[N],inv[N];

	inline ll qpow(ll x,int tim)
	{
		ll ans=1;
		for(;tim;tim>>=1,x=x*x%p)
			if(tim&1) ans=ans*x%p;
		return ans;
	}

	inline ll C(const int n,const int m)
	{
		if(n<m) return 0;
		return fac[n]*inv[m]%p*inv[n-m]%p;
	}

	inline ll Lucas(const int n,const int m)
	{
		if(!m) return 1;
		if(n<m) return 0;
		return Lucas(n/p,m/p)*C(n%p,m%p)%p;
	}

	void init()	
	{
		fac[0]=1;
		for(int i=1;i<p;i++) fac[i]=fac[i-1]*i%p;
		inv[p-1]=qpow(fac[p-1],p-2);
		for(int i=p-1;i;i--) inv[i-1]=inv[i]*i%p;
	}

	void dfs(const int now,const int num,const ll sum)
	{
		if(now>T) 
		{
			ans=(ans+((num&1)?-1:1)*Lucas(n+m-sum-num,n)%p+p)%p;
			return;
		}
		dfs(now+1,num,sum);
		dfs(now+1,num+1,sum+B[now]);
	}

	void work()
	{
		scanf("%d%d%d%d",&n,&T,&m,&p);
		for(int i=1;i<=T;i++) scanf("%d",&B[i]);
		init();
		dfs(1,0,0);
		printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
