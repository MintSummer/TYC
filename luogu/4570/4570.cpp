#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=1010;
	int n;
	ll bin[65],b[65];
	struct node
	{
		int magic;
		ll num;
		bool operator < (const node &d) const
		{
			return magic>d.magic;
		}
	}a[N];

	inline bool insert(ll x)
	{
		for(int i=60;i>=0;i--)
			if(x&bin[i])
			{
				if(!b[i]) {b[i]=x;return true;}
				else x^=b[i];
			}
		return false;
	}

	void work()
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%lld%d",&a[i].num,&a[i].magic);
		sort(a+1,a+1+n);
		ll ans=0;
		bin[0]=1;
		for(int i=1;i<=60;i++) bin[i]=bin[i-1]<<1;
		for(int i=1;i<=n;i++)
			if(insert(a[i].num)) ans+=a[i].magic;
		printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
