#include<algorithm>
#include<cstdio>
using namespace std;
int t,w,a[1010],dp[1010][40];
int main(void)
{
	scanf("%d%d",&t,&w);
	for(int i=1;i<=t;i++)scanf("%d",&a[i]);
	if(a[1]==1)dp[1][0]=1,dp[1][1]=0;
	if(a[1]==2)dp[1][0]=0,dp[1][1]=1;
	for(int i=2;i<=t;i++)
	{
		dp[i][0]=dp[i-1][0]+(a[i]==1?1:0);
		for(int j=1;j<=w;j++)
		{
			int x=j%2+1;
			dp[i][j]=max(dp[i-1][j]+(a[i]==x?1:0),
				dp[i-1][j-1]+(a[i]==x?1:0));
		}
	}
	int maxx=-1;
	for(int i=0;i<=w;i++)maxx=max(maxx,dp[t][i]);
	printf("%d",maxx);
	return 0;
}

