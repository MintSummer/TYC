#include<bits/stdc++.h>
using namespace std;
const int MAXN=310;
int n,dp[MAXN][MAXN],a[MAXN],ans;
//dp[l][r]表示合并区间l到r的最大值

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&dp[i][i]),ans=max(ans,dp[i][i]);
	for(int len=2;len<=n;len++)//枚举区间长度
	{
		for(int i=1;i+len-1<=n;i++)
		{
			int j=i+len-1;
			for(int k=i;k<j;k++)//枚举合并i到j区间的接点
				if(dp[i][k]==dp[k+1][j])
					dp[i][j]=max(dp[i][j],dp[i][k]+1);
			ans=max(ans,dp[i][j]);
		}
	}
	printf("%d",ans);
	return 0;
}
