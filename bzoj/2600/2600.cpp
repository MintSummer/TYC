#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=1e5+10;
	int n,len;
	ll money,a[N],sum[N];

	bool check(int x)
	{
		for(int l=1,r,mid1,mid2;l<=n-x+1;l++)
		{
			r=l+x-1;
			mid1=l+(x>>1)-1,mid2=r-(x>>1)+1;
			if(sum[r]-sum[mid2-1]-sum[mid1]+sum[l-1]<=money) return true;
		}
		return false;
	}

	void work()
	{
		scanf("%d%d%lld",&n,&len,&money);
		for(int i=1;i<=n;i++) 
			scanf("%lld",&a[i]),sum[i]=sum[i-1]+a[i];
		int l=1,r=n,mid,ans;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(check(mid)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%d",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
