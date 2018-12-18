#include<bits/stdc++.h>
using namespace std;

namespace XXJ
{
	int bin[35],a[35];
	inline bool insert(int x)
	{
		for(int i=30;i>=0;i--)
			if(x&bin[i])
			{
				if(!a[i]) {a[i]=x;return true;}
				else x^=a[i];
			}
		return false;
	}
}

namespace TYC
{
	int n,a[110];

	bool cmp(int x,int y)
	{
		return x>y;
	}

	void work()
	{
		long long ans=0;
		scanf("%d",&n);
		XXJ::bin[0]=1;
		for(int i=1;i<=30;i++) XXJ::bin[i]=XXJ::bin[i-1]<<1;
		for(int i=1;i<=n;i++) 
			scanf("%d",&a[i]);
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++)
			if(!XXJ::insert(a[i])) ans+=a[i];
		printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
