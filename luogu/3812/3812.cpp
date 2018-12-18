#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	int n;
	ll bin[55],a[55];

	inline void insert(ll x)
	{
		for(int i=50;i>=0;i--)
			if(x&bin[i])
			{
				if(!a[i]) {a[i]=x;return;}
				else x^=a[i];
			}
	}

	inline ll query()
	{
		ll ans=0;
		for(int i=50;i>=0;i--)
			if((ans^a[i])>ans) ans^=a[i];
		return ans;
	}

	void work()
	{
		scanf("%d",&n);
		bin[0]=1;
		for(int i=1;i<=50;i++) bin[i]=bin[i-1]<<1;
		ll x;
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&x);
			insert(x);
		}	
		printf("%lld\n",query());
	}
}

int main()
{
	TYC::work();
	return 0;
}
