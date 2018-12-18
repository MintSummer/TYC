#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	ll n,k,ans;

	void work()
	{
		scanf("%lld%lld",&n,&k);
		if(n>k) ans=k*(n-k);
		ans+=k*min(n,k);
		for(int i=1,j;i<=min(k,n);i=j+1)
		{
			j=min(k/(k/i),n);
			ans-=(k/i)*(i+j)*(j-i+1)/2;
		}
		printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
