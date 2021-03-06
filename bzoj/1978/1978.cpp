#include<bits/stdc++.h>
using namespace std;
int n,l,pre[1000005],dp[50010],ans;
//dp[i]表示如果以i作为最后一个数，最多能取多少个
//pre[j]表示能整除j的最后一个数是第几个
//每次处理a[i]时只要分解a[i]的因数，然后用pre[j]更新dp[i]，同时用i更新pre[j]。

int main()
{
	int x;
	scanf("%d%d",&n,&l);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		for(int j=1;j<=sqrt(x);j++) 
			if(x%j==0) 
			{
				if(j>=l) dp[i]=max(dp[i],dp[pre[j]]+1),pre[j]=i;
				int k=x/j;
				if(k!=j&&k>=l) dp[i]=max(dp[i],dp[pre[k]]+1),pre[k]=i;
			}
		ans=max(ans,dp[i]);
	}
	printf("%d",ans);
	return 0;
}
