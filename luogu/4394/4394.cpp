#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	int n,sum,ans,a[310],dp[100010];
	
	bool cmp(const int &x,const int &y)
	{
		return x>y;
	}
	
	void work()
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) 
			scanf("%d",&a[i]),sum+=a[i];
		sort(a+1,a+1+n,cmp);
		dp[0]=1;
		for(int i=1;i<=n;i++)
			for(int j=sum/2+a[i];j>=a[i];j--)
				if(dp[j-a[i]])
				{
					dp[j]=1;
					ans=max(ans,j);
				}
		printf("%d",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
} 
