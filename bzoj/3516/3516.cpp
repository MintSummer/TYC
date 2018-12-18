#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;

	const ll p=1e9+7;
	const int N=1010;

	int n,m;
	ll f[N],Pow[N],C[N][N];

	inline ll qpow(ll x,ll tim)
	{
		ll ans=1;
		for(;tim;tim>>=1,x=x*x%p)
			if(tim&1) ans=ans*x%p;
		return ans;
	}

	#define Mod(x) (x)>=p?(x)-p:(x)

	void init()
	{
		C[0][0]=1;
		for(int i=1;i<=m;i++)
		{
			C[i][0]=1;
			for(int j=1;j<=m;j++)
				C[i][j]=Mod(C[i-1][j-1]+C[i-1][j]);
		}
		Pow[0]=1;
		for(int i=1;i<=m;i++) Pow[i]=Pow[i-1]*n%p;
	}

	void work()
	{
		scanf("%d%d",&n,&m);
		if(m==1)
		{
			printf("%lld\n",(ll)(n+1)*n/2%p);
			return;
		}
		init();
		ll t1=qpow(m,n),t2=t1*m%p,inv=qpow(m-1,p-2);
		f[0]=(Mod(qpow(m,n+1)-1+p))*qpow(m-1,p-2)%p;
		for(int i=1;i<=m;i++)
		{
			ll sum=0;
			for(int j=0;j<i;j++)
				sum=Mod(sum+(C[i][j]*(f[j]-Pow[j]*t1%p+p)%p));
			if(m!=1) f[i]=(Pow[i]*t2-m*sum+p)%p*inv%p;
		}
		printf("%lld\n",f[m]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
